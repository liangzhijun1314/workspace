#include "showdevicesize.h"
#include <QHeaderView>
#include <QTableWidget>
#include <QProgressBar>

#ifdef Q_OS_WIN
#include "windows.h"
#endif
#define GB (1024 * 1024 * 1024)
#define MB (1024 * 1024)
#define KB (1024)

ShowDeviceSize *ShowDeviceSize::self = 0;
ShowDeviceSize::ShowDeviceSize(QObject *parent) : QObject(parent)
{
	process = new QProcess(this);
	connect(process, SIGNAL(readyRead()), this, SLOT(ReadData()));
}

void ShowDeviceSize::SetTableWidget(QTableWidget *tableWidget)
{
	this->tableWidget = tableWidget;
	this->tableWidget->clear();

	//设置列数和列宽
	this->tableWidget->setColumnCount(5);
	this->tableWidget->setColumnWidth(0, 100);
	this->tableWidget->setColumnWidth(1, 100);
	this->tableWidget->setColumnWidth(2, 100);
	this->tableWidget->setColumnWidth(3, 100);
	this->tableWidget->setColumnWidth(4, 150);

	this->tableWidget->setStyleSheet("QTableWidget::item{padding:0px;}");

	QStringList headText;
    headText << QString::fromLocal8Bit("盘符")
             << QString::fromLocal8Bit("已用空间")
             << QString::fromLocal8Bit("可用空间")
             << QString::fromLocal8Bit("总大小")
             << QString::fromLocal8Bit("已用百分比") ;
	this->tableWidget->setHorizontalHeaderLabels(headText);
	this->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	this->tableWidget->verticalHeader()->setVisible(true);
	this->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

void ShowDeviceSize::Load()
{
	//清空原有数据
	int row = this->tableWidget->rowCount();

	for (int i = 0; i < row; i++) {
		this->tableWidget->removeRow(0);
	}

#ifdef Q_OS_WIN
	QFileInfoList list = QDir::drives();

	foreach (QFileInfo dir, list) {
		QString dirName = dir.absolutePath();
		LPCWSTR lpcwstrDriver = (LPCWSTR)dirName.utf16();
		ULARGE_INTEGER liFreeBytesAvailable, liTotalBytes, liTotalFreeBytes;

		if (GetDiskFreeSpaceEx(lpcwstrDriver, &liFreeBytesAvailable, &liTotalBytes, &liTotalFreeBytes)) {
			QString use = QString::number((double)(liTotalBytes.QuadPart - liTotalFreeBytes.QuadPart) / GB, 'f', 1);
			use += "G";
			QString free = QString::number((double) liTotalFreeBytes.QuadPart / GB, 'f', 1);
			free += "G";
			QString all = QString::number((double) liTotalBytes.QuadPart / GB, 'f', 1);
			all += "G";
			int percent = 100 - ((double)liTotalFreeBytes.QuadPart / liTotalBytes.QuadPart) * 100;

			InsertSize(dirName, use, free, all, percent);
		}
	}

#else
	process->start("df -h");
#endif
}

void ShowDeviceSize::ReadData()
{
	while (!process->atEnd()) {
		QString result = QLatin1String(process->readLine());
#ifdef __arm__

		if (result.startsWith("/dev/root")) {
            CheckSize(result, QString::fromLocal8Bit("本地存储"));
		} else if (result.startsWith("/dev/mmcblk1p1")) {
            CheckSize(result, QString::fromLocal8Bit("SD卡"));
		} else if (result.startsWith("/dev/sda1")) {
            CheckSize(result, QString::fromLocal8Bit("U盘"));
		}

#else

		if (result.startsWith("/dev/sda")) {
			CheckSize(result, "");
		}

#endif
	}
}

void ShowDeviceSize::CheckSize(QString result, QString name)
{
	QString dev, use, free, all;
	int percent = 0;
	QStringList list = result.split(" ");
	int index = 0;

	for (int i = 0; i < list.count(); i++) {
		QString s = list.at(i).trimmed();

		if (s == "") {
			continue;
		}

		index++;

		if (index == 1) {
			dev = s;
		} else if (index == 2) {
			all = s;
		} else if (index == 3) {
			use = s;
		} else if (index == 4) {
			free = s;
		} else if (index == 5) {
			percent = s.left(s.length() - 1).toInt();
			break;
		}
	}

	if (name.length() > 0) {
		dev = name;
	}

	InsertSize(dev, use, free, all, percent);
}

void ShowDeviceSize::InsertSize(QString name, QString use, QString free, QString all, int percent)
{
	int row = this->tableWidget->rowCount();
	this->tableWidget->insertRow(row);
	this->tableWidget->setRowHeight(row, 25);

	QTableWidgetItem *itemname = new QTableWidgetItem(name);
	QTableWidgetItem *itemuse = new QTableWidgetItem(use);
	itemuse->setTextAlignment(Qt::AlignCenter);
	QTableWidgetItem *itemfree = new QTableWidgetItem(free);
	itemfree->setTextAlignment(Qt::AlignCenter);
	QTableWidgetItem *itemall = new QTableWidgetItem(all);
	itemall->setTextAlignment(Qt::AlignCenter);

	this->tableWidget->setItem(row, 0, itemname);
	this->tableWidget->setItem(row, 1, itemuse);
	this->tableWidget->setItem(row, 2, itemfree);
	this->tableWidget->setItem(row, 3, itemall);

	QProgressBar *bar = new QProgressBar;
	bar->setRange(0, 100);
	bar->setValue(percent);

    QString qss = "QProgressBar{background:#FFFFFF;border-width:0px;border-radius:0px;text-align:center;}";

	if (percent < 50) {
		qss += "QProgressBar{color:#000000;}QProgressBar::chunk{background:#66CD00;}";
	} else if (percent < 90) {
		qss += "QProgressBar{color:#FFFFFF;}QProgressBar::chunk{background:#3C8CDC;}";
	} else {
		qss += "QProgressBar{color:#FFFFFF;}QProgressBar::chunk{background:#D71345;}";
	}

	bar->setStyleSheet(qss);
	this->tableWidget->setCellWidget(row, 4, bar);
}
