#include "frmshowapi.h"
#include "ui_frmshowapi.h"
//#include "head.h"
#include "showcpumemory.h"
#include "showdatetime.h"
#include "showdevicesize.h"

frmShowAPI::frmShowAPI(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::frmShowAPI)
{
	ui->setupUi(this);
	this->InitForm();
	this->ChangeColor();
}

frmShowAPI::~frmShowAPI()
{
	delete ui;
}

void frmShowAPI::InitForm()
{
	ShowDateTime *showDateTime = new ShowDateTime(this);
	showDateTime->SetLab(ui->labDateTime, ui->labLive);
	showDateTime->SetLcdNumber(ui->lcdNumber);
	showDateTime->Start(1000);

	ShowCPUMemory *showCPUMemory = new ShowCPUMemory(this);
	showCPUMemory->SetLab(ui->labCPUMemory);
#ifdef __arm__
	showCPUMemory->Start(3000);
#else
	showCPUMemory->Start(1000);
#endif

	ShowDeviceSize::Instance()->SetTableWidget(ui->tableWidget);
	ShowDeviceSize::Instance()->Load();

	int icoWidth = 100;
	int icoHeight = 20;
	ui->cboxColor->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	colorList = QColor::colorNames();

	foreach (QString color, colorList) {
		QPixmap pix(QSize(icoWidth, icoHeight));
		pix.fill(color);
		ui->cboxColor->addItem(QIcon(pix), color);
		ui->cboxColor->setIconSize(QSize(icoWidth, icoHeight));
	}

	connect(ui->cboxColor, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeColor()));
}

void frmShowAPI::ChangeColor()
{
	QString colorName = colorList.at(ui->cboxColor->currentIndex());
    QString qss = QString("QLCDNumber{background-color: rgb(0, 0, 0);color:%1;}").arg(colorName);
	ui->lcdNumber->setStyleSheet(qss);
}
