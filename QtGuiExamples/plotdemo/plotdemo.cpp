//#include "stdafx.h"

//#include "BasicPlot.h"
//#include "FinancialPlot.h"

#include "plotdemo.h"
#include "QCustomplot.h"
//#include "FinancialWidget.h"
#include "TimeSharingTrendWidget.h"
#include "TimeSharingTrendPlot.h"

plotdemo::plotdemo(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    InitalizeTable();
    InitalizeBar();
    InitalizeGraph();
    InitalizeScatter();
    InitalizeScatter2();
    InitalizeVersatility();
    InitalizeColorMap();
    InitalizeScatter3();
    InitalizeGraph2();
    InitalizeMultipleAxes();
    InitalizeLogarithmicAxis();
    InitalizeLine();
    InitalizeDateAxis();
    InitalizeParametricCurves();
    InitalizeStackedBar();
    InitalizeStatisticalBox();
    InitalizeInteraction();
    InitalizeItem();
    IinitalizeAdvanceAxes();
    IinitalizeFinancial();
    Test();
}

plotdemo::~plotdemo()
{

}

void plotdemo::InitalizeBar()
{
    QVector<QString> labels(5);
    QVector<double> values(5);
    for (int i = 0; i < 5; ++i)
        labels[i] = QString("MAC") + ('0' + i);
    values[0] = (10.05);
    values[1] = 23;
    values[2] = 12;
    values[3] = 19.3;
    values[4] = 20;

    QCPBars * bars = new QCPBars(ui.widget->xAxis, ui.widget->yAxis);
    QVector<double> index(5);
    for (int i = 0; i < 5; ++i)
    {
        index[i] = i;
    }
    bars->setData(index, values);

// 	ui.widget->xAxis->setAutoTicks(false);
// 	ui.widget->xAxis->setAutoTickLabels(false);
// 	ui.widget->xAxis->setAutoTickStep(false);

//	ui.widget->addPlottable(bars);
    ui.widget->rescaleAxes();

    double wid = ui.widget->xAxis->range().upper - ui.widget->xAxis->range().lower;
    double cl = bars->width() + (1.0*wid - bars->width() * 5) / 4;

    QVector<double> coor;
    for (int i = 0; i < 5; ++i)
    {
        coor.append(ui.widget->xAxis->range().lower + i * cl + bars->width() / 2);
    }
// 	ui.widget->xAxis->setTickVector(coor);
// 	ui.widget->xAxis->setTickVectorLabels(labels);

    ui.widget->replot();
}

void plotdemo::InitalizeTable()
{
//    QStringList horizontalHeader;
//    horizontalHeader << tr("名称");
//    horizontalHeader << tr("性别");
//    horizontalHeader << tr("进度");
//    ui.widget_tableWidget->setHorizontalHeaderLabels(horizontalHeader);
//    ui.widget_tableWidget->setSortingEnabled(true);

//    RLProgressBarDelegate * progressDelegate =
//    new RLProgressBarDelegate(ui.widget_tableWidget);
//    progressDelegate->SetColumn(2);
//    ui.widget_tableWidget->setItemDelegateForColumn(2, progressDelegate);
//    for (int i = 1; i <= 20; ++i)
//    {
//    QStringList data;
//    data << QString::number(i);
//    data << QStringLiteral("男");
//    data << QString::number(90);
//    ui.widget_tableWidget->AddRow(data);
//    }

//    ui.widget_tableWidget->setStyleSheet("QHeaderView::section:horizontal"
//        "{color: red;font: bold 24px '微软雅黑';"
//        "height:50;	border-style: none;border-left: 1 solid #ecedef;"
//        "border-right: 1 solid #b1b1b5;"
//        "background-color: qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #f4f4f6,stop:1 #ceced6);}"
//        "QTableView{background-color: rgb(250, 250, 115);"
//        "alternate-background-color: rgb(141, 163, 215);"
//        "selection-color: red;selection-background-color: #595a5c;}");
}

void plotdemo::InitalizeGraph()
{
    ui.widget_3->setAcceptDrops(false);

    // add two new graphs and set their look:
    ui.widget_3->addGraph();
    ui.widget_3->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui.widget_3->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    ui.widget_3->addGraph();
    ui.widget_3->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(250), y0(250), y1(250);
    for (int i = 0; i < 250; ++i)
    {
        x[i] = i;
        y0[i] = qExp(-i / 150.0)*qCos(i / 10.0); // exponentially decaying cosine
        y1[i] = qExp(-i / 150.0);              // exponential envelope
    }
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui.widget_3->xAxis2->setVisible(true);
    ui.widget_3->xAxis2->setTickLabels(false);
    ui.widget_3->yAxis2->setVisible(true);
    ui.widget_3->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui.widget_3->xAxis, SIGNAL(rangeChanged(QCPRange)), ui.widget_3->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui.widget_3->yAxis, SIGNAL(rangeChanged(QCPRange)), ui.widget_3->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui.widget_3->graph(0)->setData(x, y0);
    ui.widget_3->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui.widget_3->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    ui.widget_3->graph(1)->rescaleAxes(true);
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui.widget_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);

}

void plotdemo::InitalizeScatter()
{
    ui.widget_4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom); // 可以缩放
    ui.widget_4->legend->setVisible(true);
    ui.widget_4->legend->setFont(QFont("Helvetica", 9));
    // set locale to english, so we get english decimal separator:
    ui.widget_4->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    // add confidence band graphs:
    ui.widget_4->addGraph();
    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setWidth(1);
    pen.setColor(QColor(180, 180, 180));
    ui.widget_4->graph(0)->setName("Confidence Band 68%");
    ui.widget_4->graph(0)->setPen(pen);
    ui.widget_4->graph(0)->setBrush(QBrush(QColor(255, 50, 30, 20)));
    ui.widget_4->addGraph();
    ui.widget_4->legend->removeItem(ui.widget_4->legend->itemCount() - 1); // don't show two confidence band graphs in legend
    ui.widget_4->graph(1)->setPen(pen);
    ui.widget_4->graph(0)->setChannelFillGraph(ui.widget_4->graph(1));
    // add theory curve graph:
    ui.widget_4->addGraph();
    pen.setStyle(Qt::DashLine);
    pen.setWidth(2);
    pen.setColor(Qt::red);
    ui.widget_4->graph(2)->setPen(pen);
    ui.widget_4->graph(2)->setName("Theory Curve");
    // add data point graph:
    ui.widget_4->addGraph();
    ui.widget_4->graph(3)->setPen(QPen(Qt::blue));
    ui.widget_4->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui.widget_4->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
// 	ui.widget_4->graph(3)->setErrorType(QCPGraph::etValue);
// 	ui.widget_4->graph(3)->setErrorPen(QPen(QColor(180, 180, 180)));
    ui.widget_4->graph(3)->setName("Measurement");

    // generate ideal sinc curve data and some randomly perturbed data for scatter plot:
    QVector<double> x0(250), y0(250);
    QVector<double> yConfUpper(250), yConfLower(250);
    for (int i = 0; i < 250; ++i)
    {
        x0[i] = (i / 249.0 - 0.5) * 30 + 0.01; // by adding a small offset we make sure not do divide by zero in next code line
        y0[i] = qSin(x0[i]) / x0[i]; // sinc function
        yConfUpper[i] = y0[i] + 0.15;
        yConfLower[i] = y0[i] - 0.15;
        x0[i] *= 1000;
    }
    QVector<double> x1(50), y1(50), y1err(50);
    for (int i = 0; i < 50; ++i)
    {
        // generate a gaussian distributed random number:
        double tmp1 = rand() / (double)RAND_MAX;
        double tmp2 = rand() / (double)RAND_MAX;
        double r = qSqrt(-2 * qLn(tmp1))*qCos(2 * M_PI*tmp2); // box-muller transform for gaussian distribution
        // set y1 to value of y0 plus a random gaussian pertubation:
        x1[i] = (i / 50.0 - 0.5) * 30 + 0.25;
        y1[i] = qSin(x1[i]) / x1[i] + r*0.15;
        x1[i] *= 1000;
        y1err[i] = 0.15;
    }
    // pass data to graphs and let QCustomPlot determine the axes ranges so the whole thing is visible:
    ui.widget_4->graph(0)->setData(x0, yConfUpper);
    ui.widget_4->graph(1)->setData(x0, yConfLower);
    ui.widget_4->graph(2)->setData(x0, y0);
//	ui.widget_4->graph(3)->setDataValueError(x1, y1, y1err);
    ui.widget_4->graph(2)->rescaleAxes();
    ui.widget_4->graph(3)->rescaleAxes(true);
    // setup look of bottom tick labels:
    ui.widget_4->xAxis->setTickLabelRotation(30);
//	ui.widget_4->xAxis->setAutoTickCount(9);
    ui.widget_4->xAxis->setNumberFormat("ebc");
    ui.widget_4->xAxis->setNumberPrecision(1);
    ui.widget_4->xAxis->moveRange(-10);
    // make top right axes clones of bottom left axes. Looks prettier:
//	ui.widget_4->axisRect()->setupFullAxesBox();
}

void plotdemo::InitalizeScatter2()
{
    ui.widget_5->legend->setVisible(true);
    ui.widget_5->legend->setFont(QFont("Helvetica", 9));
    ui.widget_5->legend->setRowSpacing(-3);
    QVector<QCPScatterStyle::ScatterShape> shapes;
    shapes << QCPScatterStyle::ssCross;
    shapes << QCPScatterStyle::ssPlus;
    shapes << QCPScatterStyle::ssCircle;
    shapes << QCPScatterStyle::ssDisc;
    shapes << QCPScatterStyle::ssSquare;
    shapes << QCPScatterStyle::ssDiamond;
    shapes << QCPScatterStyle::ssStar;
    shapes << QCPScatterStyle::ssTriangle;
    shapes << QCPScatterStyle::ssTriangleInverted;
    shapes << QCPScatterStyle::ssCrossSquare;
    shapes << QCPScatterStyle::ssPlusSquare;
    shapes << QCPScatterStyle::ssCrossCircle;
    shapes << QCPScatterStyle::ssPlusCircle;
    shapes << QCPScatterStyle::ssPeace;
    shapes << QCPScatterStyle::ssCustom;

    QPen pen;
    // add graphs with different scatter styles:
    for (int i = 0; i < shapes.size(); ++i)
    {
        ui.widget_5->addGraph();
        pen.setColor(QColor(qSin(i*0.3) * 100 + 100, qSin(i*0.6 + 0.7) * 100 + 100, qSin(i*0.4 + 0.6) * 100 + 100));
        // generate data:
        QVector<double> x(10), y(10);
        for (int k = 0; k < 10; ++k)
        {
            x[k] = k / 10.0 * 4 * 3.14 + 0.01;
            y[k] = 7 * qSin(x[k]) / x[k] + (shapes.size() - i) * 5;
        }
        ui.widget_5->graph()->setData(x, y);
        ui.widget_5->graph()->rescaleAxes(true);
        ui.widget_5->graph()->setPen(pen);
//        ui.widget_5->graph()->setName(QCPScatterStyle::staticMetaObject.enumerator(QCPScatterStyle::staticMetaObject.indexOfEnumerator("ScatterShape")).valueToKey(shapes.at(i)));
        ui.widget_5->graph()->setLineStyle(QCPGraph::lsLine);
        // set scatter style:
        if (shapes.at(i) != QCPScatterStyle::ssCustom)
        {
            ui.widget_5->graph()->setScatterStyle(QCPScatterStyle(shapes.at(i), 10));
        }
        else
        {
            QPainterPath customScatterPath;
            for (int i = 0; i < 3; ++i)
                customScatterPath.cubicTo(qCos(2 * M_PI*i / 3.0) * 9, qSin(2 * M_PI*i / 3.0) * 9, qCos(2 * M_PI*(i + 0.9) / 3.0) * 9, qSin(2 * M_PI*(i + 0.9) / 3.0) * 9, 0, 0);
            ui.widget_5->graph()->setScatterStyle(QCPScatterStyle(customScatterPath, QPen(Qt::black, 0), QColor(40, 70, 255, 50), 10));
        }
    }
    // set blank axis lines:
    ui.widget_5->rescaleAxes();
    ui.widget_5->xAxis->setTicks(false);
    ui.widget_5->yAxis->setTicks(false);
    ui.widget_5->xAxis->setTickLabels(false);
    ui.widget_5->yAxis->setTickLabels(false);
    // make top right axes clones of bottom left axes:
    ui.widget_5->axisRect()->setupFullAxesBox();
}

void plotdemo::InitalizeVersatility()
{
    // prepare data:
    QVector<double> x1(20), y1(20);
    QVector<double> x2(10), y2(10);
    QVector<double> x3(20), y3(20);
    QVector<double> x4(20), y4(20);
    for (int i = 0; i < x1.size(); ++i)
    {
        x1[i] = i / (double)x1.size() * 10;
        y1[i] = qCos(x1[i] * 0.8 + qSin(x1[i] * 0.16 + 1.0))*qSin(x1[i] * 0.54) + 1.4;
    }
    for (int i = 0; i < x2.size(); ++i)
    {
        x2[i] = i / (double)x2.size() * 10;
        y2[i] = qCos(x2[i] * 0.85 + qSin(x2[i] * 0.165 + 1.1))*qSin(x2[i] * 0.50) + 1.7;
    }
    for (int i = 0; i < x3.size(); ++i)
    {
        x3[i] = i / (double)x3.size() * 10;
        y3[i] = 0.05 + 3 * (0.5 + qCos(x3[i] * x3[i] * 0.2 + 2)*0.5) / (double)(x3[i] + 0.7) + qrand() / (double)RAND_MAX*0.01;
    }
    for (int i = 0; i < x4.size(); ++i)
    {
        x4[i] = x3[i];
        y4[i] = (0.5 - y3[i]) + ((x4[i] - 2)*(x4[i] - 2)*0.02);
    }

    // create and configure plottables:
    QCPGraph *graph1 = ui.widget_6->addGraph();
    graph1->setData(x1, y1);
//	graph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
    graph1->setPen(QPen(QColor(120, 120, 120), 2));

    QCPGraph *graph2 = ui.widget_6->addGraph();
    graph2->setData(x2, y2);
//	graph2->setPen(Qt::NoPen);
    graph2->setBrush(QColor(200, 200, 200, 20));
    graph2->setChannelFillGraph(graph1);

    QCPBars *bars1 = new QCPBars(ui.widget_6->xAxis, ui.widget_6->yAxis);
//	ui.widget_6->addPlottable(bars1);
    bars1->setWidth(9 / (double)x3.size());
    bars1->setData(x3, y3);
//	bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(10, 140, 70, 160));

    QCPBars *bars2 = new QCPBars(ui.widget_6->xAxis, ui.widget_6->yAxis);
//	ui.widget_6->addPlottable(bars2);
    bars2->setWidth(9 / (double)x4.size());
    bars2->setData(x4, y4);
//	bars2->setPen(Qt::NoPen);
    bars2->setBrush(QColor(10, 100, 50, 70));
    bars2->moveAbove(bars1);

    // move bars above graphs and grid below bars:
    ui.widget_6->addLayer("abovemain", ui.widget_6->layer("main"), QCustomPlot::limAbove);
    ui.widget_6->addLayer("belowmain", ui.widget_6->layer("main"), QCustomPlot::limBelow);
    graph1->setLayer("abovemain");
    ui.widget_6->xAxis->grid()->setLayer("abovemain");
    ui.widget_6->yAxis->grid()->setLayer("belowmain");

// 	ui.widget_6->xAxis->setAutoTickLabels(false);
// 	ui.widget_6->xAxis->setAutoSubTicks(false);
    // set some pens, brushes and backgrounds:
    ui.widget_6->xAxis->setBasePen(QPen(Qt::red, 1));
    ui.widget_6->yAxis->setBasePen(QPen(Qt::red, 1));
    ui.widget_6->xAxis->setTickPen(QPen(Qt::black, 1));
    ui.widget_6->yAxis->setTickPen(QPen(Qt::black, 1));
    ui.widget_6->xAxis->setSubTickPen(QPen(Qt::yellow, 1));
    ui.widget_6->yAxis->setSubTickPen(QPen(Qt::black, 1));
    ui.widget_6->xAxis->setTickLabelColor(Qt::black);
    ui.widget_6->yAxis->setTickLabelColor(Qt::black);
    ui.widget_6->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui.widget_6->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui.widget_6->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui.widget_6->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui.widget_6->xAxis->grid()->setSubGridVisible(true);
    ui.widget_6->yAxis->grid()->setSubGridVisible(true);
    ui.widget_6->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui.widget_6->yAxis->grid()->setZeroLinePen(Qt::NoPen);

//	ui.widget_6->xAxis->setSubTickCount(5);

    ui.widget_6->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui.widget_6->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui.widget_6->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    ui.widget_6->axisRect()->setBackground(axisRectGradient);

    ui.widget_6->rescaleAxes();
    ui.widget_6->yAxis->setRange(0, 2);
}

void plotdemo::InitalizeColorMap()
{
    // configure axis rect:
    ui.widget_7->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui.widget_7->axisRect()->setupFullAxesBox(true);
    ui.widget_7->xAxis->setLabel("x");
    ui.widget_7->yAxis->setLabel("y");

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(ui.widget_7->xAxis, ui.widget_7->yAxis);
//	ui.widget_7->addPlottable(colorMap);
    int nx = 200;
    int ny = 200;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(-4, 4), QCPRange(-4, 4)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double x, y, z;
    for (int xIndex = 0; xIndex < nx; ++xIndex)
    {
        for (int yIndex = 0; yIndex < ny; ++yIndex)
        {
            colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
            double r = 3 * qSqrt(x*x + y*y) + 1e-2;
            z = 2 * x*(qCos(r + 2) / r - qSin(r + 2) / r); // the B field strength of dipole radiation (modulo physical constants)
            colorMap->data()->setCell(xIndex, yIndex, z);
        }
    }

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(ui.widget_7);
    ui.widget_7->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("Magnetic Field Strength");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpPolar);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui.widget_7);
    ui.widget_7->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    ui.widget_7->rescaleAxes();
}

void plotdemo::InitalizeScatter3()
{
    ui.widget_8->axisRect()->setBackground(/*QPixmap("./solarpanels.jpg")*/Qt::gray);
    ui.widget_8->addGraph();
    ui.widget_8->graph()->setLineStyle(QCPGraph::lsLine);
    QPen pen;
    pen.setColor(QColor(255, 200, 20, 200));
    pen.setStyle(Qt::DashLine);
    pen.setWidthF(2.5);
    ui.widget_8->graph()->setPen(pen);
    ui.widget_8->graph()->setBrush(QBrush(QColor(255, 200, 20, 70)));
    ui.widget_8->graph()->setScatterStyle(QCPScatterStyle(/*QPixmap("./sun.png")*/QCPScatterStyle::ssCross));
    // set graph name, will show up in legend next to icon:
    ui.widget_8->graph()->setName("Data from Photovoltaic\nenergy barometer 2011");
    // set data:
    QVector<double> year, value;
    year << 2005 << 2006 << 2007 << 2008 << 2009 << 2010;
    value << 2.17 << 3.42 << 4.94 << 10.38 << 15.86 << 29.33;
    ui.widget_8->graph()->setData(year, value);

    // set title of plot:
    ui.widget_8->plotLayout()->insertRow(0);
//	ui.widget_8->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui.widget_8, "Regenerative Energies"));
    // set a fixed tick-step to one tick per year value:
// 	ui.widget_8->xAxis->setAutoTickStep(false);
// 	ui.widget_8->xAxis->setTickStep(1);
// 	ui.widget_8->xAxis->setSubTickCount(3);
    // other axis configurations:
    ui.widget_8->xAxis->setLabel("Year");
    ui.widget_8->yAxis->setLabel("Installed Gigawatts of\nphotovoltaic in the European Union");
    ui.widget_8->xAxis2->setVisible(true);
    ui.widget_8->yAxis2->setVisible(true);
    ui.widget_8->xAxis2->setTickLabels(false);
    ui.widget_8->yAxis2->setTickLabels(false);
    ui.widget_8->xAxis2->setTicks(false);
    ui.widget_8->yAxis2->setTicks(false);
// 	ui.widget_8->xAxis2->setSubTickCount(0);
// 	ui.widget_8->yAxis2->setSubTickCount(0);
    ui.widget_8->xAxis->setRange(2004.5, 2010.5);
    ui.widget_8->yAxis->setRange(0, 30);
    // setup legend:
    ui.widget_8->legend->setFont(QFont(font().family(), 7));
    ui.widget_8->legend->setIconSize(50, 20);
    ui.widget_8->legend->setVisible(true);
}

void plotdemo::InitalizeGraph2()
{
    ui.widget_9->addGraph(); // blue line
    ui.widget_9->graph(0)->setPen(QPen(Qt::blue));
    ui.widget_9->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    ui.widget_9->graph(0)->setAntialiasedFill(false);
    ui.widget_9->addGraph(); // red line
    ui.widget_9->graph(1)->setPen(QPen(Qt::red));
    ui.widget_9->graph(0)->setChannelFillGraph(ui.widget_9->graph(1));

    ui.widget_9->addGraph(); // blue dot
    ui.widget_9->graph(2)->setPen(QPen(Qt::blue));
    ui.widget_9->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui.widget_9->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui.widget_9->addGraph(); // red dot
    ui.widget_9->graph(3)->setPen(QPen(Qt::red));
    ui.widget_9->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui.widget_9->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

// 	ui.widget_9->xAxis->setTickLabelType(QCPAxis::ltDateTime);
// 	ui.widget_9->xAxis->setDateTimeFormat("hh:mm:ss");
// 	ui.widget_9->xAxis->setAutoTickStep(false);
// 	ui.widget_9->xAxis->setTickStep(2);
    ui.widget_9->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui.widget_9->xAxis, SIGNAL(rangeChanged(QCPRange)), ui.widget_9->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui.widget_9->yAxis, SIGNAL(rangeChanged(QCPRange)), ui.widget_9->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    QTimer * dataTimer = new QTimer(this);
    connect(dataTimer, &QTimer::timeout, this, [this]{
        // calculate two new data points:
        double key = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
        static double lastPointKey = 0;
        if (key - lastPointKey > 0.01) // at most add point every 10 ms
        {
            double value0 = qSin(key); //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
            double value1 = qCos(key); //qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
            // add data to lines:
            ui.widget_9->graph(0)->addData(key, value0);
            ui.widget_9->graph(1)->addData(key, value1);
            // set data of dots:
    //		ui.widget_9->graph(2)->clearData();
            ui.widget_9->graph(2)->addData(key, value0);
    //		ui.widget_9->graph(3)->clearData();
            ui.widget_9->graph(3)->addData(key, value1);
            // remove data of lines that's outside visible range:
// 			ui.widget_9->graph(0)->removeDataBefore(key - 8);
// 			ui.widget_9->graph(1)->removeDataBefore(key - 8);
            // rescale value (vertical) axis to fit the current data:
            ui.widget_9->graph(0)->rescaleValueAxis();
            ui.widget_9->graph(1)->rescaleValueAxis(true);
            lastPointKey = key;
        }
        // make key axis range scroll with the data (at a constant range size of 8):
        ui.widget_9->xAxis->setRange(key + 0.25, 8, Qt::AlignRight);
        ui.widget_9->replot();

        // calculate frames per second:
        static double lastFpsKey;
        static int frameCount;
        ++frameCount;
        if (key - lastFpsKey > 2) // average fps over 2 seconds
        {
            //ui->statusBar->showMessage(
            //	QString("%1 FPS, Total Data points: %2")
            //	.arg(frameCount / (key - lastFpsKey), 0, 'f', 0)
            //	.arg(ui.widget_9->graph(0)->data()->count() + ui.widget_9->graph(1)->data()->count())
            //	, 0);
            lastFpsKey = key;
            frameCount = 0;
        }
    });
    dataTimer->start(0); // Interval 0 means to refresh as fast as possible
}

void plotdemo::InitalizeMultipleAxes()
{
    ui.widget_10->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
    ui.widget_10->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    ui.widget_10->legend->setFont(legendFont);
    ui.widget_10->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    ui.widget_10->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom | Qt::AlignRight);

    // setup for graph 0: key axis left, value axis bottom
    // will contain left maxwell-like function
    ui.widget_10->addGraph(ui.widget_10->yAxis, ui.widget_10->xAxis);
    ui.widget_10->graph(0)->setPen(QPen(QColor(255, 100, 0)));
    ui.widget_10->graph(0)->setBrush(QBrush(QPixmap("./balboa.jpg"))); // fill with texture of specified image
    ui.widget_10->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui.widget_10->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    ui.widget_10->graph(0)->setName("Left maxwell function");

    // setup for graph 1: key axis bottom, value axis left (those are the default axes)
    // will contain bottom maxwell-like function
    ui.widget_10->addGraph();
    ui.widget_10->graph(1)->setPen(QPen(Qt::red));
    ui.widget_10->graph(1)->setBrush(QBrush(QPixmap("./balboa.jpg"))); // same fill as we used for graph 0
    ui.widget_10->graph(1)->setLineStyle(QCPGraph::lsStepCenter);
    ui.widget_10->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 7));
    //	ui.widget_10->graph(1)->setErrorType(QCPGraph::etValue);
    ui.widget_10->graph(1)->setName("Bottom maxwell function");

    // setup for graph 2: key axis top, value axis right
    // will contain high frequency sine with low frequency beating:
    ui.widget_10->addGraph(ui.widget_10->xAxis2, ui.widget_10->yAxis2);
    ui.widget_10->graph(2)->setPen(QPen(Qt::blue));
    ui.widget_10->graph(2)->setName("High frequency sine");

    // setup for graph 3: same axes as graph 2
    // will contain low frequency beating envelope of graph 2
    ui.widget_10->addGraph(ui.widget_10->xAxis2, ui.widget_10->yAxis2);
    QPen blueDotPen;
    blueDotPen.setColor(QColor(30, 40, 255, 150));
    blueDotPen.setStyle(Qt::DotLine);
    blueDotPen.setWidthF(4);
    ui.widget_10->graph(3)->setPen(blueDotPen);
    ui.widget_10->graph(3)->setName("Sine envelope");

    // setup for graph 4: key axis right, value axis top
    // will contain parabolically distributed data points with some random perturbance
    ui.widget_10->addGraph(ui.widget_10->yAxis2, ui.widget_10->xAxis2);
    ui.widget_10->graph(4)->setPen(QColor(50, 50, 50, 255));
    ui.widget_10->graph(4)->setLineStyle(QCPGraph::lsNone);
    ui.widget_10->graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    ui.widget_10->graph(4)->setName("Some random data around\na quadratic function");

    // generate data, just playing with numbers, not much to learn here:
    QVector<double> x0(25), y0(25);
    QVector<double> x1(15), y1(15), y1err(15);
    QVector<double> x2(250), y2(250);
    QVector<double> x3(250), y3(250);
    QVector<double> x4(250), y4(250);
    for (int i = 0; i < 25; ++i) // data for graph 0
    {
        x0[i] = 3 * i / 25.0;
        y0[i] = qExp(-x0[i] * x0[i] * 0.8)*(x0[i] * x0[i] + x0[i]);
    }
    for (int i = 0; i < 15; ++i) // data for graph 1
    {
        x1[i] = 3 * i / 15.0;;
        y1[i] = qExp(-x1[i] * x1[i])*(x1[i] * x1[i])*2.6;
        y1err[i] = y1[i] * 0.25;
    }
    for (int i = 0; i < 250; ++i) // data for graphs 2, 3 and 4
    {
        x2[i] = i / 250.0 * 3 * M_PI;
        x3[i] = x2[i];
        x4[i] = i / 250.0 * 100 - 50;
        y2[i] = qSin(x2[i] * 12)*qCos(x2[i]) * 10;
        y3[i] = qCos(x3[i]) * 10;
        y4[i] = 0.01*x4[i] * x4[i] + 1.5*(rand() / (double)RAND_MAX - 0.5) + 1.5*M_PI;
    }

    // pass data points to graphs:
    ui.widget_10->graph(0)->setData(x0, y0);
    //	ui.widget_10->graph(1)->setDataValueError(x1, y1, y1err);
    ui.widget_10->graph(2)->setData(x2, y2);
    ui.widget_10->graph(3)->setData(x3, y3);
    ui.widget_10->graph(4)->setData(x4, y4);
    // activate top and right axes, which are invisible by default:
    ui.widget_10->xAxis2->setVisible(true);
    ui.widget_10->yAxis2->setVisible(true);
    // set ranges appropriate to show data:
    ui.widget_10->xAxis->setRange(0, 2.7);
    ui.widget_10->yAxis->setRange(0, 2.6);
    ui.widget_10->xAxis2->setRange(0, 3.0*M_PI);
    ui.widget_10->yAxis2->setRange(-70, 35);
    // set pi ticks on top axis:
    QVector<double> piTicks;
    QVector<QString> piLabels;
    piTicks << 0 << 0.5*M_PI << M_PI << 1.5*M_PI << 2 * M_PI << 2.5*M_PI << 3 * M_PI;
    piLabels << "0" << QStringLiteral("½π") << QStringLiteral("π") << QStringLiteral("1½π") << QStringLiteral("2π") << QStringLiteral("2½π") << QStringLiteral("3π");
    // 	ui.widget_10->xAxis2->setAutoTicks(false);
    // 	ui.widget_10->xAxis2->setAutoTickLabels(false);
    // 	ui.widget_10->xAxis2->setTickVector(piTicks);
    // 	ui.widget_10->xAxis2->setTickVectorLabels(piLabels);
    // add title layout element:
    ui.widget_10->plotLayout()->insertRow(0);
    //	ui.widget_10->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui.widget_10, "Way too many graphs in one plot"));
    // set labels:
    ui.widget_10->xAxis->setLabel("Bottom axis with outward ticks");
    ui.widget_10->yAxis->setLabel("Left axis label");
    ui.widget_10->xAxis2->setLabel("Top axis label");
    ui.widget_10->yAxis2->setLabel("Right axis label");
    // make ticks on bottom axis go outward:
    ui.widget_10->xAxis->setTickLength(0, 5);
    ui.widget_10->xAxis->setSubTickLength(0, 3);
    // make ticks on right axis go inward and outward:
    ui.widget_10->yAxis2->setTickLength(3, 3);
    ui.widget_10->yAxis2->setSubTickLength(1, 1);
}

void plotdemo::InitalizeLogarithmicAxis()
{
    ui.widget_11->setNoAntialiasingOnDrag(true); // more performance/responsiveness during dragging
    ui.widget_11->addGraph();
    QPen pen;
    pen.setColor(QColor(255, 170, 100));
    pen.setWidth(2);
    pen.setStyle(Qt::DotLine);
    ui.widget_11->graph(0)->setPen(pen);
    ui.widget_11->graph(0)->setName("x");

    ui.widget_11->addGraph();
    ui.widget_11->graph(1)->setPen(QPen(Qt::red));
    ui.widget_11->graph(1)->setBrush(QBrush(QColor(255, 0, 0, 20)));
//	ui.widget_11->graph(1)->setErrorType(QCPGraph::etBoth);
    ui.widget_11->graph(1)->setName("-sin(x)exp(x)");

    ui.widget_11->addGraph();
    ui.widget_11->graph(2)->setPen(QPen(Qt::blue));
    ui.widget_11->graph(2)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui.widget_11->graph(2)->setName(" sin(x)exp(x)");

    ui.widget_11->addGraph();
    pen.setColor(QColor(0, 0, 0));
    pen.setWidth(1);
    pen.setStyle(Qt::DashLine);
    ui.widget_11->graph(3)->setPen(pen);
    ui.widget_11->graph(3)->setBrush(QBrush(QColor(0, 0, 0, 15)));
    ui.widget_11->graph(3)->setLineStyle(QCPGraph::lsStepCenter);
    ui.widget_11->graph(3)->setName("x!");

    QVector<double> x0(200), y0(200);
    QVector<double> x1(200), y1(200);
    QVector<double> x2(200), y2(200);
    QVector<double> x3(21), y3(21);
    for (int i = 0; i < 200; ++i)
    {
        x0[i] = i / 10.0;
        y0[i] = x0[i];
        x1[i] = i / 10.0;
        y1[i] = -qSin(x1[i])*qExp(x1[i]);
        x2[i] = i / 10.0;
        y2[i] = qSin(x2[i])*qExp(x2[i]);
    }
    for (int i = 0; i < 21; ++i)
    {
        x3[i] = i;
        y3[i] = 1;
        for (int k = 1; k <= i; ++k) y3[i] *= k; // factorial
    }
    ui.widget_11->graph(0)->setData(x0, y0);
    ui.widget_11->graph(1)->setData(x1, y1);
    ui.widget_11->graph(2)->setData(x2, y2);
    ui.widget_11->graph(3)->setData(x3, y3);

    ui.widget_11->yAxis->grid()->setSubGridVisible(true);
    ui.widget_11->xAxis->grid()->setSubGridVisible(true);
    ui.widget_11->yAxis->setScaleType(QCPAxis::stLogarithmic);
//	ui.widget_11->yAxis->setScaleLogBase(100);
    ui.widget_11->yAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
    ui.widget_11->yAxis->setNumberPrecision(0); // makes sure "1*10^4" is displayed only as "10^4"
//	ui.widget_11->yAxis->setSubTickCount(10);
    ui.widget_11->xAxis->setRange(0, 19.9);
    ui.widget_11->yAxis->setRange(1e-2, 1e10);
    // make range draggable and zoomable:
    ui.widget_11->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // make top right axes clones of bottom left axes:
    ui.widget_11->axisRect()->setupFullAxesBox();
    // connect signals so top and right axes move in sync with bottom and left axes:
    connect(ui.widget_11->xAxis, SIGNAL(rangeChanged(QCPRange)), ui.widget_11->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui.widget_11->yAxis, SIGNAL(rangeChanged(QCPRange)), ui.widget_11->yAxis2, SLOT(setRange(QCPRange)));

    ui.widget_11->legend->setVisible(true);
    ui.widget_11->legend->setBrush(QBrush(QColor(255, 255, 255, 150)));
    ui.widget_11->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop); // make legend align in top left corner or axis rect
}

void plotdemo::InitalizeLine()
{
    ui.widget_12->legend->setVisible(true);
    ui.widget_12->legend->setFont(QFont("Helvetica", 9));
    QPen pen;
    QStringList lineNames;
    lineNames << "lsNone" << "lsLine" << "lsStepLeft" << "lsStepRight" << "lsStepCenter" << "lsImpulse";
    // add graphs with different line styles:
    for (int i = QCPGraph::lsNone; i <= QCPGraph::lsImpulse; ++i)
    {
        ui.widget_12->addGraph();
        pen.setColor(QColor(qSin(i * 1 + 1.2) * 80 + 80, qSin(i*0.3 + 0) * 80 + 80, qSin(i*0.3 + 1.5) * 80 + 80));
        ui.widget_12->graph()->setPen(pen);
        ui.widget_12->graph()->setName(lineNames.at(i - QCPGraph::lsNone));
        ui.widget_12->graph()->setLineStyle((QCPGraph::LineStyle)i);
        ui.widget_12->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
        // generate data:
        QVector<double> x(15), y(15);
        for (int j = 0; j < 15; ++j)
        {
            x[j] = j / 15.0 * 5 * 3.14 + 0.01;
            y[j] = 7 * qSin(x[j]) / x[j] - (i - QCPGraph::lsNone) * 5 + (QCPGraph::lsImpulse) * 5 + 2;
        }
        ui.widget_12->graph()->setData(x, y);
        ui.widget_12->graph()->rescaleAxes(true);
    }
    // zoom out a bit:
    ui.widget_12->yAxis->scaleRange(1.1, ui.widget_12->yAxis->range().center());
    ui.widget_12->xAxis->scaleRange(1.1, ui.widget_12->xAxis->range().center());
    // set blank axis lines:
    ui.widget_12->xAxis->setTicks(false);
    ui.widget_12->yAxis->setTicks(true);
    ui.widget_12->xAxis->setTickLabels(false);
    ui.widget_12->yAxis->setTickLabels(true);
    // make top right axes clones of bottom left axes:
    ui.widget_12->axisRect()->setupFullAxesBox();
}

void plotdemo::InitalizeDateAxis()
{
    // set locale to english, so we get english month names:
    ui.widget_13->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    // seconds of current time, we'll use it as starting point in time for data:
    double now = QDateTime::currentDateTime().toTime_t();
    srand(8); // set the random seed, so we always get the same random data
    // create multiple graphs:
    for (int gi = 0; gi < 5; ++gi)
    {
        ui.widget_13->addGraph();
        QPen pen;
        pen.setColor(QColor(0, 0, 255, 200));
        ui.widget_13->graph()->setLineStyle(QCPGraph::lsLine);
        ui.widget_13->graph()->setPen(pen);
        ui.widget_13->graph()->setBrush(QBrush(QColor(255 / 4.0*gi, 160, 50, 150)));
        // generate random walk data:
        QVector<double> time(250), value(250);
        for (int i = 0; i < 250; ++i)
        {
            time[i] = now + 24 * 3600 * i;
            if (i == 0)
                value[i] = (i / 50.0 + 1)*(rand() / (double)RAND_MAX - 0.5);
            else
                value[i] = qFabs(value[i - 1])*(1 + 0.02 / 4.0*(4 - gi)) + (i / 50.0 + 1)*(rand() / (double)RAND_MAX - 0.5);
        }
        ui.widget_13->graph()->setData(time, value);
    }
    // configure bottom axis to show date and time instead of number:
// 	ui.widget_13->xAxis->setTickLabelType(QCPAxis::ltDateTime);
// 	ui.widget_13->xAxis->setDateTimeFormat("MMMM\nyyyy");
    // set a more compact font size for bottom and left axis tick labels:
    ui.widget_13->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    ui.widget_13->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    // set a fixed tick-step to one tick per month:
// 	ui.widget_13->xAxis->setAutoTickStep(false);
// 	ui.widget_13->xAxis->setTickStep(2628000); // one month in seconds
// 	ui.widget_13->xAxis->setSubTickCount(3);
    // apply manual tick and tick label for left axis:
// 	ui.widget_13->yAxis->setAutoTicks(false);
// 	ui.widget_13->yAxis->setAutoTickLabels(false);
// 	ui.widget_13->yAxis->setTickVector(QVector<double>() << 5 << 55);
// 	ui.widget_13->yAxis->setTickVectorLabels(QVector<QString>() << "Not so\nhigh" << "Very\nhigh");
    // set axis labels:
    ui.widget_13->xAxis->setLabel("Date");
    ui.widget_13->yAxis->setLabel("Random wobbly lines value");
    // make top and right axes visible but without ticks and labels:
    ui.widget_13->xAxis2->setVisible(true);
    ui.widget_13->yAxis2->setVisible(true);
    ui.widget_13->xAxis2->setTicks(false);
    ui.widget_13->yAxis2->setTicks(false);
    ui.widget_13->xAxis2->setTickLabels(false);
    ui.widget_13->yAxis2->setTickLabels(false);
    // set axis ranges to show all data:
    ui.widget_13->xAxis->setRange(now, now + 24 * 3600 * 249);
    ui.widget_13->yAxis->setRange(0, 60);
    // show legend:
    ui.widget_13->legend->setVisible(true);
}

void plotdemo::InitalizeParametricCurves()
{
    // create empty curve objects and add them to customPlot:
    QCPCurve *fermatSpiral1 = new QCPCurve(ui.widget_14->xAxis, ui.widget_14->yAxis);
    QCPCurve *fermatSpiral2 = new QCPCurve(ui.widget_14->xAxis, ui.widget_14->yAxis);
    QCPCurve *deltoidRadial = new QCPCurve(ui.widget_14->xAxis, ui.widget_14->yAxis);
// 	ui.widget_14->addPlottable(fermatSpiral1);
// 	ui.widget_14->addPlottable(fermatSpiral2);
// 	ui.widget_14->addPlottable(deltoidRadial);
    // generate the curve data points:
    int pointCount = 500;
    QVector<double> x1(pointCount), y1(pointCount);
    QVector<double> x2(pointCount), y2(pointCount);
    QVector<double> x3(pointCount), y3(pointCount);
    for (int i = 0; i < pointCount; ++i)
    {
        double phi = (i / (double)(pointCount - 1)) * 8 * M_PI;
        x1[i] = qSqrt(phi)*qCos(phi);
        y1[i] = qSqrt(phi)*qSin(phi);
        x2[i] = -x1[i];
        y2[i] = -y1[i];
        double t = i / (double)(pointCount - 1) * 2 * M_PI;
        x3[i] = 2 * qCos(2 * t) + qCos(1 * t) + 2 * qSin(t);
        y3[i] = 2 * qSin(2 * t) - qSin(1 * t);
    }
    // pass the data to the curves:
    fermatSpiral1->setData(x1, y1);
    fermatSpiral2->setData(x2, y2);
    deltoidRadial->setData(x3, y3);
    // color the curves:
    fermatSpiral1->setPen(QPen(Qt::blue));
    fermatSpiral1->setBrush(QBrush(QColor(0, 0, 255, 20)));
    fermatSpiral2->setPen(QPen(QColor(255, 120, 0)));
    fermatSpiral2->setBrush(QBrush(QColor(255, 120, 0, 30)));
    QRadialGradient radialGrad(QPointF(310, 180), 200);
    radialGrad.setColorAt(0, QColor(170, 20, 240, 100));
    radialGrad.setColorAt(0.5, QColor(20, 10, 255, 40));
    radialGrad.setColorAt(1, QColor(120, 20, 240, 10));
    deltoidRadial->setPen(QPen(QColor(170, 20, 240)));
    deltoidRadial->setBrush(QBrush(radialGrad));
    // set some basic customPlot config:
    ui.widget_14->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui.widget_14->axisRect()->setupFullAxesBox();
    ui.widget_14->rescaleAxes();
}

void plotdemo::InitalizeStackedBar()
{
    // create empty bar chart objects:
    QCPBars *regen = new QCPBars(ui.widget_15->xAxis, ui.widget_15->yAxis);
    QCPBars *nuclear = new QCPBars(ui.widget_15->xAxis, ui.widget_15->yAxis);
    QCPBars *fossil = new QCPBars(ui.widget_15->xAxis, ui.widget_15->yAxis);
// 	ui.widget_15->addPlottable(regen);
// 	ui.widget_15->addPlottable(nuclear);
// 	ui.widget_15->addPlottable(fossil);
    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);
    fossil->setName("Fossil fuels");
    pen.setColor(QColor(255, 131, 0));
    fossil->setPen(pen);
    fossil->setBrush(QColor(255, 131, 0, 50));
    nuclear->setName("Nuclear");
    pen.setColor(QColor(1, 92, 191));
    nuclear->setPen(pen);
    nuclear->setBrush(QColor(1, 92, 191, 50));
    regen->setName("Regenerative");
    pen.setColor(QColor(150, 222, 0));
    regen->setPen(pen);
    regen->setBrush(QColor(150, 222, 0, 70));
    // stack bars ontop of each other:
    nuclear->moveAbove(fossil);
    regen->moveAbove(nuclear);

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
    labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
// 	ui.widget_15->xAxis->setAutoTicks(false);
// 	ui.widget_15->xAxis->setAutoTickLabels(false);
// 	ui.widget_15->xAxis->setTickVector(ticks);
// 	ui.widget_15->xAxis->setTickVectorLabels(labels);
    ui.widget_15->xAxis->setTickLabelRotation(60);
//	ui.widget_15->xAxis->setSubTickCount(0);
    ui.widget_15->xAxis->setTickLength(0, 4);
    ui.widget_15->xAxis->grid()->setVisible(true);
    ui.widget_15->xAxis->setRange(0, 8);

    // prepare y axis:
    ui.widget_15->yAxis->setRange(0, 12.1);
    ui.widget_15->yAxis->setPadding(5); // a bit more space to the left border
    ui.widget_15->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
    ui.widget_15->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    ui.widget_15->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    ui.widget_15->yAxis->grid()->setSubGridPen(gridPen);

    // Add data:
    QVector<double> fossilData, nuclearData, regenData;
    fossilData << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;
    nuclearData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
    regenData << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
    fossil->setData(ticks, fossilData);
    nuclear->setData(ticks, nuclearData);
    regen->setData(ticks, regenData);

    // setup legend:
    ui.widget_15->legend->setVisible(true);
    ui.widget_15->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignHCenter);
    ui.widget_15->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    ui.widget_15->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui.widget_15->legend->setFont(legendFont);
    ui.widget_15->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void plotdemo::InitalizeStatisticalBox()
{
    // create empty statistical box plottables:
    QCPStatisticalBox *sample1 = new QCPStatisticalBox(ui.widget_16->xAxis, ui.widget_16->yAxis);
    QCPStatisticalBox *sample2 = new QCPStatisticalBox(ui.widget_16->xAxis, ui.widget_16->yAxis);
    QCPStatisticalBox *sample3 = new QCPStatisticalBox(ui.widget_16->xAxis, ui.widget_16->yAxis);
// 	ui.widget_16->addPlottable(sample1);
// 	ui.widget_16->addPlottable(sample2);
// 	ui.widget_16->addPlottable(sample3);
    QBrush boxBrush(QColor(60, 60, 255, 100));
    boxBrush.setStyle(Qt::Dense6Pattern); // make it look oldschool
    sample1->setBrush(boxBrush);
    sample2->setBrush(boxBrush);
    sample3->setBrush(boxBrush);

    // set data:
// 	sample1->setKey(1);
// 	sample1->setMinimum(1.1);
// 	sample1->setLowerQuartile(1.9);
// 	sample1->setMedian(2.25);
// 	sample1->setUpperQuartile(2.7);
// 	sample1->setMaximum(4.2);
//
// 	sample2->setKey(2);
// 	sample2->setMinimum(0.8);
// 	sample2->setLowerQuartile(1.6);
// 	sample2->setMedian(2.2);
// 	sample2->setUpperQuartile(3.2);
// 	sample2->setMaximum(4.9);
// 	sample2->setOutliers(QVector<double>() << 0.7 << 0.39 << 0.45 << 6.2 << 5.84);
//
// 	sample3->setKey(3);
// 	sample3->setMinimum(0.2);
// 	sample3->setLowerQuartile(0.7);
// 	sample3->setMedian(1.1);
// 	sample3->setUpperQuartile(1.6);
// 	sample3->setMaximum(2.9);

    // prepare manual x axis labels:
//	ui.widget_16->xAxis->setSubTickCount(0);
    ui.widget_16->xAxis->setTickLength(0, 4);
    ui.widget_16->xAxis->setTickLabelRotation(20);
// 	ui.widget_16->xAxis->setAutoTicks(false);
// 	ui.widget_16->xAxis->setAutoTickLabels(false);
// 	ui.widget_16->xAxis->setTickVector(QVector<double>() << 1 << 2 << 3);
// 	ui.widget_16->xAxis->setTickVectorLabels(QVector<QString>() << "Sample 1" << "Sample 2" << "Control Group");

    // prepare axes:
    ui.widget_16->yAxis->setLabel(QString::fromStdWString(L"O₂ Absorption [mg]"));
    ui.widget_16->rescaleAxes();
    ui.widget_16->xAxis->scaleRange(1.7, ui.widget_16->xAxis->range().center());
    ui.widget_16->yAxis->setRange(0, 7);
    ui.widget_16->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void plotdemo::InitalizeInteraction()
{
    srand(QDateTime::currentDateTime().toTime_t());

    ui.widget_17->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
        QCP::iSelectLegend | QCP::iSelectPlottables);
    ui.widget_17->xAxis->setRange(-8, 8);
    ui.widget_17->yAxis->setRange(-5, 5);
    ui.widget_17->axisRect()->setupFullAxesBox();

    ui.widget_17->plotLayout()->insertRow(0);
//	ui.widget_17->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui.widget_17, "Interaction Example"));

    ui.widget_17->xAxis->setLabel("x Axis");
    ui.widget_17->yAxis->setLabel("y Axis");
    ui.widget_17->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui.widget_17->legend->setFont(legendFont);
    ui.widget_17->legend->setSelectedFont(legendFont);
    ui.widget_17->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

    addRandomGraph();
    addRandomGraph();
    addRandomGraph();
    addRandomGraph();

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui.widget_17, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui.widget_17, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui.widget_17, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui.widget_17->xAxis, SIGNAL(rangeChanged(QCPRange)), ui.widget_17->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui.widget_17->yAxis, SIGNAL(rangeChanged(QCPRange)), ui.widget_17->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
//	connect(ui.widget_17, SIGNAL(titleDoubleClick(QMouseEvent*, QCPPlotTitle*)), this, SLOT(titleDoubleClick(QMouseEvent*, QCPPlotTitle*)));
    connect(ui.widget_17, SIGNAL(axisDoubleClick(QCPAxis*, QCPAxis::SelectablePart, QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*, QCPAxis::SelectablePart)));
    connect(ui.widget_17, SIGNAL(legendDoubleClick(QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*, QCPAbstractLegendItem*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(ui.widget_17, SIGNAL(plottableClick(QCPAbstractPlottable*, QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));

    // setup policy and connect slot for context menu popup:
    ui.widget_17->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui.widget_17, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
}

void plotdemo::InitalizeItem()
{
    ui.widget_18->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    QCPGraph *graph = ui.widget_18->addGraph();
    int n = 500;
    double phase = 0;
    double k = 3;
    QVector<double> x(n), y(n);
    for (int i = 0; i < n; ++i)
    {
        x[i] = i / (double)(n - 1) * 34 - 17;
        y[i] = qExp(-x[i] * x[i] / 20.0)*qSin(k*x[i] + phase);
    }
    graph->setData(x, y);
    graph->setPen(QPen(Qt::blue));
    graph->rescaleKeyAxis();
    ui.widget_18->yAxis->setRange(-1.45, 1.65);
    ui.widget_18->xAxis->grid()->setZeroLinePen(Qt::NoPen);

    // add the bracket at the top:
    QCPItemBracket *bracket = new QCPItemBracket(ui.widget_18);
//	ui.widget_18->addItem(bracket);
    bracket->left->setCoords(-8, 1.1);
    bracket->right->setCoords(8, 1.1);
    bracket->setLength(13);

    // add the text label at the top:
    QCPItemText *wavePacketText = new QCPItemText(ui.widget_18);
//	ui.widget_18->addItem(wavePacketText);
    wavePacketText->position->setParentAnchor(bracket->center);
    wavePacketText->position->setCoords(0, -10); // move 10 pixels to the top from bracket center anchor
    wavePacketText->setPositionAlignment(Qt::AlignBottom | Qt::AlignHCenter);
//	wavePacketText->setText("Wavepacket");
    wavePacketText->setFont(QFont(font().family(), 10));

    // add the phase tracer (red circle) which sticks to the graph data (and gets updated in bracketDataSlot by timer event):
    QCPItemTracer *phaseTracer = new QCPItemTracer(ui.widget_18);
//	ui.widget_18->addItem(phaseTracer);
    itemDemoPhaseTracer = phaseTracer; // so we can access it later in the bracketDataSlot for animation
    phaseTracer->setGraph(graph);
    phaseTracer->setGraphKey((M_PI*1.5 - phase) / k);
    phaseTracer->setInterpolating(true);
    phaseTracer->setStyle(QCPItemTracer::tsCircle);
    phaseTracer->setPen(QPen(Qt::red));
    phaseTracer->setBrush(Qt::red);
    phaseTracer->setSize(7);

    // add label for phase tracer:
    QCPItemText *phaseTracerText = new QCPItemText(ui.widget_18);
//	ui.widget_18->addItem(phaseTracerText);
    phaseTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
    phaseTracerText->setPositionAlignment(Qt::AlignRight | Qt::AlignBottom);
    phaseTracerText->position->setCoords(1.0, 0.95); // lower right corner of axis rect
    phaseTracerText->setText("Points of fixed\nphase define\nphase velocity vp");
    phaseTracerText->setTextAlignment(Qt::AlignLeft);
    phaseTracerText->setFont(QFont(font().family(), 9));
    phaseTracerText->setPadding(QMargins(8, 0, 0, 0));

    // add arrow pointing at phase tracer, coming from label:
    QCPItemCurve *phaseTracerArrow = new QCPItemCurve(ui.widget_18);
//	ui.widget_18->addItem(phaseTracerArrow);
    phaseTracerArrow->start->setParentAnchor(phaseTracerText->left);
    phaseTracerArrow->startDir->setParentAnchor(phaseTracerArrow->start);
    phaseTracerArrow->startDir->setCoords(-40, 0); // direction 30 pixels to the left of parent anchor (tracerArrow->start)
    phaseTracerArrow->end->setParentAnchor(phaseTracer->position);
    phaseTracerArrow->end->setCoords(10, 10);
    phaseTracerArrow->endDir->setParentAnchor(phaseTracerArrow->end);
    phaseTracerArrow->endDir->setCoords(30, 30);
    phaseTracerArrow->setHead(QCPLineEnding::esSpikeArrow);
//	phaseTracerArrow->setTail(QCPLineEnding(QCPLineEnding::esBar, (phaseTracerText->bottom->pixelPoint().y() - phaseTracerText->top->pixelPoint().y())*0.85));

    // add the group velocity tracer (green circle):
    QCPItemTracer *groupTracer = new QCPItemTracer(ui.widget_18);
//	ui.widget_18->addItem(groupTracer);
    groupTracer->setGraph(graph);
    groupTracer->setGraphKey(5.5);
    groupTracer->setInterpolating(true);
    groupTracer->setStyle(QCPItemTracer::tsCircle);
    groupTracer->setPen(QPen(Qt::green));
    groupTracer->setBrush(Qt::green);
    groupTracer->setSize(7);

    // add label for group tracer:
    QCPItemText *groupTracerText = new QCPItemText(ui.widget_18);
//	ui.widget_18->addItem(groupTracerText);
    groupTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
    groupTracerText->setPositionAlignment(Qt::AlignRight | Qt::AlignTop);
    groupTracerText->position->setCoords(1.0, 0.20); // lower right corner of axis rect
    groupTracerText->setText("Fixed positions in\nwave packet define\ngroup velocity vg");
    groupTracerText->setTextAlignment(Qt::AlignLeft);
    groupTracerText->setFont(QFont(font().family(), 9));
    groupTracerText->setPadding(QMargins(8, 0, 0, 0));

    // add arrow pointing at group tracer, coming from label:
    QCPItemCurve *groupTracerArrow = new QCPItemCurve(ui.widget_18);
//	ui.widget_18->addItem(groupTracerArrow);
    groupTracerArrow->start->setParentAnchor(groupTracerText->left);
    groupTracerArrow->startDir->setParentAnchor(groupTracerArrow->start);
    groupTracerArrow->startDir->setCoords(-40, 0); // direction 30 pixels to the left of parent anchor (tracerArrow->start)
    groupTracerArrow->end->setCoords(5.5, 0.4);
    groupTracerArrow->endDir->setParentAnchor(groupTracerArrow->end);
    groupTracerArrow->endDir->setCoords(0, -40);
    groupTracerArrow->setHead(QCPLineEnding::esSpikeArrow);
//	groupTracerArrow->setTail(QCPLineEnding(QCPLineEnding::esBar, (groupTracerText->bottom->pixelPoint().y() - groupTracerText->top->pixelPoint().y())*0.85));

    // add dispersion arrow:
    QCPItemCurve *arrow = new QCPItemCurve(ui.widget_18);
//	ui.widget_18->addItem(arrow);
    arrow->start->setCoords(1, -1.1);
    arrow->startDir->setCoords(-1, -1.3);
    arrow->endDir->setCoords(-5, -0.3);
    arrow->end->setCoords(-10, -0.2);
    arrow->setHead(QCPLineEnding::esSpikeArrow);

    // add the dispersion arrow label:
    QCPItemText *dispersionText = new QCPItemText(ui.widget_18);
//	ui.widget_18->addItem(dispersionText);
    dispersionText->position->setCoords(-6, -0.9);
    dispersionText->setRotation(40);
    dispersionText->setText("Dispersion with\nvp < vg");
    dispersionText->setFont(QFont(font().family(), 10));

    // setup a timer that repeatedly calls MainWindow::bracketDataSlot:
    QTimer * dataTimer = new QTimer(this);
    connect(dataTimer, &QTimer::timeout, this, [this]{
        double secs = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
        // update data to make phase move:
        int n = 500;
        double phase = secs * 5;
        double k = 3;
        QVector<double> x(n), y(n);
        for (int i = 0; i < n; ++i)
        {
            x[i] = i / (double)(n - 1) * 34 - 17;
            y[i] = qExp(-x[i] * x[i] / 20.0)*qSin(k*x[i] + phase);
        }
        ui.widget_18->graph()->setData(x, y);

        itemDemoPhaseTracer->setGraphKey((8 * M_PI + fmod(M_PI*1.5 - phase, 6 * M_PI)) / k);

        ui.widget_18->replot();

        // calculate frames per second:
        double key = secs;
        static double lastFpsKey;
        static int frameCount;
        ++frameCount;
        if (key - lastFpsKey > 2) // average fps over 2 seconds
        {
            /*ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount / (key - lastFpsKey), 0, 'f', 0)
            .arg(ui->customPlot->graph(0)->data()->count())
            , 0);*/
            lastFpsKey = key;
            frameCount = 0;
        }
    });
    dataTimer->start(0); // Interval 0 means to refresh as fast as possible
}

void plotdemo::IinitalizeAdvanceAxes()
{
    // configure axis rect:
    ui.widget_19->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    QCPAxisRect *wideAxisRect = new QCPAxisRect(ui.widget_19);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui.widget_19->plotLayout()->addElement(0, 0, wideAxisRect); // insert axis rect in first row
    ui.widget_19->plotLayout()->addElement(1, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //customPlot->plotLayout()->setRowStretchFactor(1, 2);
    // prepare axis rects that will be placed in the sublayout:
    QCPAxisRect *subRectLeft = new QCPAxisRect(ui.widget_19, false); // false means to not setup default axes
    QCPAxisRect *subRectRight = new QCPAxisRect(ui.widget_19, false);
    subLayout->addElement(0, 0, subRectLeft);
    subLayout->addElement(0, 1, subRectRight);
    subRectRight->setMaximumSize(150, 150); // make bottom right axis rect size fixed 150x150
    subRectRight->setMinimumSize(150, 150); // make bottom right axis rect size fixed 150x150
    // setup axes in sub layout axis rects:
    subRectLeft->addAxes(QCPAxis::atBottom | QCPAxis::atLeft);
    subRectRight->addAxes(QCPAxis::atBottom | QCPAxis::atRight);
// 	subRectLeft->axis(QCPAxis::atLeft)->setAutoTickCount(2);
// 	subRectRight->axis(QCPAxis::atRight)->setAutoTickCount(2);
// 	subRectRight->axis(QCPAxis::atBottom)->setAutoTickCount(2);
    subRectLeft->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    // synchronize the left and right margins of the top and bottom axis rects:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui.widget_19);
    subRectLeft->setMarginGroup(QCP::msLeft, marginGroup);
    subRectRight->setMarginGroup(QCP::msRight, marginGroup);
    wideAxisRect->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);
    // move newly created axes on "axes" layer and grids on "grid" layer:
    foreach(QCPAxisRect *rect, ui.widget_19->axisRects())
    {
        foreach(QCPAxis *axis, rect->axes())
        {
            axis->setLayer("axes");
            axis->grid()->setLayer("grid");
        }
    }

    // prepare data:
    QVector<double> x1a(20), y1a(20);
    QVector<double> x1b(50), y1b(50);
    QVector<double> x2(100), y2(100);
    QVector<double> x3, y3;
    qsrand(3);
    for (int i = 0; i < x1a.size(); ++i)
    {
        x1a[i] = i / (double)(x1a.size() - 1) * 10 - 5.0;
        y1a[i] = qCos(x1a[i]);
    }
    for (int i = 0; i < x1b.size(); ++i)
    {
        x1b[i] = i / (double)x1b.size() * 10 - 5.0;
        y1b[i] = qExp(-x1b[i] * x1b[i] * 0.2) * 1000;
    }
    for (int i = 0; i < x2.size(); ++i)
    {
        x2[i] = i / (double)x2.size() * 10;
        y2[i] = qrand() / (double)RAND_MAX - 0.5 + y2[qAbs(i - 1)];
    }
    x3 << 1 << 2 << 3 << 4;
    y3 << 2 << 2.5 << 4 << 1.5;

    // create and configure plottables:
    QCPGraph *mainGraph1 = ui.widget_19->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
    mainGraph1->setData(x1a, y1a);
    mainGraph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black), QBrush(Qt::white), 6));
    mainGraph1->setPen(QPen(QColor(120, 120, 120), 2));
    QCPGraph *mainGraph2 = ui.widget_19->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft, 1));
    mainGraph2->setData(x1b, y1b);
    mainGraph2->setPen(QPen(QColor("#8070B8"), 2));
    mainGraph2->setBrush(QColor(110, 170, 110, 30));
    mainGraph1->setChannelFillGraph(mainGraph2);
    mainGraph1->setBrush(QColor(255, 161, 0, 50));

    QCPGraph *graph2 = ui.widget_19->addGraph(subRectLeft->axis(QCPAxis::atBottom), subRectLeft->axis(QCPAxis::atLeft));
    graph2->setData(x2, y2);
    graph2->setLineStyle(QCPGraph::lsImpulse);
    graph2->setPen(QPen(QColor("#FFA100"), 1.5));

    QCPBars *bars1 = new QCPBars(subRectRight->axis(QCPAxis::atBottom), subRectRight->axis(QCPAxis::atRight));
//	ui.widget_19->addPlottable(bars1);
    bars1->setWidth(3 / (double)x3.size());
    bars1->setData(x3, y3);
    bars1->setPen(QPen(Qt::black));
    bars1->setAntialiased(false);
    bars1->setAntialiasedFill(false);
    bars1->setBrush(QColor("#705BE8"));
// 	bars1->keyAxis()->setAutoTicks(false);
// 	bars1->keyAxis()->setTickVector(x3);
// 	bars1->keyAxis()->setSubTickCount(0);

    // rescale axes according to graph's data:
    mainGraph1->rescaleAxes();
    mainGraph2->rescaleAxes();
    graph2->rescaleAxes();
    bars1->rescaleAxes();
    wideAxisRect->axis(QCPAxis::atLeft, 1)->setRangeLower(0);
}

void plotdemo::IinitalizeFinancial()
{
    ui.widget_20->legend->setVisible(true);

    // generate two sets of random walk data (one for candlestick and one for ohlc chart):
    int n = 500;
    QVector<double> time(n), value1(n), value2(n);
    QDateTime start = QDateTime(QDate(2014, 6, 11));
    start.setTimeSpec(Qt::UTC);
    double startTime = start.toTime_t();
    double binSize = 3600 * 24; // bin data in 1 day intervals
    time[0] = startTime;
    value1[0] = 60;
    value2[0] = 20;
    qsrand(9);
    for (int i = 1; i < n; ++i)
    {
        time[i] = startTime + 3600 * i;
        value1[i] = value1[i - 1] + (qrand() / (double)RAND_MAX - 0.5) * 10;
        value2[i] = value2[i - 1] + (qrand() / (double)RAND_MAX - 0.5) * 3;
    }

    // create candlestick chart:
    QCPFinancial *candlesticks = new QCPFinancial(ui.widget_20->xAxis, ui.widget_20->yAxis);
// 	ui.widget_20->addPlottable(candlesticks);
// 	QCPFinancialDataMap data1 = QCPFinancial::timeSeriesToOhlc(time, value1, binSize, startTime);
    candlesticks->setName("Candlestick");
    candlesticks->setChartStyle(QCPFinancial::csCandlestick);
//	candlesticks->setData(&data1, true);
    candlesticks->setWidth(binSize*0.9);
    candlesticks->setTwoColored(true);
    candlesticks->setBrushPositive(QColor(245, 245, 245));
    candlesticks->setBrushNegative(QColor(0, 0, 0));
    candlesticks->setPenPositive(QPen(QColor(0, 0, 0)));
    candlesticks->setPenNegative(QPen(QColor(0, 0, 0)));

    // create ohlc chart:
    QCPFinancial *ohlc = new QCPFinancial(ui.widget_20->xAxis, ui.widget_20->yAxis);
// 	ui.widget_20->addPlottable(ohlc);
// 	QCPFinancialDataMap data2 = QCPFinancial::timeSeriesToOhlc(time, value2, binSize / 3.0, startTime); // divide binSize by 3 just to make the ohlc bars a bit denser
    ohlc->setName("OHLC");
    ohlc->setChartStyle(QCPFinancial::csOhlc);
//	ohlc->setData(&data2, true);
    ohlc->setWidth(binSize*0.2);
    ohlc->setTwoColored(true);

    // create bottom axis rect for volume bar chart:
    QCPAxisRect *volumeAxisRect = new QCPAxisRect(ui.widget_20);
    ui.widget_20->plotLayout()->addElement(1, 0, volumeAxisRect);
    volumeAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 100));
    volumeAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
    volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
    // bring bottom and main axis rect closer together:
    ui.widget_20->plotLayout()->setRowSpacing(0);
    volumeAxisRect->setAutoMargins(QCP::msLeft | QCP::msRight | QCP::msBottom);
    volumeAxisRect->setMargins(QMargins(0, 0, 0, 0));
    // create two bar plottables, for positive (green) and negative (red) volume bars:
    QCPBars *volumePos = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
    QCPBars *volumeNeg = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
    for (int i = 0; i < n / 5; ++i)
    {
        int v = qrand() % 20000 + qrand() % 20000 + qrand() % 20000 - 10000 * 3;
        (v < 0 ? volumeNeg : volumePos)->addData(startTime + 3600 * 5.0*i, qAbs(v)); // add data to either volumeNeg or volumePos, depending on sign of v
    }
    ui.widget_20->setAutoAddPlottableToLegend(false);
// 	ui.widget_20->addPlottable(volumePos);
// 	ui.widget_20->addPlottable(volumeNeg);
    volumePos->setWidth(3600 * 4);
    volumePos->setPen(Qt::NoPen);
    volumePos->setBrush(QColor(100, 180, 110));
    volumeNeg->setWidth(3600 * 4);
    volumeNeg->setPen(Qt::NoPen);
    volumeNeg->setBrush(QColor(180, 90, 90));

    // interconnect x axis ranges of main and bottom axis rects:
    connect(ui.widget_20->xAxis, SIGNAL(rangeChanged(QCPRange)), volumeAxisRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(volumeAxisRect->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), ui.widget_20->xAxis, SLOT(setRange(QCPRange)));
    // configure axes of both main and bottom axis rect:
// 	volumeAxisRect->axis(QCPAxis::atBottom)->setAutoTickStep(false);
// 	volumeAxisRect->axis(QCPAxis::atBottom)->setTickStep(3600 * 24 * 4); // 4 day tickstep
// 	volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelType(QCPAxis::ltDateTime);
// 	volumeAxisRect->axis(QCPAxis::atBottom)->setDateTimeSpec(Qt::UTC);
// 	volumeAxisRect->axis(QCPAxis::atBottom)->setDateTimeFormat("dd. MMM");
    volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelRotation(15);
//	volumeAxisRect->axis(QCPAxis::atLeft)->setAutoTickCount(3);
    ui.widget_20->xAxis->setBasePen(Qt::NoPen);
    ui.widget_20->xAxis->setTickLabels(false);
    ui.widget_20->xAxis->setTicks(false); // only want vertical grid in main axis rect, so hide xAxis backbone, ticks, and labels
// 	ui.widget_20->xAxis->setAutoTickStep(false);
// 	ui.widget_20->xAxis->setTickStep(3600 * 24 * 4); // 4 day tickstep
    ui.widget_20->rescaleAxes();
    ui.widget_20->xAxis->scaleRange(1.025, ui.widget_20->xAxis->range().center());
    ui.widget_20->yAxis->scaleRange(1.1, ui.widget_20->yAxis->range().center());

    // make axis rects' left side line up:
    QCPMarginGroup *group = new QCPMarginGroup(ui.widget_20);
    ui.widget_20->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight, group);
    volumeAxisRect->setMarginGroup(QCP::msLeft | QCP::msRight, group);
}

void plotdemo::Test()
{
//    //分时测试
//    TimeSharingTrendWidget * widget = new TimeSharingTrendWidget;
//    TimeSharingTrendPlot * widget6 = widget->GetTimeSharingTrendPlot();
//    ui.widget_22->SetContentWidget(widget);
//    ui.widget_22->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
//    // seconds of current time, we'll use it as starting point in time for data:
//    double now = QDateTime::currentDateTime().toTime_t();
//    srand(8); // set the random seed, so we always get the same random data
//    // create multiple graphs:
//    for (int gi = 0; gi < 5; ++gi)
//    {
//        widget6->AddGraph();
//        QPen pen;
//        pen.setColor(QColor(0, 0, 255, 200));
//        widget6->GetGraph()->setLineStyle(QCPGraph::lsLine);
//        widget6->GetGraph()->setPen(pen);
//        widget6->GetGraph()->setBrush(QBrush(QColor(255 / 4.0*gi, 160, 50, 150)));
//        widget->SetPresentPriceVisible(true);
//        // generate random walk data:
//        QVector<double> time(250), value(250);
//        for (int i = 0; i < 250; ++i)
//        {
//            time[i] = now + 24 * 3600 * i;
//            if (i == 0)
//                value[i] = (i / 50.0 + 1)*(rand() / (double)RAND_MAX - 0.5);
//            else
//                value[i] = qFabs(value[i - 1])*(1 + 0.02 / 4.0*(4 - gi)) + (i / 50.0 + 1)*(rand() / (double)RAND_MAX - 0.5);
//        }
//        widget6->GetGraph()->setData(time, value);
//    }
//    // configure bottom axis to show date and time instead of number:
//    // set a more compact font size for bottom and left axis tick labels:
//    widget6->GetAxis(QCPAxis::atBottom)->setTickLabelFont(QFont(QFont().family(), 8));
//    widget6->GetAxis(QCPAxis::atLeft)->setTickLabelFont(QFont(QFont().family(), 8));

//    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
//    dateTicker->setDateTimeFormat("d. MMMM\nyyyy");
//    widget6->GetAxis(QCPAxis::atBottom)->setTicker(dateTicker);

//    widget6->GetAxis(QCPAxis::atBottom)->setLabel("Date");
//    widget6->GetAxis(QCPAxis::atLeft)->setLabel("Random wobbly lines value");
//    // make top and right axes visible but without ticks and labels:
//    // set axis ranges to show all data:
//    widget6->GetAxis(QCPAxis::atBottom)->setRange(now, now + 24 * 3600 * 249);
//    widget6->GetAxis(QCPAxis::atLeft)->setRange(0, 60);
//    widget6->GetAxis(QCPAxis::atBottom)->setTickLabels(true);
//    widget6->SetInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);
//    widget6->SetLineTracerEnable(true);
//    widget6->SetMoveTipLabel(true);

    //k线测试
//	FinancialWidget * widget = new FinancialWidget;
//	FinancialPlot * widget5 = widget->GetFinancialPlot();
//	//widget5->legend->setVisible(true);
//	ui.widget_22->SetContentWidget(widget);
//	ui.widget_22->AddQuota(QStringLiteral("test1"), 12);
//	ui.widget_22->AddQuota(QStringLiteral("test2"), 22);
//	// generate two sets of random walk data (one for candlestick and one for ohlc chart):
//	int n = 500;
//	QVector<double> time(n), value1(n), value2(n);
//	QDateTime start = QDateTime(QDate(2014, 6, 11));
//	start.setTimeSpec(Qt::UTC);
//	double startTime = start.toTime_t();
//	double binSize = 3600 * 24; // bin data in 1 day intervals
//	time[0] = startTime;
//	value1[0] = 60;
//	value2[0] = 20;
//	qsrand(9);
//	for (int i = 1; i < n; ++i)
//	{
//		time[i] = startTime + 3600 * i;
//		value1[i] = value1[i - 1] + (qrand() / (double)RAND_MAX - 0.5) * 10;
//		value2[i] = value2[i - 1] + (qrand() / (double)RAND_MAX - 0.5) * 3;
//	}
//
//	// create candlestick chart:
//
//	QCPFinancial *candlesticks = widget5->AddFinancial();
//	candlesticks->setName("Candlestick");
//	candlesticks->setChartStyle(QCPFinancial::csCandlestick);
//	candlesticks->data()->set(QCPFinancial::timeSeriesToOhlc(time, value1, binSize, startTime));
// 	candlesticks->setWidth(binSize*0.9);
//// 	candlesticks->setTwoColored(true);
//// 	candlesticks->setBrushPositive(QColor(245, 245, 245));
//// 	candlesticks->setBrushNegative(QColor(40, 40, 40));
//// 	candlesticks->setPenPositive(QPen(QColor(0, 0, 0)));
//// 	candlesticks->setPenNegative(QPen(QColor(0, 0, 0)));
//
//	// create ohlc chart:
//	QCPFinancial *ohlc = widget5->AddFinancial();
//	ohlc->setName("OHLC");
//	ohlc->setChartStyle(QCPFinancial::csOhlc);
//	ohlc->data()->set(QCPFinancial::timeSeriesToOhlc(time, value2, binSize / 3.0, startTime)); // divide binSize by 3 just to make the ohlc bars a bit denser
//	ohlc->setWidth(binSize*0.2);
//	ohlc->setTwoColored(true);
//
//	QCustomPlot * customPlot = ohlc->parentPlot();
//	// create bottom axis rect for volume bar chart:
//	QCPAxisRect *volumeAxisRect = new QCPAxisRect(customPlot);
//	customPlot->plotLayout()->addElement(1, 0, volumeAxisRect);
//	volumeAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 100));
//	volumeAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
//	volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
//	// bring bottom and main axis rect closer together:
//	customPlot->plotLayout()->setRowSpacing(0);
//	volumeAxisRect->setAutoMargins(QCP::msLeft | QCP::msRight | QCP::msBottom);
//	volumeAxisRect->setMargins(QMargins(0, 0, 0, 0));
//	// create two bar plottables, for positive (green) and negative (red) volume bars:
//	customPlot->setAutoAddPlottableToLegend(true);
//	QCPBars *volumePos = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
//	QCPBars *volumeNeg = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
//	for (int i = 0; i < n / 5; ++i)
//	{
//		int v = qrand() % 20000 + qrand() % 20000 + qrand() % 20000 - 10000 * 3;
//		(v < 0 ? volumeNeg : volumePos)->addData(startTime + 3600 * 5.0*i, qAbs(v)); // add data to either volumeNeg or volumePos, depending on sign of v
//	}
//	volumePos->setWidth(3600 * 4);
//	volumePos->setPen(Qt::NoPen);
//	volumePos->setBrush(QColor(100, 180, 110));
//	volumeNeg->setWidth(3600 * 4);
//	volumeNeg->setPen(Qt::NoPen);
//	volumeNeg->setBrush(QColor(180, 90, 90));
//
//	// interconnect x axis ranges of main and bottom axis rects:
//	connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), volumeAxisRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
//	connect(volumeAxisRect->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis, SLOT(setRange(QCPRange)));
//	// configure axes of both main and bottom axis rect:
//	QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
//	dateTimeTicker->setDateTimeSpec(Qt::UTC);
//	dateTimeTicker->setDateTimeFormat("dd. MMMM");
//	volumeAxisRect->axis(QCPAxis::atBottom)->setTicker(dateTimeTicker);
//	volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelRotation(15);
//	customPlot->xAxis->setBasePen(Qt::NoPen);
//	customPlot->xAxis->setTickLabels(false);
//	customPlot->xAxis->setTicks(false); // only want vertical grid in main axis rect, so hide xAxis backbone, ticks, and labels
//	customPlot->xAxis->setTicker(dateTimeTicker);
//	customPlot->rescaleAxes();
//	customPlot->xAxis->scaleRange(1.025, customPlot->xAxis->range().center());
//	customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
//
//	// make axis rects' left side line up:
//	QCPMarginGroup *group = new QCPMarginGroup(customPlot);
//	customPlot->axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight, group);
//	volumeAxisRect->setMarginGroup(QCP::msLeft | QCP::msRight, group);
//	widget5->SetInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);


    //==========================================================================================================
    //FinancialPlot * widget4 = new FinancialPlot;
    //ui.widget_22->SetContentWidget(widget4);
    //ui.widget_22->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    //// seconds of current time, we'll use it as starting point in time for data:
    //double now = QDateTime::currentDateTime().toTime_t();
    //srand(8); // set the random seed, so we always get the same random data
    //// create multiple graphs:
    //for (int gi = 0; gi < 5; ++gi)
    //{
    //	widget4->AddGraph();
    //	QPen pen;
    //	pen.setColor(QColor(0, 0, 255, 200));
    //	widget4->GetGraph()->setLineStyle(QCPGraph::lsLine);
    //	widget4->GetGraph()->setPen(pen);
    //	widget4->GetGraph()->setBrush(QBrush(QColor(255 / 4.0*gi, 160, 50, 150)));
    //	// generate random walk data:
    //	QVector<double> time(250), value(250);
    //	for (int i = 0; i < 250; ++i)
    //	{
    //		time[i] = now + 24 * 3600 * i;
    //		if (i == 0)
    //			value[i] = (i / 50.0 + 1)*(rand() / (double)RAND_MAX - 0.5);
    //		else
    //			value[i] = qFabs(value[i - 1])*(1 + 0.02 / 4.0*(4 - gi)) + (i / 50.0 + 1)*(rand() / (double)RAND_MAX - 0.5);
    //	}
    //	widget4->GetGraph()->setData(time, value);
    //}
    //// configure bottom axis to show date and time instead of number:
    //// set a more compact font size for bottom and left axis tick labels:
    //widget4->GetAxis(QCPAxis::atBottom)->setTickLabelFont(QFont(QFont().family(), 8));
    //widget4->GetAxis(QCPAxis::atLeft)->setTickLabelFont(QFont(QFont().family(), 8));

    //QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    //dateTicker->setDateTimeFormat("d. MMMM\nyyyy");
    //widget4->GetAxis(QCPAxis::atBottom)->setTicker(dateTicker);



    // set a fixed tick-step to one tick per month:
    // 	ui.widget_22->xAxis->setAutoTickStep(false);
    // 	ui.widget_22->xAxis->setTickStep(2628000); // one month in seconds
    // 	ui.widget_22->xAxis->setSubTickCount(3);
    // apply manual tick and tick label for left axis:
    // 	ui.widget_22->yAxis->setAutoTicks(false);
    // 	ui.widget_22->yAxis->setAutoTickLabels(false);
    // 	ui.widget_22->yAxis->setTickVector(QVector<double>() << 5 << 55);
    // 	ui.widget_22->yAxis->setTickVectorLabels(QVector<QString>() << "Not so\nhigh" << "Very\nhigh");
    // set axis labels:
// 	widget4->GetAxis(QCPAxis::atBottom)->setLabel("Date");
// 	widget4->GetAxis(QCPAxis::atLeft)->setLabel("Random wobbly lines value");
// 	// make top and right axes visible but without ticks and labels:
// 	// set axis ranges to show all data:
// 	widget4->GetAxis(QCPAxis::atBottom)->setRange(now, now + 24 * 3600 * 249);
// 	widget4->GetAxis(QCPAxis::atLeft)->setRange(0, 60);
// 	widget4->GetAxis(QCPAxis::atBottom)->setTickLabels(true);
// 	widget4->SetInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);
// 	widget4->SetLineTracerEnable(true);
// 	widget4->SetMoveTipLabel(true);
// 	widget4->SetPresentPriceVisible(true);
    // show legend:

//	FinancialPlot * widget3 = new FinancialPlot;
//	ui.widget_23->setStyleSheet(QString("QWidget{border:1 solid red;background:#121212;}"
//		));
//	ui.widget_23->AddQuota(QStringLiteral("test1:"), 12);
//	ui.widget_23->AddQuota(QStringLiteral("test2:"), 22);
//	ui.widget_23->SetContentWidget(widget3);
//
//	widget3->setAcceptDrops(true);
//	widget3->SetDragOrientation(Qt::Horizontal);
//
//	QCPGraph * graph3 = widget3->AddGraph();
//	QCPGraph * graph4 = widget3->AddGraph();
//	graph3->setPen(QPen(Qt::blue)); // line color blue for first graph
//	graph3->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
//	QVector<double> x(250), y0(250), y1(250);
//	for (int i = 0; i < 250; ++i)
//	{
//		x[i] = i;
//		y0[i] = i * 2;// qExp(-i / 150.0)*qCos(i / 10.0); // exponentially decaying cosine
//		y1[i] = 700 - i * 3;// qExp(-i / 150.0);              // exponential envelope
//	}
//
//// 	widget3->GetAxis(QCPAxis::atLeft)->setTickStep(0.2);
//// 	widget3->GetAxis(QCPAxis::atBottom)->setTickStep(4);//会被后边的widget步长重置
//
//	// make left and bottom axes always transfer their ranges to right and top axes:
//	connect(widget3->GetAxis(QCPAxis::atTop), SIGNAL(rangeChanged(QCPRange)), widget3->GetAxis(QCPAxis::atTop), SLOT(setRange(QCPRange)));
//	connect(widget3->GetAxis(QCPAxis::atRight), SIGNAL(rangeChanged(QCPRange)), widget3->GetAxis(QCPAxis::atRight), SLOT(setRange(QCPRange)));
//	// pass data points to graphs:
//	graph3->setData(x, y0);
//	graph4->setData(x, y1);
//
//	graph3->rescaleAxes();
//	//widget3->SetInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);
//
//	FinancialPlot * widget = new FinancialPlot;
//	widget->RegisiterBortherLine(widget3->GetCrossLine());
//	ui.widget_22->setStyleSheet(QString("QWidget{border:1 solid red;background:#121212;}"
//		));
//	ui.widget_22->AddQuota(QStringLiteral("test1:"), 12);
//	ui.widget_22->AddQuota(QStringLiteral("test2:"), 22);
//	ui.widget_22->SetContentWidget(widget);
//
//	widget->setAcceptDrops(true);
//	widget->SetDragOrientation(Qt::Horizontal);
//	widget->SetCursorShape(Qt::ClosedHandCursor);
//
//	// add two new graphs and set their look:
//	QCPGraph * graph0 = widget->AddGraph();
//	graph0->setPen(QPen(Qt::blue)); // line color blue for first graph
//	graph0->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
////	QCPGraph * graph1 = widget->AddGraph();
////	graph1->setPen(QPen(Qt::red)); // line color red for second graph
//	// generate some points of data (y0 for first, y1 for second graph):
//	//QVector<double> x(250), y0(250), y1(250);
//	//for (int i = 0; i < 250; ++i)
//	//{
//	//	x[i] = i;
//	//	y0[i] = qExp(-i / 150.0)*qCos(i / 10.0); // exponentially decaying cosine
//	//	y1[i] = qExp(-i / 150.0);              // exponential envelope
//	//}
//	//
//	// configure right and top axis to show ticks but no labels:
//	// (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
//// 	widget->GetAxis(QCP::TOP)->setVisible(false);
//// 	widget->GetAxis(QCP::LEFT)->setVisible(false);
//// 	widget->GetAxis(QCP::RIGHT)->setVisible(false);
//// 	widget->GetAxis(QCP::RIGHT)->setTickLabels(true);
//
//	//	widget->SetGridVisible(false);
//// 	widget->GetAxis(QCPAxis::atLeft)->setTickStep(0.3);
//// 	widget->GetAxis(QCPAxis::atBottom)->setTickStep(25);
//	widget->RegisiterBrotherRange(QCPAxis::atBottom, widget3);
//
//	// make left and bottom axes always transfer their ranges to right and top axes:
//	connect(widget->GetAxis(QCPAxis::atTop), SIGNAL(rangeChanged(QCPRange)), widget->GetAxis(QCPAxis::atTop), SLOT(setRange(QCPRange)));
//	connect(widget->GetAxis(QCPAxis::atRight), SIGNAL(rangeChanged(QCPRange)), widget->GetAxis(QCPAxis::atRight), SLOT(setRange(QCPRange)));
//	// pass data points to graphs:
//	graph0->setData(x, y1);
//
//	graph0->rescaleAxes();
//	widget->SetInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);
//	widget3->GetAxis(QCPAxis::atBottom)->setTickLabels(true);
//	widget3->SetLineTracerEnable(true);
//	widget3->SetMoveTipLabel(true);
//	widget3->SetPresentPriceVisible(true);
//	widget3->GetAxis(QCPAxis::atBottom)->axisRect()->setMargins(QMargins(15, -15, 15, 15));
}
////
////void plotdemo::removeSelectedGraph()
////{
////	if (ui.widget_17->selectedGraphs().size() > 0)
////	{
////		ui.widget_17->removeGraph(ui.widget_17->selectedGraphs().first());
////		ui.widget_17->replot();
////	}
////}
////
////void plotdemo::removeAllGraphs()
////{
////	ui.widget_17->clearGraphs();
////	ui.widget_17->replot();
////}
////
////void plotdemo::selectionChanged()
////{
////	/*
////	normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
////	the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
////	and the axis base line together. However, the axis label shall be selectable individually.
////
////	The selection state of the left and right axes shall be synchronized as well as the state of the
////	bottom and top axes.
////
////	Further, we want to synchronize the selection of the graphs with the selection state of the respective
////	legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
////	or on its legend item.
////	*/
////
////	// make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
////	if (ui.widget_17->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui.widget_17->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
////		ui.widget_17->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui.widget_17->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
////	{
////		ui.widget_17->xAxis2->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels);
////		ui.widget_17->xAxis->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels);
////	}
////	// make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
////	if (ui.widget_17->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui.widget_17->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
////		ui.widget_17->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui.widget_17->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
////	{
////		ui.widget_17->yAxis2->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels);
////		ui.widget_17->yAxis->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels);
////	}
////
////	// synchronize selection of graphs with selection of corresponding legend items:
////	for (int i = 0; i < ui.widget_17->graphCount(); ++i)
////	{
////		QCPGraph *graph = ui.widget_17->graph(i);
////		QCPPlottableLegendItem *item = ui.widget_17->legend->itemWithPlottable(graph);
////		if (item->selected() || graph->selected())
////		{
////			item->setSelected(true);
////		//	graph->setSelected(true);
////		}
////	}
////}
////
////void plotdemo::mousePress()
////{
////	// if an axis is selected, only allow the direction of that axis to be dragged
////	// if no axis is selected, both directions may be dragged
////
////	if (ui.widget_17->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
////		ui.widget_17->axisRect()->setRangeDrag(ui.widget_17->xAxis->orientation());
////	else if (ui.widget_17->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
////		ui.widget_17->axisRect()->setRangeDrag(ui.widget_17->yAxis->orientation());
////	else
////		ui.widget_17->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
////}
////
////void plotdemo::mouseWheel()
////{
////	// if an axis is selected, only allow the direction of that axis to be zoomed
////	// if no axis is selected, both directions may be zoomed
////
////	if (ui.widget_17->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
////		ui.widget_17->axisRect()->setRangeZoom(ui.widget_17->xAxis->orientation());
////	else if (ui.widget_17->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
////		ui.widget_17->axisRect()->setRangeZoom(ui.widget_17->yAxis->orientation());
////	else
////		ui.widget_17->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
////}
////
////// void plotdemo::titleDoubleClick(QMouseEvent* event, QCPPlotTitle* title)
////// {
////// 	Q_UNUSED(event)
////// 		// Set the plot title by double clicking on it
////// 		bool ok;
////// 	QString newTitle = QInputDialog::getText(this, "QCustomPlot example", "New plot title:", QLineEdit::Normal, title->text(), &ok);
////// 	if (ok)
////// 	{
////// 		title->setText(newTitle);
////// 		ui.widget_17->replot();
////// 	}
////// }
////
////void plotdemo::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
////{
////	// Set an axis label by double clicking on it
////	if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
////	{
////		bool ok;
////		QString newLabel = QInputDialog::getText(this, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
////		if (ok)
////		{
////			axis->setLabel(newLabel);
////			ui.widget_17->replot();
////		}
////	}
////}
////
////void plotdemo::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
////{
////	// Rename a graph by double clicking on its legend item
////	Q_UNUSED(legend)
////		if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
////		{
////			QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
////			bool ok;
////			QString newName = QInputDialog::getText(this, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
////			if (ok)
////			{
////				plItem->plottable()->setName(newName);
////				ui.widget_17->replot();
////			}
////		}
////}
////
////void plotdemo::graphClicked(QCPAbstractPlottable *plottable)
////{
////	//	ui->statusBar->showMessage(QString("Clicked on graph '%1'.").arg(plottable->name()), 1000);
////}
////
void plotdemo::addRandomGraph()
{
    int n = 50; // number of points in graph
    double xScale = (rand() / (double)RAND_MAX + 0.5) * 2;
    double yScale = (rand() / (double)RAND_MAX + 0.5) * 2;
    double xOffset = (rand() / (double)RAND_MAX - 0.5) * 4;
    double yOffset = (rand() / (double)RAND_MAX - 0.5) * 5;
    double r1 = (rand() / (double)RAND_MAX - 0.5) * 2;
    double r2 = (rand() / (double)RAND_MAX - 0.5) * 2;
    double r3 = (rand() / (double)RAND_MAX - 0.5) * 2;
    double r4 = (rand() / (double)RAND_MAX - 0.5) * 2;
    QVector<double> x(n), y(n);
    for (int i = 0; i < n; i++)
    {
        x[i] = (i / (double)n - 0.5)*10.0*xScale + xOffset;
        y[i] = (qSin(x[i] * r1 * 5)*qSin(qCos(x[i] * r2)*r4 * 3) + r3*qCos(qSin(x[i])*r4 * 2))*yScale + yOffset;
    }

    ui.widget_17->addGraph();
    ui.widget_17->graph()->setName(QString("New graph %1").arg(ui.widget_17->graphCount() - 1));
    ui.widget_17->graph()->setData(x, y);
    ui.widget_17->graph()->setLineStyle((QCPGraph::LineStyle)(rand() % 5 + 1));
    if (rand() % 100 > 75)
        ui.widget_17->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand() % 9 + 1)));
    QPen graphPen;
    graphPen.setColor(QColor(rand() % 245 + 10, rand() % 245 + 10, rand() % 245 + 10));
    graphPen.setWidthF(rand() / (double)RAND_MAX * 2 + 1);
    ui.widget_17->graph()->setPen(graphPen);
    ui.widget_17->replot();
}
////
////void plotdemo::contextMenuRequest(QPoint pos)
////{
////	QMenu *menu = new QMenu(this);
////	menu->setAttribute(Qt::WA_DeleteOnClose);
////
////	if (ui.widget_17->legend->selectTest(pos, false) >= 0) // context menu on legend requested
////	{
////		menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop | Qt::AlignLeft));
////		menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop | Qt::AlignHCenter));
////		menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop | Qt::AlignRight));
////		menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom | Qt::AlignRight));
////		menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom | Qt::AlignLeft));
////	}
////	else  // general context menu on graphs requested
////	{
////		menu->addAction("Add random graph", this, SLOT(addRandomGraph()));
////		if (ui.widget_17->selectedGraphs().size() > 0)
////			menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph()));
////		if (ui.widget_17->graphCount() > 0)
////			menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));
////	}
////
////	menu->popup(ui.widget_17->mapToGlobal(pos));
////}
