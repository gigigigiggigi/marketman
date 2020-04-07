#include "MainView.h"
#include "ui_MainView.h"
#include "navlistview.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqltablemodel>

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    setFixedSize(this->width(),this->height());
    SqlLink();
    this->SetListItem();
}

void MainView::SqlLink()
{
     db=QSqlDatabase::addDatabase("QMYSQL","ttt");
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
         qDebug()<<"连接成功"<<"connect to mysql OK"<<db.lastError().text();
        // QSqlQuery query = QSqlQuery(db);
         //query.exec("create table student(id INTEGER PRIMARY KEY autoincrement,  name nvarchar(20), age int)"); //id自动增加
        // db.exec("insert into student values(1,'小明', 14)");
         //query.exec("insert into student values(2,'小王',15)");

     }
}

void MainView::SetListItem()
{
    ui->listView->readData(":/image/config.xml");

   //connect(this->ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(press()));
    //connect(this->ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(press(QModelIndex)));
}

void MainView::SetGoodsTypeTable()
{

   // QSqlQuery query = QSqlQuery(db);
    QSqlTableModel *pModel = new QSqlTableModel(this,db);
    pModel->setTable("goodtype");
    pModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    pModel->select(); //选取整个表的所有行
    pModel->setHeaderData(0, Qt::Horizontal, tr("商品类别"));
    pModel->removeColumn(0);

    ui->tableGoodstype->setModel(pModel);
    ui->tableGoodstype->setColumnWidth(0,ui->tableGoodstype->width());

    ui->tableGoodstype->show();


  //  QSqlQueryModel *model = new QSqlQueryModel(this);

  //  model->setQuery(QString("select * from goodtype"),db);
   // model->setHeaderData(1, Qt::Horizontal, QObject::tr("商品类别"));


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
    {
        this->ui->stackedWidget->setCurrentIndex(1);
        SetGoodsTypeTable();
    }
    else if(str == "商品录入")
        this->ui->stackedWidget->setCurrentIndex(3);
    else if(str == "商品信息")
        this->ui->stackedWidget->setCurrentIndex(2);

}

void MainView::on_pushButton_clicked()
{
    QString str = ui->lineEdit_goodtype->text();
    QSqlQuery query = QSqlQuery(db);
    QString sql  = QString("insert into goodtype(goodtype_type) values('%1')").arg(str);
    bool b = query.exec(sql);
    if(b)
    {
        QMessageBox::information(this,"提示","添加成功");
        ui->lineEdit_goodtype->setText("");
    }

    else
        QMessageBox::information(this,"提示","失败");
}
