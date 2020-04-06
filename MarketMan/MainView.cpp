#include "MainView.h"
#include "ui_MainView.h"
#include "navlistview.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    this->SqlLink();
    this->SetListItem();
}

void MainView::SqlLink()
{
     QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","local");
     db.setHostName("127.0.0.1");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
     db.setPort(3306);                 //连接数据库端口号，与设置一致
     db.setDatabaseName("marketman");      //连接数据库名，与设置一致
     db.setUserName("root");          //数据库用户名，与设置一致
     db.setPassword("123456");    //数据库密码，与设置一致
     db.open();
     if(!db.open())
     {
         qDebug()<<"不能连接"<<"connect to mysql error"<<db.lastError().text();
         return ;
     }
     else
     {
         qDebug()<<"连接成功"<<"connect to mysql OK";
     }
}

void MainView::SetListItem()
{
    ui->listView->readData(":/image/config.xml");

   //connect(this->ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(press()));
    //connect(this->ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(press(QModelIndex)));
}


MainView::~MainView()
{
    delete ui;
}

void MainView::on_listView_pressed(const QModelIndex &index)
{

    QString str = index.data().toString();

    if(str == "主界面")
        this->ui->stackedWidget->setCurrentIndex(0);
    else if(str == "商品类别")
        this->ui->stackedWidget->setCurrentIndex(1);
}
