#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QWidget>
#include "widget.h"

namespace Ui {
class ChangePassword;
}

class ChangePassword : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePassword(QWidget *parent = 0);
    ~ChangePassword();
    void ChangePassword_userName(QString username);

private slots:
    void on_pB_confirm_clicked();

private:
    Ui::ChangePassword *ui;

};

#endif // CHANGEPASSWORD_H
