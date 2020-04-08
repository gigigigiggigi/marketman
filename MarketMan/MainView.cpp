#include "MainView.h"
#include "ui_MainView.h"
#include "navlistview.h"
#include "intable_model.h"
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
    SetModels();
}
MainView::~MainView()
{
    delete ui;
}

void MainView::SqlLink()
{
     db=QSqlDatabase::addDatabase("QMYSQL","ttt");
     db.setHostName("127.0.0.1");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
     db.setPort(3306);                 //连接数据库端口号，与设置一致
     db.setDatabaseName("marketman2");      //连接数据库名，与设置一致
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
     }
}



void MainView::SetListItem()
{
    ui->listView->readData(":/image/config.xml");

    //connect(this->ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(press()));
    //connect(this->ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(press(QModelIndex)));
}


void MainView::InitGoodadd()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(QString("select goodtype_type from goodtype"),db);
    ui->cboc_goodadd_goodtype->setModel(model);

    QSqlQueryModel *model2 = new QSqlQueryModel(this);
    model2->setQuery(QString("select suppliers_name from suppliers"),db);
    ui->cboc_goodadd_supllier->setModel(model2);

    QRegExp regx("^([0]|[1-9][0-9]{0,99})(?:\\.\\d{1,4})?$|(^\\t?$)");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEdit_goodadd_id);
    ui->lineEdit_goodadd_id->setValidator(validator);
    ui->lineEdit_goodadd_barcode->setValidator(validator);
    ui->lineEdit_goodadd_onground->setValidator(validator);
    ui->lineEdit_goodadd_saled->setValidator(validator);
    ui->lineEdit_goodadd_stock->setValidator(validator);
    ui->lineEdit_goodadd_warnline->setValidator(validator);

    ui->lineEdit_goodadd_inprice->setValidator(validator);
    ui->lineEdit_goodadd_outprice->setValidator(validator);
    ui->lineEdit_goodadd_pricecut->setValidator(validator);

}


void MainView::SetGoodsTypeTable()
{
    pModel_tablegoodtype = new intable_model(this,db);
    pModel_tablegoodtype->setTable("goodtype");
    pModel_tablegoodtype->setEditStrategy(QSqlTableModel::OnManualSubmit);
    pModel_tablegoodtype->select(); //选取整个表的所有行
    pModel_tablegoodtype->setHeaderData(1, Qt::Horizontal, tr("商品类别"));

    ui->tableGoodstype->setModel(pModel_tablegoodtype);
    ui->tableGoodstype->setColumnWidth(1,ui->tableGoodstype->width());
    ui->tableGoodstype->setColumnHidden(0,true);
    ui->tableGoodstype->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tableGoodstype->show();



    // pModel->removeColumn(0);
    // ui->tableGoodstype->setSelectionMode( QAbstractItemView::SingleSelection);//设置选中单个
    // ui->tableGoodstype->setShowGrid(true);
    // ui->tableGoodstype->setGridStyle(Qt::SolidLine);
    // QSqlQueryModel *model = new QSqlQueryModel(this);
    // model->setQuery(QString("select * from goodtype"),db);
    // model->setHeaderData(1, Qt::Horizontal, QObject::tr("商品类别"));

}

void MainView::SetGoodsInfoTable()
{
    pModel_tablegoodinfo = new intable_model(this,db);
    pModel_tablegoodinfo->setTable("goods");
    pModel_tablegoodinfo->setEditStrategy(QSqlTableModel::OnManualSubmit);
    pModel_tablegoodinfo->select(); //选取整个表的所有行
    pModel_tablegoodinfo->setHeaderData(0, Qt::Horizontal, tr("商品编号"));
    pModel_tablegoodinfo->setHeaderData(1, Qt::Horizontal, tr("商品条码"));
    pModel_tablegoodinfo->setHeaderData(2, Qt::Horizontal, tr("商品名"));
    pModel_tablegoodinfo->setHeaderData(3, Qt::Horizontal, tr("商品类型"));
    pModel_tablegoodinfo->setHeaderData(5, Qt::Horizontal, tr("商品进价"));
    pModel_tablegoodinfo->setHeaderData(6, Qt::Horizontal, tr("商品售价"));
    pModel_tablegoodinfo->setHeaderData(7, Qt::Horizontal, tr("商品活动折扣"));
    pModel_tablegoodinfo->setHeaderData(8, Qt::Horizontal, tr("商品活动开始时间"));
    pModel_tablegoodinfo->setHeaderData(9, Qt::Horizontal, tr("商品活动结束时间"));
    pModel_tablegoodinfo->setHeaderData(10, Qt::Horizontal, tr("商品在架数"));
    pModel_tablegoodinfo->setHeaderData(11, Qt::Horizontal, tr("商品已售"));
    pModel_tablegoodinfo->setHeaderData(12, Qt::Horizontal, tr("商品库存警告线"));
    pModel_tablegoodinfo->setHeaderData(13, Qt::Horizontal, tr("商品库存"));
    pModel_tablegoodinfo->setHeaderData(14, Qt::Horizontal, tr("商品生产厂商"));
    pModel_tablegoodinfo->setHeaderData(15, Qt::Horizontal, tr("商品供货商"));

    ui->tableGoodsinfo->setModel(pModel_tablegoodinfo);

    ui->tableGoodsinfo->setColumnHidden(4,true);
    ui->tableGoodsinfo->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tableGoodsinfo->show();

}

void MainView::on_listView_pressed(const QModelIndex &index)
{

    QString str = index.data().toString();

    if(str == "主界面")
        this->ui->stackedWidget->setCurrentIndex(0);
    else if(str == "商品类别")
    {
        this->ui->stackedWidget->setCurrentIndex(1);
    }
    else if(str == "商品录入")
    {
        this->ui->stackedWidget->setCurrentIndex(3);
        InitGoodadd();
    }
    else if(str == "商品信息")
        this->ui->stackedWidget->setCurrentIndex(2);

}

void MainView::on_btnadd_goodtype_clicked()
{
    QString str = ui->lineEdit_goodtype->text();
    if(str=="")
    {
        QMessageBox::information(this,"提示","输入无效");
        return;
    }
    QSqlQuery query = QSqlQuery(db);
    QSqlQuery query2 = QSqlQuery(db);
    QString sql  = QString("insert into goodtype(goodtype_type) values('%1')").arg(str);
    QString sql2  = QString("select goodtype_type from goodtype where goodtype_type = '%1'").arg(str);
    query2.exec(sql2);
    while(query2.next())
    {
         QMessageBox::information(this,"提示","重复添加");
         return;
    }
    bool b = query.exec(sql);
    if(b)
    {
        QMessageBox::information(this,"提示","添加成功");
        pModel_tablegoodtype->select();
        ui->lineEdit_goodtype->setText("");
    }

    else
        QMessageBox::information(this,"提示","失败");
}

void MainView::on_btndelete_goodtype_clicked()
{
       QItemSelectionModel *sModel = ui->tableGoodstype->selectionModel();

       //取出模型中的索引
       QModelIndexList list = sModel->selectedRows();
       //删除所有选中的行
       bool b;
       if(list.size()>0)
       {
           for(int i=0; i < list.size(); i++){
               pModel_tablegoodtype->removeRow( list.at(i).row() );
           }

           int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"), QMessageBox::Yes,QMessageBox::No);

           if(ok == QMessageBox::Yes)
           {
               qDebug()<<"com in";
               pModel_tablegoodtype->submitAll();
               b =  pModel_tablegoodtype->database().commit();
               if(b)
               {
                   QMessageBox::information(this,"提示","删除成功");

               }
               else
                   QMessageBox::information(this,"提示","失败");
           }
           else
           {
               pModel_tablegoodtype->revertAll();
           }
       }



}

void MainView::SetModels()
{
    SetGoodsTypeTable();
    SetGoodsInfoTable();
}

void MainView::on_btnupdate_goodtype_clicked()
{
    int ok = QMessageBox::warning(this,tr("提交修改!"),tr("你确定提交修改吗？"), QMessageBox::Yes,QMessageBox::No);

    if(ok == QMessageBox::Yes)
    {
        qDebug()<<"com in";
        pModel_tablegoodtype->submitAll();
        bool b;
        b =  pModel_tablegoodtype->database().commit();
        if(b)
        {
            QMessageBox::information(this,"提示","修改成功");

        }
        else
            QMessageBox::information(this,"提示","失败");
    }

}

void MainView::on_btnupdate_goodinfo_clicked()
{
    int ok = QMessageBox::warning(this,tr("提交修改!"),tr("你确定提交修改吗？"), QMessageBox::Yes,QMessageBox::No);

    if(ok == QMessageBox::Yes)
    {
        qDebug()<<"com in";
        pModel_tablegoodinfo->submitAll();
        bool b;
        b =  pModel_tablegoodinfo->database().commit();
        if(b)
        {
            QMessageBox::information(this,"提示","修改成功");

        }
        else
            QMessageBox::information(this,"提示","失败");
    }
}

void MainView::on_btndelete_goodinfo_clicked()
{
    QItemSelectionModel *sModel = ui->tableGoodsinfo->selectionModel();

    //取出模型中的索引
    QModelIndexList list = sModel->selectedRows();
    //删除所有选中的行
    bool b;
    if(list.size()>0)
    {
        for(int i=0; i < list.size(); i++){
            pModel_tablegoodinfo->removeRow( list.at(i).row() );
        }

        int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"), QMessageBox::Yes,QMessageBox::No);

        if(ok == QMessageBox::Yes)
        {
            qDebug()<<"com in";
            pModel_tablegoodinfo->submitAll();
            b =  pModel_tablegoodinfo->database().commit();
            if(b)
            {
                QMessageBox::information(this,"提示","删除成功");

            }
            else
                QMessageBox::information(this,"提示","失败");
        }
        else
        {
            pModel_tablegoodinfo->revertAll();
        }
    }

}

void MainView::on_btnadd_goodadd_clicked()
{
   QString good_type = ui->cboc_goodadd_goodtype->currentText();
   QString good_id = ui->lineEdit_goodadd_id->text();
   QString good_name = ui->lineEdit_goodadd_name->text();
   QString good_barcode = ui->lineEdit_goodadd_barcode->text();
   QDate good_cutstarttime = ui->lineEdit_goodadd_cutstarttime->date();
   QDate good_cutstoptime = ui->lineEdit_goodadd_cutstoptime->date();
   double good_inprice = ui->lineEdit_goodadd_inprice->text().toDouble();
   double good_outprice = ui->lineEdit_goodadd_outprice->text().toDouble();
   double good_pricecut = ui->lineEdit_goodadd_pricecut->text().toDouble();
   int good_stock = ui->lineEdit_goodadd_stock->text().toInt();
   int good_onground = ui->lineEdit_goodadd_onground->text().toInt();
   int good_saled = ui->lineEdit_goodadd_saled->text().toInt();
   QString good_producer = ui->lineEdit_goodadd_producer->text();
   QString good_supllier = ui->cboc_goodadd_supllier->currentText();
   int good_warnline = ui->lineEdit_goodadd_warnline->text().toInt();
   QString pic = "";

   if(good_barcode==""||good_type==""||good_name==""||good_id==""||good_producer==""||good_supllier==""
           ||good_inprice==NULL||good_outprice==NULL||good_stock==NULL||good_onground==NULL||
           good_saled==NULL||good_warnline==NULL)
   {
       QMessageBox::information(this,"提示","输入无效,检查空值！！！");
       return;
   }


   QSqlQuery query = QSqlQuery(db);
   QSqlQuery query2 = QSqlQuery(db);
   QString sql  = QString("insert into goods values('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15','%16')").arg(good_id)
           .arg(good_barcode).arg(good_name).arg(good_type).arg(pic).arg(good_inprice)
           .arg(good_outprice).arg(good_pricecut).arg(good_cutstarttime.toString()).arg(good_cutstoptime.toString())
           .arg(good_onground).arg(good_saled).arg(good_warnline).arg(good_stock).arg(good_producer).arg(good_supllier);
   QString sql2  = QString("select good_barcode from goods where good_barcode = '%1'").arg(good_barcode);
   query2.exec(sql2);
   while(query2.next())
   {
        QMessageBox::information(this,"提示","重复添加");
        return;
   }
   bool b = query.exec(sql);
   if(b)
   {
        QMessageBox::information(this,"提示","添加成功");
        ui->lineEdit_goodadd_id->setText("");
        ui->lineEdit_goodadd_barcode->setText("");
        ui->lineEdit_goodadd_inprice->setText("");
        ui->lineEdit_goodadd_name->setText("");
        ui->lineEdit_goodadd_onground->setText("");
        ui->lineEdit_goodadd_outprice->setText("");
        ui->lineEdit_goodadd_pricecut->setText("");
        ui->lineEdit_goodadd_producer->setText("");
        ui->lineEdit_goodadd_saled->setText("");
        ui->lineEdit_goodadd_stock->setText("");
        ui->lineEdit_goodadd_warnline->setText("");
        pModel_tablegoodinfo->select();
   }

   else
   {
         QMessageBox::information(this,"提示","失败");
         qDebug()<<db.lastError();
   }









}
