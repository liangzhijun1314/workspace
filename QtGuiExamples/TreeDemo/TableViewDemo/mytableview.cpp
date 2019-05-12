#include "mytableview.h"
#include <QPainter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QDate>
#include <QScrollBar>
#include <QMessageBox>

#if (QT_VERSION >= QT_VERSION_CHECK(4, 4, 0))
#include <QPrintPreviewDialog>
#endif

static inline double mmToInches(double mm) { return mm * 0.039370147; }

QString headertext =
    "<table width=\"100%\">"
    "  <tr>"
    "    <td align=\"left\"><strong>%1</strong></td>"
    "    <td align=\"right\"><strong>&date;</strong></td>"
    "  </tr>"
    "</table>";

QString footertext = "<p align=\"right\"><strong>&page;</strong></p>";

MyTableView::MyTableView()
    :print_printer(new QPrinter(QPrinter::ScreenResolution)),
    print_leftmargin(15.0), print_rightmargin(15.0), print_topmargin(15.0),
    print_bottommargin(15.0), print_spacing(5.0),
    print_headersize(10.0), print_headerrule(0.5), print_headertext(QString()),
    print_footersize(10.0), print_footerrule(0.5), print_footertext(QString())
{
    print_printer->setFullPage(true);
    print_printer->setOrientation(QPrinter::Portrait);

    // for convenience, default to US_Letter for C/US/Canada
    // NOTE: bug in Qt, this value is not loaded by QPrintDialog
    switch (QLocale::system().country())
    {
    case QLocale::AnyCountry:
    case QLocale::Canada:
    case QLocale::UnitedStates:
    case QLocale::UnitedStatesMinorOutlyingIslands:
        print_printer->setPageSize(QPrinter::Letter); break;
    default:
        print_printer->setPageSize(QPrinter::A4); break;
    }
}

MyTableView::~MyTableView()
{
    delete print_printer;
}

QPrinter::PageSize MyTableView::print_pageSize() const
{
    return print_printer->pageSize();
}

void MyTableView::print_setPageSize(QPrinter::PageSize size)
{
    print_printer->setPageSize(size);
}

QPrinter::Orientation MyTableView::print_orientation() const
{
    return print_printer->orientation();
}

void MyTableView::print_setOrientation(QPrinter::Orientation orientation)
{
    print_printer->setOrientation(orientation);
}

double MyTableView::print_leftMargin() const
{
    return print_leftmargin;
}

void MyTableView::print_setLeftMargin(double margin)
{
    if ((margin > 0) && (margin < print_printer->paperRect().width() / 2))
    {
        print_leftmargin = margin;
    }
    else
    {
        print_leftmargin = 0;
    }
}

double MyTableView::print_rightMargin() const
{
    return print_rightmargin;
}

void MyTableView::print_setRightMargin(double margin)
{
    if ((margin > 0) && (margin < print_printer->paperRect().width() / 2))
    {
        print_rightmargin = margin;
    }
    else
    {
        print_rightmargin = 0;
    }
}

double MyTableView::print_topMargin() const
{
    return print_topmargin;
}

void MyTableView::print_setTopMargin(double margin)
{
    if ((margin > 0) && (margin < print_printer->paperRect().height() / 4))
    {
        print_topmargin = margin;
    }
    else
    {
        print_topmargin = 0;
    }
}

double MyTableView::print_bottomMargin() const
{
    return print_bottommargin;
}

void MyTableView::print_setBottomMargin(double margin)
{
    if ((margin > 0) && (margin < print_printer->paperRect().height() / 4))
    {
        print_bottommargin = margin;
    }
    else
    {
        print_bottommargin = 0;
    }
}

void MyTableView::print_setMargins(double margin)
{
    if ((margin > 0)
        && (margin < print_printer->paperRect().height() / 2)
        && (margin < print_printer->paperRect().width() / 2))
    {
        print_leftmargin = print_rightmargin = print_topmargin = print_bottommargin = margin;
    }
    else
    {
        print_leftmargin = print_rightmargin = print_topmargin = print_bottommargin = 0;
    }
}

double MyTableView::print_spacings() const
{
    return print_spacing;
}

void MyTableView::print_setSpacings(double spacing)
{
    if ((spacing > 0) && (spacing <= print_printer->paperRect().height() / 8))
    {
        print_spacing = spacing;
    }
    else
    {
        print_spacing = 0;
    }
}

double MyTableView::print_headerSize() const
{
    return print_headersize;
}

void MyTableView::print_setHeaderSize(double size)
{
    if ((size > 0) && (size <= print_printer->paperRect().height() / 8))
    {
        print_headersize = size;
    }
    else
    {
        print_headersize = 0;
    }
}

double MyTableView::print_headerRule() const
{
    return print_headerrule;
}

void MyTableView::print_setHeaderRule(double pointsize)
{
    print_headerrule = qMax(0.0, pointsize);
}

const QString &MyTableView::print_headerText() const
{
    return print_headertext;
}

void MyTableView::print_setHeaderText(const QString &text)
{
    print_headertext = text;
}

double MyTableView::print_footerSize() const
{
    return print_footersize;
}

void MyTableView::print_setFooterSize(double size)
{
    if ((size > 0) && (size <= print_printer->paperRect().height() / 8))
    {
        print_footersize = size;
    }
    else
    {
        print_footersize = 0;
    }
}

double MyTableView::print_footerRule() const
{
    return print_footerrule;
}

void MyTableView::print_setFooterRule(double pointsize)
{
    print_footerrule = qMax(0.0, pointsize);
}

const QString &MyTableView::print_footerText() const
{
    return print_footertext;
}

void MyTableView::print_setFooterText(const QString &text)
{
    print_footertext = text;
}


void MyTableView::print_print(const QString &caption)
{
    // setup printer
    print_printer->setOutputFormat(QPrinter::NativeFormat);
    print_printer->setOutputFileName(QString());

    print_setHeaderText(headertext.arg(caption));
    print_setFooterText(footertext);

    // show print dialog
    QPrintDialog dialog(print_printer, this);
    dialog.setWindowTitle(caption.isEmpty() ? "Print view" : caption);
    if (dialog.exec() == QDialog::Rejected) return;

    // print it
    print_print(print_printer);
}


void MyTableView::print_exportPdf(const QString &caption,
                                    const QString &filename)
{
    // file save dialog
    QString dialogcaption = caption.isEmpty() ? "Export PDF" : caption;
    QString exportname;
    if (QFile::exists(filename))
    {
        exportname = filename;
    }
    else
    {
        exportname = QFileDialog::getSaveFileName(this, dialogcaption,
                                                  filename, "*.pdf");
    }
    if (exportname.isEmpty()) return;
    if (QFileInfo(exportname).suffix().isEmpty())
        exportname.append(".pdf");

    // setup printer
    print_printer->setOutputFormat(QPrinter::PdfFormat);
    print_printer->setOutputFileName(exportname);

    // print it
    print_print(print_printer);

    QMessageBox::information(this, tr("Export PDF"), tr("Done"));
}

void MyTableView::print_preview(const QString &caption)
{
#if (QT_VERSION >= QT_VERSION_CHECK(4, 4, 0))

    print_setHeaderText(headertext.arg(caption));
    print_setFooterText(footertext);

    QPrintPreviewDialog *dialog = new QPrintPreviewDialog(print_printer, this);
    dialog->setWindowTitle(caption.isEmpty() ? "Print Preview" : caption);

    connect(dialog, SIGNAL(paintRequested(QPrinter*)),
            this, SLOT(print_print(QPrinter*)));

    // preview it
    dialog->exec();
    delete dialog;
#endif
}

QRectF MyTableView::print_paperRect(QPaintDevice *device)
{
    // calculate size of paper
    QRectF rect = print_printer->paperRect();
    // adjust for DPI
    rect.setWidth(rect.width() *
                  device->logicalDpiX() / print_printer->logicalDpiX());
    rect.setHeight(rect.height() *
                  device->logicalDpiY() / print_printer->logicalDpiY());

    return rect;
}


QRectF MyTableView::print_contentRect(QPaintDevice *device)
{
    // calculate size of content (paper - margins)
    QRectF rect = print_paperRect(device);

    rect.adjust(mmToInches(print_leftmargin) * device->logicalDpiX(),
                mmToInches(print_topmargin) * device->logicalDpiY(),
                -mmToInches(print_rightmargin) * device->logicalDpiX(),
                -mmToInches(print_bottommargin) * device->logicalDpiY());

    // header
    if (print_headersize > 0) {
        rect.adjust(0, mmToInches(print_headersize) * device->logicalDpiY(), 0, 0);
        rect.adjust(0, mmToInches(print_spacing) * device->logicalDpiY(), 0, 0);
    }
    // footer
    if (print_footersize > 0) {
        rect.adjust(0, 0, 0, -mmToInches(print_footersize) * device->logicalDpiY());
        rect.adjust(0, 0, 0, -mmToInches(print_spacing) * device->logicalDpiY());
    }

    return rect;
}


QRectF MyTableView::print_headerRect(QPaintDevice *device)
{
    QRectF rect = print_paperRect(device);
    rect.adjust(mmToInches(print_leftmargin) * device->logicalDpiX(),
                mmToInches(print_topmargin) * device->logicalDpiY(),
                -mmToInches(print_rightmargin) * device->logicalDpiX(), 0);

    //(print_headerrule / 144.0);

    rect.setBottom(rect.top() +
                   mmToInches(print_headersize) * device->logicalDpiY());

    return rect;
};


QRectF MyTableView::print_footerRect(QPaintDevice *device)
{
    QRectF rect = print_paperRect(device);
    rect.adjust(mmToInches(print_leftmargin) * device->logicalDpiX(), 0,
                -mmToInches(print_rightmargin) * device->logicalDpiX(),
                -mmToInches(print_bottommargin) * device->logicalDpiY());

    rect.setTop(rect.bottom() -
                mmToInches(print_footersize) * device->logicalDpiY());

    return rect;
};

// print() ////////////////////////////////////////////////////////////////////
// Common printing routine. Print tempdoc_ to given printer device.

void MyTableView::print_print(QPrinter *printer)
{
    if (!printer) return;

    print_currow = 0;
    print_curcol = 0;

    // get original size
    QSize originalsize = size();
    // set scroll bars to invisible
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // to iterate through pages we have to worry about
    // copies, collation, page range, and print order

    QPainter painter(printer);
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform, true);

    // get num copies
    int doccopies;
    int pagecopies;
    if (printer->collateCopies())
    {
        doccopies = 1;
        pagecopies = printer->numCopies();
    }
    else
    {
        doccopies = printer->numCopies();
        pagecopies = 1;
    }

    // get page range from content
    QRectF rect = print_contentRect(painter.device());
    //get 'vertical pages'
    int iheight, iwidth, i = 0, maxVpage = 0, maxHpage = 0;
    int rowCount = model()->rowCount();
    while(i < rowCount)
    {
        iheight = 0;
        maxVpage++;
        while(i < rowCount && (iheight + rowHeight(i)) < rect.height())
        {//new page
            iheight += rowHeight(i++);
        }
    }

    int colCount = model()->columnCount();
    i = 0;
    while(i < colCount)
    {
        iwidth = 0;
        maxHpage++;
        while(i < colCount && (iwidth + columnWidth(i)) < rect.width())
        {//new page
            iwidth += columnWidth(i++);
        }
    }
    // get page range
    int firstpage = printer->fromPage();
    int lastpage = printer->toPage();

    if (firstpage == 0 && lastpage == 0)
    { // all pages
        firstpage = 1;
        lastpage = maxVpage * maxHpage;
    }
    //
    // print order
    bool ascending = true;
    // sorry - only ascending is supported now
    /*
    if (printer->pageOrder() == QPrinter::LastPageFirst)
    {
        int tmp = firstpage;
        firstpage = lastpage;
        lastpage = tmp;
        ascending = false;
    }
    */

    //set the view
    resize(print_contentRect(painter.device()).size().toSize());

    QScrollBar *barV = verticalScrollBar();
    QScrollBar *barH = this->horizontalScrollBar();
    int icurbarposV = barV->value();
    int icurbarposH = barH->value();

    // loop through and print pages
    for (int dc=0; dc<doccopies; dc++)
    {
        //scroll to the top left
        barV->setValue(barV->minimum());
        barH->setValue(barH->minimum());

        int pagenum = firstpage;
        while (true)
        {
            for (int pc=0; pc<pagecopies; pc++)
            {
                if (printer->printerState() == QPrinter::Aborted ||
                    printer->printerState() == QPrinter::Error)
                {
                    return;
                }
                // print page
                print_paintPage(&painter, pagenum);
                if (pc < pagecopies-1) printer->newPage();
            }
            if (pagenum == lastpage)
                break;
            if (ascending)
                pagenum++;
            else
                pagenum--;
            printer->newPage();
        }

        if (dc < doccopies-1) printer->newPage();

        // set all rows and colums visible
        for(int r = 0 ; r < model()->rowCount() ; r++)
            setRowHidden(r, false);
        for(int c = 0 ; c < model()->columnCount() ; c++)
            setColumnHidden(c, false);
    }

    //restore scroll bar position
    barV->setValue( icurbarposV );
    barH->setValue( icurbarposH );

    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->resize(originalsize);
}

void MyTableView::print_paintPage(QPainter *painter, int pagenum)
{
    QRectF rect;
    double onepoint = painter->device()->logicalDpiY() / 72.0;

    // header
    if (print_headersize > 0)
    {
        rect = print_headerRect(painter->device());
        if (print_headerrule > 0.0)
        {
            painter->save();
            // allow space between rule and header
            painter->translate(0, onepoint + (print_headerrule * onepoint / 2.0));
            painter->setPen(QPen(Qt::black, print_headerrule * onepoint));
            painter->drawLine(rect.bottomLeft(), rect.bottomRight());
            painter->restore();
        }

        // replace page variables
        QString header = print_headertext;
        header.replace("&page;", QString::number(pagenum));
        //date
        header.replace("&date;", QDate::currentDate().toString("yyyy-MM-dd "));

        painter->save();
        painter->translate(rect.left(), rect.top());
        QRectF clip(0, 0, rect.width(), rect.height());
        QTextDocument doc;
        doc.setUseDesignMetrics(true);
        doc.setHtml(header);
        doc.documentLayout()->setPaintDevice(painter->device());
        doc.setPageSize(rect.size());

        // align text to bottom
        double newtop = clip.bottom() - doc.size().height();
        clip.setHeight(doc.size().height());
        painter->translate(0, newtop);

        doc.drawContents(painter, clip);
        painter->restore();
    }

    // footer
    if (print_footersize > 0)
    {
        rect = print_footerRect(painter->device());
        if (print_footerrule > 0.0)
        {
            painter->save();
            // allow space between rule and footer
            painter->translate(0, -onepoint + (print_footerrule * onepoint / 2.0));
            painter->setPen(QPen(Qt::black, print_footerrule * onepoint));
            painter->drawLine(rect.topLeft(), rect.topRight());
            painter->restore();
        }

        // replace page variables
        QString footer = print_footertext;
        footer.replace("&page;", QString::number(pagenum));
        //date
        //footer.replace("&date;", QDate::currentDate().toString());


        painter->save();
        painter->translate(rect.left(), rect.top());
        QRectF clip(0, 0, rect.width(), rect.height());
        QTextDocument doc;
        doc.setUseDesignMetrics(true);
        doc.setHtml(footer);
        doc.documentLayout()->setPaintDevice(painter->device());
        doc.setPageSize(rect.size());
        doc.drawContents(painter, clip);
        painter->restore();
    }

    // content
    painter->save();

    rect = print_contentRect(painter->device());
    //painter->translate(rect.left(), rect.top() - (pagenum-1) * rect.height());
    painter->translate(rect.left(), rect.top());
    //painter->scale(4.5, 4.5);
    //QRectF clip(0, (pagenum-1) * rect.height(), rect.width(), rect.height());

    // ok, now render to printer
    render(painter);
    painter->restore();

    //hide the rows which have been printed
    int iheight = 0;
    while(print_currow < model()->rowCount() &&
          (iheight + rowHeight(print_currow)) < rect.height())
    {
        iheight += rowHeight(print_currow);
        setRowHidden(print_currow++, true);
    }

    if(print_currow >= model()->rowCount())
    {
        print_currow = 0;
        // set all rows visible
        for(int r = 0 ; r < model()->rowCount() ; r++)
            setRowHidden(r, false);

        // other pages exist?
        int iwidth = 0;
        while(print_curcol < model()->columnCount() &&
              (iwidth + columnWidth(print_curcol)) < rect.width())
        {
            iwidth += columnWidth(print_curcol);
            setColumnHidden(print_curcol++, true);
        }
    }
}
