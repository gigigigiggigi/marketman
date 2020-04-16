#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "backview.h"
#include "frmnavlistviewform.h"
#include "changepassword.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void LinkMysql();

private slots:
    void on_pushButton_3_clicked();

    void on_pB_loginIn_clicked();


private:
    Ui::Widget *ui;
    frmNavListViewForm *f = new frmNavListViewForm;
    backview *b;
};

#endif // WIDGET_H
