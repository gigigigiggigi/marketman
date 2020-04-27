#include "changepassword.h"
#include "ui_changepassword.h"
#include "widget.h"

#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQueryModel>   //创建Query模型
#include <QSqlQuery>

ChangePassword::ChangePassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePassword)
{
    ui->setupUi(this);
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/007.jpg")));
    this->setPalette(pal);
     ui->lineEdit_old->setEchoMode(QLineEdit::Password);
     ui->lineEdit_new->setEchoMode(QLineEdit::Password);
     ui->lineEdit_confirm->setEchoMode(QLineEdit::Password);

}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::on_pB_confirm_clicked()
{

    //更改数据库
    QString oldUsername = ui->lineEdit_oldUsername->text();
    QString oldPassword = ui->lineEdit_old->text();
    QString newPassword = ui->lineEdit_new->text();
    QString confirmPassword = ui->lineEdit_confirm->text();

    //查找数据库
    QSqlQuery query;
    QString sql = QString("select * from user where user_name = '%1'")
            .arg(oldUsername);
    query.exec(sql);
    QString getPassword;
    while (query.next())  {
        getPassword = query.value("user_password").toString();
    }

    //更改数据库
    if(oldPassword == getPassword && newPassword == confirmPassword)
    {
        QString sql = QString("update user set user_password = '%1' where user_name = '%2'")
                .arg(newPassword)
                .arg(oldUsername);
        query.exec(sql);

        QMessageBox::information(NULL, "成功", "密码更改成功",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        //跳转
        this->hide();
        Widget *loginIn = new Widget;
        loginIn->show();
    }
    else if (oldPassword != getPassword) {
        QMessageBox::information(NULL, "错误", "用户名或原密码错误！！！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else {
        QMessageBox::information(NULL, "错误", "请重新确认密码",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}
