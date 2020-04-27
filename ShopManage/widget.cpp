#include "widget.h"
#include "ui_widget.h"
#include "frmnavlistviewform.h"
#include "changepassword.h"
#include "backview.h"

#include <QWidget>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQueryModel>   //创建Query模型
#include <QSqlQuery>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    this->setWindowTitle("登陆界面");
    //打开数据库
     setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    setFixedSize(this->width(),this->height());
    LinkMysql();
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image/016.jpg")));
    this->setPalette(pal);
    //ui->lineEdit_userName->setTextMargins(1,0,0,0);
    ui->lineEdit_passWord->setEchoMode(QLineEdit::Password);



}

Widget::~Widget()
{
    delete ui;
}

//链接数据库
void Widget::LinkMysql()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("rm-bp1w73ygn47t2obnu0o.mysql.rds.aliyuncs.com");//数据库服务器的IP
    db.setUserName("root"); //数据库用户名
    db.setPassword("1996jackLWB!@#"); //密码
    db.setDatabaseName("marketman"); //使用哪个数据库
    if(!db.open())
    {
        QMessageBox::warning(this,"连接失败",db.lastError().text());
        return;
    }
    else {
        //QMessageBox::warning(this,"连接成功");
    }

}


void Widget::on_pushButton_3_clicked()
{
    QString userName = ui->lineEdit_userName->text();

    ChangePassword *cg = new ChangePassword;

    //cg->ChangePassword_userName(userName);

    this->hide();
    cg->show();
}


void Widget::on_pB_loginIn_clicked()
{
    QString userName = ui->lineEdit_userName->text();
    QString passWord = ui->lineEdit_passWord->text();

    QSqlQuery query;
    QString sql = QString("select * from user where user_name = '%1' and user_password = '%2'")
            .arg(userName).arg(passWord);

    query.exec(sql);

    if(query.next()) {
        //qDebug()<<"JMC";
        this->hide();

        if(query.value(7).toString() == "1")
        {
            //跳转界面至前台界面
            f->show();
            f->work_name = userName;
            f->work_passage = passWord;
        }
        else
        {
            b = new backview(NULL,userName,passWord);

            b->show();
        }
    }
    else{
        QMessageBox::information(NULL, "错误", "用户名或密码错误！！！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        //qDebug()<<"LLWWBB";
    }


}


