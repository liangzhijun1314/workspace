#include "stdafx.h"

#include <QtCore/QSignalMapper>

#include <QtGui/QPalette>

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>

#include "BasicWidget.h"

#include "PlotWidget.h"

struct QuotaItemPrivate
{
	QCP::QuotaLineType m_eID;
	QToolButton * m_pButton = nullptr;
	QLabel * m_pTextValue = nullptr;
};

QuotaItem::QuotaItem(QCP::QuotaLineType id, double value, QWidget * parent /*= nullptr*/)
	: QWidget(parent)
	, d_ptr(new QuotaItemPrivate)
{
	d_ptr->m_eID = id;

	setFixedWidth(100);

	QHBoxLayout * mainLayout = new QHBoxLayout;
	d_ptr->m_pButton = new QToolButton;
	d_ptr->m_pTextValue = new QLabel;

	connect(d_ptr->m_pButton, &QToolButton::clicked, this, [this]{
		d_ptr->m_pTextValue->setVisible(d_ptr->m_pTextValue->isVisible() == false);
		emit ItemClicked(d_ptr->m_eID, d_ptr->m_pTextValue->isVisible());
	});

	d_ptr->m_pButton->setText(QString::number(id) + QStringLiteral(":"));
	SetValue(value);

	mainLayout->setMargin(0);
	mainLayout->setSpacing(0);

	mainLayout->addWidget(d_ptr->m_pButton);
	mainLayout->addWidget(d_ptr->m_pTextValue);
	mainLayout->addStretch(1);

	SetTextColor(Qt::red);

	setLayout(mainLayout);
}

QuotaItem::~QuotaItem()
{

}

const QString & QuotaItem::QuotaName() const
{
	return d_ptr->m_pButton->text().remove(QStringLiteral(":"));
}

void QuotaItem::SetValue(double value)
{
	d_ptr->m_pTextValue->setText(QString::number(value, 'f', 3));
}

double QuotaItem::GetValue() const
{
	return d_ptr->m_pTextValue->text().toDouble();
}

void QuotaItem::SetTextColor(const QColor & color)
{
	QPalette palette = d_ptr->m_pButton->palette();
	palette.setColor(QPalette::ButtonText, color);
	d_ptr->m_pButton->setPalette(palette);

	palette = d_ptr->m_pTextValue->palette();
	palette.setColor(QPalette::WindowText, color);
	d_ptr->m_pTextValue->setPalette(palette);
}

const QColor &  QuotaItem::GetTextColor() const
{
	return d_ptr->m_pTextValue->palette().color(QPalette::WindowText);
}

struct PlotWidgetPrivate
{
	QCP::WindowFlags m_Flags = QCP::NOTHING;
	QLabel * m_pTitleName = nullptr;
	QLabel * m_pAvargeLineName = nullptr;
	QToolButton * m_pRefrush = nullptr;
	QToolButton * m_pZoomout = nullptr;
	QToolButton * m_pZoomin = nullptr;
	QToolButton * m_pSetup = nullptr;
	QSignalMapper * m_pBarClickedMap = nullptr;
	QVBoxLayout * m_pMainLayout = nullptr;//主窗口布局
	QHBoxLayout * m_pTitleLayout = nullptr;//标题栏布局
	QHBoxLayout * m_pQuotaLayout = nullptr;//标题栏指标布局
	QWidget * m_pContentWidget = nullptr;

	std::map<std::wstring, QuotaItem *> m_QuotaItems;
	std::function<void(QCP::WindowFlag flag)> * m_pToolbarCallback = nullptr;
};

PlotWidget::PlotWidget(QWidget * parent, QCP::WindowFlags flags)
	: QWidget(parent)
	, d_ptr(new PlotWidgetPrivate)
{
	d_ptr->m_Flags = flags;
	InitializeUI();
}

PlotWidget::~PlotWidget()
{

}

void PlotWidget::SetTitleName(const QString & name)
{
	if (d_ptr->m_pTitleName)
	{
		d_ptr->m_pTitleName->setText(name);
	}
}

void PlotWidget::SetAvarageName(const QString & name)
{
	if (d_ptr->m_pAvargeLineName)
	{
		d_ptr->m_pAvargeLineName->setText(name);
	}
}

void PlotWidget::SetContentWidget(BasicWidget * widget)
{
	if (d_ptr->m_pContentWidget)
	{
		delete d_ptr->m_pMainLayout->takeAt(d_ptr->m_pMainLayout->count() - 1);
		delete  d_ptr->m_pContentWidget;
	}

	widget->SetWrapWidget(this);
	d_ptr->m_pContentWidget = widget;

	SetupContentWidget();
}

void PlotWidget::RegisterToolBarCallback(std::function<void(QCP::WindowFlag flag)> & onclicked)
{
	d_ptr->m_pToolbarCallback = &onclicked;
}

QuotaItem * PlotWidget::AddQuota(QCP::QuotaLineType id, double value)
{
	QuotaItem * item = nullptr;
	std::wstring wstrQuota;
	auto iter = d_ptr->m_QuotaItems.find(wstrQuota);
	if (iter == d_ptr->m_QuotaItems.end())
	{
		//标题栏新增指标显示
		item = new QuotaItem(id, value);
		connect(item, &QuotaItem::ItemClicked, this, &PlotWidget::ShowQuotaSignal);

		d_ptr->m_pQuotaLayout->addWidget(item);
		d_ptr->m_QuotaItems[wstrQuota] = item;

		emit AddQuotaSignal(id);
	}
	else
	{
		item = iter->second;
		iter->second->SetValue(value);
	}

	return item;
}

bool PlotWidget::RemoveQuota(QCP::QuotaLineType id)
{
	std::wstring wstrQuota;
	auto iter = d_ptr->m_QuotaItems.find(wstrQuota);
	if (iter != d_ptr->m_QuotaItems.end())
	{
		d_ptr->m_QuotaItems.erase(iter);
		emit RemoveQuotaSignal(id);
	}

	return false;
}

bool PlotWidget::SetQuotaValue(QCP::QuotaLineType id, double value)
{
	std::wstring wstrQuota;
	auto iter = d_ptr->m_QuotaItems.find(wstrQuota);
	if (iter == d_ptr->m_QuotaItems.end())
	{
		iter->second->SetValue(value);
		return true;
	}
	else
	{
		//不存在
		return false;
	}
}

void PlotWidget::ToobarButtonClicked(int index)
{
	QCP::WindowFlag flag = (QCP::WindowFlag)index;
	if (d_ptr->m_Flags.testFlag(flag))
	{
		if (d_ptr->m_pToolbarCallback)
		{
			(*d_ptr->m_pToolbarCallback)(flag);
		}

		switch (flag)
		{
		case QCP::TITLE:
			break;
		case QCP::ZOOM_OUT:
			break;
		case QCP::ZOOM_IN:
			break;
		case QCP::SETUP:
			break;
		case QCP::FRUSH:
			break;
		case QCP::NOTHING:
			break;
		default:
			break;
		}
	}
}

QColor PlotWidget::GetQuotaColor(QCP::QuotaLineType id) const
{
	QColor color;
	std::wstring wstrQuota;
	auto iter = d_ptr->m_QuotaItems.find(wstrQuota);
	if (iter == d_ptr->m_QuotaItems.end())
	{
		color = iter->second->GetTextColor();
	}
	
	return color;
}

void PlotWidget::InitializeUI()
{
	d_ptr->m_pMainLayout = new QVBoxLayout;
	d_ptr->m_pMainLayout->setMargin(0);
	d_ptr->m_pMainLayout->setSpacing(0);

	//标题栏
	SetupTitile();
	
	//中心窗口
	SetupContentWidget();

	setLayout(d_ptr->m_pMainLayout);
}

void PlotWidget::SetupTitile()
{
	QWidget * titleWidget = new QWidget;
	titleWidget->setBackgroundRole(QPalette::HighlightedText);

	d_ptr->m_pTitleLayout = new QHBoxLayout;
	d_ptr->m_pQuotaLayout = new QHBoxLayout;

	d_ptr->m_pTitleLayout->setMargin(0);
	d_ptr->m_pTitleLayout->setSpacing(0);
	d_ptr->m_pQuotaLayout->setMargin(0);
	d_ptr->m_pQuotaLayout->setSpacing(0);

	d_ptr->m_pBarClickedMap = new QSignalMapper;

	if (d_ptr->m_Flags.testFlag(QCP::TITLE))
	{
		d_ptr->m_pTitleName = new QLabel;
		d_ptr->m_pTitleName->setFixedSize(QSize(18, 18));
		d_ptr->m_pTitleLayout->addWidget(d_ptr->m_pTitleName);
	}

	if (d_ptr->m_Flags.testFlag(QCP::AVARGE))
	{
		d_ptr->m_pAvargeLineName = new QLabel;
		d_ptr->m_pAvargeLineName->setFixedSize(QSize(18, 18));
		d_ptr->m_pTitleLayout->addWidget(d_ptr->m_pTitleName);
	}

	d_ptr->m_pTitleLayout->addLayout(d_ptr->m_pQuotaLayout);
	d_ptr->m_pTitleLayout->addStretch(1);
	if (d_ptr->m_Flags.testFlag(QCP::FRUSH))
	{
		d_ptr->m_pRefrush = new QToolButton;
		connect(d_ptr->m_pRefrush, &QToolButton::clicked, d_ptr->m_pBarClickedMap, static_cast<void (QSignalMapper:: *)()>(&QSignalMapper::map));
		d_ptr->m_pBarClickedMap->setMapping(d_ptr->m_pRefrush, QCP::FRUSH);
		d_ptr->m_pRefrush->setFixedSize(QSize(18, 18));
		d_ptr->m_pTitleLayout->addWidget(d_ptr->m_pRefrush);
	}
	if (d_ptr->m_Flags.testFlag(QCP::ZOOM_OUT))
	{
		d_ptr->m_pZoomout = new QToolButton;
		connect(d_ptr->m_pZoomout, &QToolButton::clicked, d_ptr->m_pBarClickedMap, static_cast<void (QSignalMapper:: *)()>(&QSignalMapper::map));
		d_ptr->m_pBarClickedMap->setMapping(d_ptr->m_pZoomout, QCP::ZOOM_OUT);
		d_ptr->m_pZoomout->setFixedSize(QSize(18, 18));
		d_ptr->m_pTitleLayout->addWidget(d_ptr->m_pZoomout);
	}
	if (d_ptr->m_Flags.testFlag(QCP::ZOOM_IN))
	{
		d_ptr->m_pZoomin = new QToolButton;
		connect(d_ptr->m_pZoomin, &QToolButton::clicked, d_ptr->m_pBarClickedMap, static_cast<void (QSignalMapper:: *)()>(&QSignalMapper::map));
		d_ptr->m_pBarClickedMap->setMapping(d_ptr->m_pZoomin, QCP::ZOOM_IN);
		d_ptr->m_pZoomin->setFixedSize(QSize(18, 18));
		d_ptr->m_pTitleLayout->addWidget(d_ptr->m_pZoomin);
	}
	if (d_ptr->m_Flags.testFlag(QCP::SETUP))
	{
		d_ptr->m_pSetup = new QToolButton;
		connect(d_ptr->m_pSetup, &QToolButton::clicked, d_ptr->m_pBarClickedMap, static_cast<void (QSignalMapper:: *)()>(&QSignalMapper::map));
		d_ptr->m_pBarClickedMap->setMapping(d_ptr->m_pSetup, QCP::SETUP);
		d_ptr->m_pSetup->setFixedSize(QSize(18, 18));
		d_ptr->m_pTitleLayout->addWidget(d_ptr->m_pSetup);
	}

	connect(d_ptr->m_pBarClickedMap, static_cast<void (QSignalMapper:: *)(int)>(&QSignalMapper::mapped),
		this, static_cast<void (PlotWidget:: *)(int)>(&PlotWidget::ToobarButtonClicked));

	titleWidget->setLayout(d_ptr->m_pTitleLayout);
	d_ptr->m_pMainLayout->addWidget(titleWidget);
}

void PlotWidget::SetupContentWidget()
{
	if (d_ptr->m_pContentWidget == nullptr)
	{
		d_ptr->m_pContentWidget = new QWidget(this);
	}
	d_ptr->m_pMainLayout->addWidget(d_ptr->m_pContentWidget, 1);
}
