#ifndef FRMSHOWAPI_H
#define FRMSHOWAPI_H

#include <QWidget>

namespace Ui {
class frmShowAPI;
}

class frmShowAPI : public QWidget
{
    Q_OBJECT

public:
    explicit frmShowAPI(QWidget *parent = 0);
    ~frmShowAPI();

private:
    Ui::frmShowAPI *ui;
    QStringList colorList;

private slots:
    void InitForm();
    void ChangeColor();
};

#endif // FRMSHOWAPI_H
