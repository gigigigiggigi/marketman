#include "backview.h"
#include "widget.h"
#include "ui_backview.h"
#include "navlistview.h"
#include "intable_model.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqltablemodel>

backview::backview(QWidget *parent,QString username,QString userpwd) :
    QWidget(parent),
    ui(new Ui::backview)
{
    this->username = username;
    this->userpwd = userpwd;

    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    setFixedSize(this->width(),this->height());
    this->setWindowTitle("管理员界面");
    SqlLink();
    this->SetListItem();
    SetModels();

}

backview::~backview()
{
    delete ui;
}

void backview::SqlLink()
{

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("rm-bp1w73ygn47t2obnu0o.mysql.rds.aliyuncs.com");//数据库服务器的IP
    db.setUserName("root"); //数据库用户名
    db.setPassword("1996jackLWB!@#"); //密码
    db.setDatabaseName("marketman"); //使用哪个数据库
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


void backview::handlelineeditclicked()
{
    float p = ui->lineEdit_stock_goodnum->text().toInt()*ui->lineEdit_stock_singleprice->text().toFloat();
    QString data = QString("%1").arg(p);
    ui->lineEdit_stock_totalprice->setText(data);
}



void backview::SetListItem()
{
    ui->listView->readData(":/image/backstage.xml");

    //connect(this->ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(press()));
    //connect(this->ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(press(QModelIndex)));
}


void backview::InitGoodadd()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(QString("select goodtype_type from goodtype"),db);
    ui->cboc_goodadd_goodtype->setModel(model);

    QSqlQueryModel *model2 = new QSqlQueryModel(this);
    model2->setQuery(QString("select suppliers_name from suppliers"),db);
    ui->cboc_goodadd_supplier->setModel(model2);

    QRegExp regx("^([0]|[1-9][0-9]{0,99})(?:\\.\\d{1,4})?$|(^\\t?$)");
    QValidator *validator = new QRegExpValidator(regx);
    ui->lineEdit_goodadd_id->setValidator(validator);
    ui->lineEdit_goodadd_barcode->setValidator(validator);
    ui->lineEdit_goodadd_onground->setValidator(validator);
    ui->lineEdit_goodadd_saled->setValidator(validator);
    ui->lineEdit_goodadd_stock->setValidator(validator);
    ui->lineEdit_goodadd_warnline->setValidator(validator);

    ui->lineEdit_goodadd_inprice->setValidator(validator);
    ui->lineEdit_goodadd_outprice->setValidator(validator);
    ui->lineEdit_goodadd_pricecut->setValidator(validator);
    ui->lineEdit_goodadd_cutstarttime->setDate(QDate::currentDate());
    ui->lineEdit_goodadd_cutstoptime->setDate(QDate::currentDate());

    ui->lineEdit_goodinfo_goodup->setValidator(validator);

}

void backview::InitStockman_stockinput()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(QString("select good_id from goods"),db);
    ui->cbox_stock_goodid->setModel(model);
    QString str = ui->cbox_stock_goodid->currentText();
    QSqlQuery query(db);
    QString sql = QString("select goods_name,goods_inprice from goods where good_id = '%1'").arg(str);
    query.exec(sql);
    while(query.next())
    {
        ui->lineEdit_stock_goodname->setText(query.value(0).toString());
        ui->lineEdit_stock_singleprice->setText(query.value(1).toString());
    }
     ui->lineEdit_stock_goodname->setEnabled(false);
     ui->lineEdit_stock_singleprice->setEnabled(false);

    QSqlQueryModel *model2 = new QSqlQueryModel(this);
    model2->setQuery(QString("select suppliers_name from suppliers"),db);
    ui->cbox_stock_supplier->setModel(model2);
    str = ui->cbox_stock_supplier->currentText();
    sql = QString("select suppliers_phone from suppliers where suppliers_name = '%1'").arg(str);
    query.exec(sql);
    while(query.next())
    {
        ui->lineEdit_stock_supplierphone->setText(query.value(0).toString());
    }
     ui->lineEdit_stock_supplierphone->setEnabled(false);

    QSqlQueryModel *model3 = new QSqlQueryModel(this);
    model3->setQuery(QString("select user_name from user"),db);
    ui->cbox_stock_person->setModel(model3);

    QRegExp regx("^([0]|[1-9][0-9]{0,99})(?:\\.\\d{1,4})?$|(^\\t?$)");
    QValidator *validator = new QRegExpValidator(regx);

    ui->lineEdit_stock_goodnum->setValidator(validator);
    ui->lineEdit_stock_totalprice->setValidator(validator);
    ui->dateEdit_stock_time->setDate(QDate::currentDate());
    connect(ui->lineEdit_stock_totalprice, SIGNAL(clicked()), this, SLOT(handlelineeditclicked()));

}

void backview::InitSupplieradd()
{
    QRegExp regx("^([0]|[1-9][0-9]{0,99})(?:\\.\\d{1,4})?$|(^\\t?$)");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEdit_goodadd_id);
    ui->lineEdit_stock_supplier_phone->setValidator(validator);
}

void backview::InitWorkermanworkeradd()
{
    QRegExp regx("^([0]|[1-9][0-9]{0,99})(?:\\.\\d{1,4})?$|(^\\t?$)");
    QValidator *validator = new QRegExpValidator(regx);
    QRegExp regx2("[a-zA-Z0-9\-\\\_]{25}");
    QValidator *validator2 = new QRegExpValidator(regx);
    ui->lineEdit_workerman_pwd->setValidator(validator2);
    ui->lineEdit_workerman_id->setValidator(validator);
    ui->lineEdit_workerman_salary->setValidator(validator);
    ui->lineEdit_workerman_phone->setValidator(validator);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(QString("select workertype_type_name from workertype"),db);
    ui->cbox_workerman_workertype->setModel(model);
}


void backview::SetGoodsTypeTable()
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

void backview::SetGoodsInfoTable()
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

void backview::SetStockInfoTable()
{
    pModel_tablestockinfo = new intable_model(this,db);
    pModel_tablestockinfo->setTable("stock");
    pModel_tablestockinfo->setEditStrategy(QSqlTableModel::OnManualSubmit);
    pModel_tablestockinfo->select(); //选取整个表的所有行

    pModel_tablestockinfo->setHeaderData(1, Qt::Horizontal, tr("商品编号"));
    pModel_tablestockinfo->setHeaderData(2, Qt::Horizontal, tr("商品名称"));
    pModel_tablestockinfo->setHeaderData(3, Qt::Horizontal, tr("商品数量"));
    pModel_tablestockinfo->setHeaderData(4, Qt::Horizontal, tr("商品进价"));
    pModel_tablestockinfo->setHeaderData(5, Qt::Horizontal, tr("商品总价"));
    pModel_tablestockinfo->setHeaderData(6, Qt::Horizontal, tr("供货商"));
    pModel_tablestockinfo->setHeaderData(7, Qt::Horizontal, tr("供货商电话"));
    pModel_tablestockinfo->setHeaderData(8, Qt::Horizontal, tr("入库时间"));
    pModel_tablestockinfo->setHeaderData(9, Qt::Horizontal, tr("入库工作人员"));

    ui->tablestockinfo->setModel(pModel_tablestockinfo);
    ui->tablestockinfo->setColumnHidden(0,true);
    ui->tablestockinfo->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tablestockinfo->show();


}

void backview::SetSuppliersInfoTable()
{
    pModel_tablesuppliersinfo = new intable_model(this,db);
    pModel_tablesuppliersinfo->setTable("suppliers");
    pModel_tablesuppliersinfo->setEditStrategy(QSqlTableModel::OnManualSubmit);
    pModel_tablesuppliersinfo->select(); //选取整个表的所有行

    pModel_tablesuppliersinfo->setHeaderData(1, Qt::Horizontal, tr("供货商名"));
    pModel_tablesuppliersinfo->setHeaderData(2, Qt::Horizontal, tr("供货商电话"));
    pModel_tablesuppliersinfo->setHeaderData(3, Qt::Horizontal, tr("供货商地址"));

    ui->tablesuppliersinfo->setModel(pModel_tablesuppliersinfo);
    ui->tablesuppliersinfo->setColumnHidden(0,true);
    ui->tablesuppliersinfo->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tablesuppliersinfo->show();




}

void backview::SetWorkerInfoTable()
{
    pModel_tableworkerinfo = new intable_model(this,db);
    pModel_tableworkerinfo->setTable("user");
    pModel_tableworkerinfo->setEditStrategy(QSqlTableModel::OnManualSubmit);
    pModel_tableworkerinfo->select(); //选取整个表的所有行
    pModel_tableworkerinfo->setHeaderData(0, Qt::Horizontal, tr("员工编号"));
    pModel_tableworkerinfo->setHeaderData(1, Qt::Horizontal, tr("员工姓名"));
    pModel_tableworkerinfo->setHeaderData(2, Qt::Horizontal, tr("员工手机号"));
    pModel_tableworkerinfo->setHeaderData(4, Qt::Horizontal, tr("员工性别"));
    pModel_tableworkerinfo->setHeaderData(6, Qt::Horizontal, tr("员工工资"));
    pModel_tableworkerinfo->setHeaderData(7, Qt::Horizontal, tr("员工权限"));
    pModel_tableworkerinfo->setHeaderData(8, Qt::Horizontal, tr("员工类型"));

    ui->tableworkerinfo->setModel(pModel_tableworkerinfo);
    ui->tableworkerinfo->setColumnHidden(3,true);
    ui->tableworkerinfo->setColumnHidden(5,true);
    ui->tableworkerinfo->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tableworkerinfo->show();
}

void backview::SetWorkerTypeInfoTable()
{
    pModel_tableworkerinfo_worktyinfo = new intable_model(this,db);
    pModel_tableworkerinfo_worktyinfo->setTable("workertype");
    pModel_tableworkerinfo_worktyinfo->setEditStrategy(QSqlTableModel::OnManualSubmit);
    pModel_tableworkerinfo_worktyinfo->select();
    pModel_tableworkerinfo_worktyinfo->setHeaderData(1, Qt::Horizontal, tr("员工权限"));
    pModel_tableworkerinfo_worktyinfo->setHeaderData(2, Qt::Horizontal, tr("员工类型"));


    ui->tableworkertype->setModel(pModel_tableworkerinfo_worktyinfo);
    ui->tableworkertype->setColumnHidden(0,true);
    ui->tableworkertype->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tableworkertype->show();
}

void backview::SetModels()
{
    SetGoodsTypeTable();
    SetGoodsInfoTable();
    SetStockInfoTable();
    SetSuppliersInfoTable();
    SetWorkerInfoTable();
    SetWorkerTypeInfoTable();
    SetBack();

}

void backview::SetBack()
{
    QPalette pl = ui->textEdit_2->palette();

    pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));

     ui->textEdit_2->setPalette(pl);
     ui->textEdit_2->setStyleSheet("border: none;");

     ui->lineEdit_usernow->setText(username);
     ui->lineEdit_usernow->setStyleSheet("QLineEdit{background-color:transparent}"
                                         "QLineEdit{border-width:0;border-style:outset}");


     ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     ui->textEdit->setStyleSheet("border: none;");
     ui->textEdit_3->setStyleSheet("border: none;");
     ui->textEdit_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     ui->textEdit_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}




void backview::on_listView_pressed(const QModelIndex &index)
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
    {
         this->ui->stackedWidget->setCurrentIndex(2);

    }
    else if(str == "进货入库")
    {
        this->ui->stackedWidget->setCurrentIndex(4);
        InitStockman_stockinput();
    }
    else if(str == "入库查询")
    {
        this->ui->stackedWidget->setCurrentIndex(5);
        this->ui->btnupdate_stock->setVisible(false);
    }
    else if(str == "管理供货")
    {
        this->ui->stackedWidget->setCurrentIndex(6);
        InitSupplieradd();
    }
    else if(str == "员工录入")
    {
        this->ui->stackedWidget->setCurrentIndex(7);
        InitWorkermanworkeradd();
    }
    else if(str == "员工查询")
    {
        this->ui->stackedWidget->setCurrentIndex(8);
    }
    else if(str == "员工类型管理")
    {
        this->ui->stackedWidget->setCurrentIndex(9);
    }
    else if(str == "进入前台")
    {
        int ok = QMessageBox::warning(this,tr("进入前台"),tr("你确定进入前台界面吗？"), QMessageBox::Yes,QMessageBox::No);

        if(ok == QMessageBox::Yes)
        {
            this->hide();
            f = new frmNavListViewForm;
            f->work_name = username;
            f->work_passage = userpwd;
            f->show();
        }
        else
        {
            return;
        }

    }




}

void backview::on_btnadd_goodtype_clicked()
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

void backview::on_btndelete_goodtype_clicked()
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


void backview::on_btnupdate_goodtype_clicked()
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
            pModel_tablegoodinfo->select();

        }
        else
            QMessageBox::information(this,"提示","失败");
    }

}

void backview::on_btnupdate_goodinfo_clicked()
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

void backview::on_btndelete_goodinfo_clicked()
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

void backview::on_btnadd_goodadd_clicked()
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
   QString good_supllier = ui->cboc_goodadd_supplier->currentText();
   int good_warnline = ui->lineEdit_goodadd_warnline->text().toInt();
   QString pic = "";

   if(good_barcode==""||good_type==""||good_name==""||good_id==""||good_producer==""||good_supllier==""
           ||good_inprice==NULL||good_outprice==NULL||
           good_warnline==NULL)
   {
       QMessageBox::information(this,"提示","输入无效,检查空值！！！");
       return;
   }


   QSqlQuery query = QSqlQuery(db);
   QSqlQuery query2 = QSqlQuery(db);
   QString sql  = QString("insert into goods values('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15','%16')").arg(good_id)
           .arg(good_barcode).arg(good_name).arg(good_type).arg(pic).arg(good_inprice)
           .arg(good_outprice).arg(good_pricecut).arg(good_cutstarttime.toString("yy-MM-dd")).arg(good_cutstoptime.toString("yy-MM-dd"))
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

void backview::on_cbox_stock_goodid_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query(db);
    QString sql = QString("select goods_name,goods_inprice from goods where good_id = '%1'").arg(arg1);
    query.exec(sql);
    while(query.next())
    {
        ui->lineEdit_stock_goodname->setText(query.value(0).toString());
         ui->lineEdit_stock_singleprice->setText(query.value(1).toString());
    }
}

void backview::on_btnadd_stock_clicked()
{
      QString good_id = ui->cbox_stock_goodid->currentText();
      QString good_name = ui->lineEdit_stock_goodname->text();
      QString good_num = ui->lineEdit_stock_goodnum->text();
      QString good_singleprice = ui->lineEdit_stock_singleprice->text();
      QString supplierphone = ui->lineEdit_stock_supplierphone->text();
      QString totalprice = ui->lineEdit_stock_totalprice->text();
      QString suppliername = ui->cbox_stock_supplier->currentText();
      QString purchasername = ui->cbox_stock_person->currentText();
      QDate data = ui->dateEdit_stock_time->date();

      if(good_num == NULL||good_singleprice==NULL||totalprice==NULL)
      {
          QMessageBox::information(this,"提示","输入无效,检查空值！！！");
          return;
      }

      QSqlQuery query = QSqlQuery(db);
      QSqlQuery query2 = QSqlQuery(db);

      QString sql1 = QString("update goods set goods_stocknum = goods_stocknum+'%1' where good_id = '%2' ").arg(good_num.toInt()).arg(good_id.toInt());
      query.exec(sql1);
      QString sql2 = QString("insert into stock(stock_goodid,stock_goodname,stock_goodnum,stock_goodsingleprice,stock_totalprice,stock_suppliername,stock_supplierphone,stock_stocktime,stock_purchaser) values('%1','%2','%3','%4','%5','%6','%7','%8','%9')")
                     .arg(good_id).arg(good_name).arg(good_num).arg(good_singleprice).arg(totalprice).arg(suppliername).arg(supplierphone).arg(data.toString("yy-MM-dd")).arg(purchasername);

      QString sd = data.toString();
     bool b =  query2.exec(sql2);
     if(b)
     {
          QMessageBox::information(this,"提示","添加成功");
          ui->lineEdit_stock_goodnum->setText("");
          ui->lineEdit_stock_totalprice->setText("");
          pModel_tablestockinfo->select();
          pModel_tablegoodinfo->select();
     }
     else
     {
         QMessageBox::information(this,"提示","失败");
         qDebug()<<db.lastError();
     }

}

void backview::on_btndelete_stock_clicked()
{
    QItemSelectionModel *sModel = ui->tablestockinfo->selectionModel();

    //取出模型中的索引
    QModelIndexList list = sModel->selectedRows();
    //删除所有选中的行
    bool b;
     qDebug()<<"com in";
    if(list.size()>0)
    {
        for(int i=0; i < list.size(); i++){
            pModel_tablestockinfo->removeRow( list.at(i).row() );
        }

        int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"), QMessageBox::Yes,QMessageBox::No);

        if(ok == QMessageBox::Yes)
        {
            qDebug()<<"com in";
            pModel_tablestockinfo->submitAll();
            b =  pModel_tablestockinfo->database().commit();
            if(b)
            {
                QMessageBox::information(this,"提示","删除成功");

            }
            else
                QMessageBox::information(this,"提示","失败");
        }
        else
        {
            pModel_tablestockinfo->revertAll();
        }
    }
}

void backview::on_btnupdate_stock_clicked()
{
    int ok = QMessageBox::warning(this,tr("提交修改!"),tr("你确定提交修改吗？"), QMessageBox::Yes,QMessageBox::No);

    if(ok == QMessageBox::Yes)
    {
        qDebug()<<"com in";
        pModel_tablestockinfo->submitAll();
        bool b;
        b =  pModel_tablestockinfo->database().commit();
        if(b)
        {
            QMessageBox::information(this,"提示","修改成功");
        }
        else
            QMessageBox::information(this,"提示","失败");
    }
}

void backview::on_btndelete_stock_supplier_clicked()
{
    QItemSelectionModel *sModel = ui->tablesuppliersinfo->selectionModel();

    //取出模型中的索引
    QModelIndexList list = sModel->selectedRows();
    //删除所有选中的行
    bool b;
     qDebug()<<"com in";
    if(list.size()>0)
    {
        for(int i=0; i < list.size(); i++){
            pModel_tablesuppliersinfo->removeRow( list.at(i).row() );
        }

        int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"), QMessageBox::Yes,QMessageBox::No);

        if(ok == QMessageBox::Yes)
        {
            qDebug()<<"com in";
            pModel_tablesuppliersinfo->submitAll();
            b =  pModel_tablesuppliersinfo->database().commit();
            if(b)
            {
                QMessageBox::information(this,"提示","删除成功");

            }
            else
                QMessageBox::information(this,"提示","失败");
        }
        else
        {
            pModel_tablesuppliersinfo->revertAll();
        }
    }
}

void backview::on_btnupdate_stock_supplier_clicked()
{
    int ok = QMessageBox::warning(this,tr("提交修改!"),tr("你确定提交修改吗？"), QMessageBox::Yes,QMessageBox::No);

    if(ok == QMessageBox::Yes)
    {
        qDebug()<<"com in";
        pModel_tablesuppliersinfo->submitAll();
        bool b;
        b =  pModel_tablesuppliersinfo->database().commit();
        if(b)
        {
            QMessageBox::information(this,"提示","修改成功");

        }
        else
            QMessageBox::information(this,"提示","失败");
    }
}

void backview::on_btnadd_stock_supplier_clicked()
{
    QString suppliername = ui->lineEdit_stock_supplier_name->text();
    QString supplierphone = ui->lineEdit_stock_supplier_phone->text();
    QString supplieraddress = ui->lineEdit_stock_supplier_address->text();
    if(supplieraddress==NULL||suppliername==NULL||supplierphone==NULL)
    {
        QMessageBox::information(this,"提示","输入无效,检查空值！！！");
        return;
    }
    QSqlQuery query(db);
    QString sql = QString("select suppliers_name from suppliers where suppliers_name = '%1'").arg(suppliername);
    query.exec(sql);
    while(query.next())
    {
        QMessageBox::information(this,"提示","重复添加");
        return;
    }

    QString sql2 = QString("insert into suppliers(suppliers_name,suppliers_phone,suppliers_address) values('%1','%2','%3')")
                    .arg(suppliername).arg(supplierphone).arg(supplieraddress);
    bool b = query.exec(sql2);
    if(b)
    {
         QMessageBox::information(this,"提示","添加成功");
         ui->lineEdit_stock_supplier_address->setText("");
         ui->lineEdit_stock_supplier_name->setText("");
         ui->lineEdit_stock_supplier_phone->setText("");
         pModel_tablesuppliersinfo->select();
    }
    else
    {
        QMessageBox::information(this,"提示","失败");
        qDebug()<<db.lastError();
    }


}

void backview::on_btnadd_workerman_clicked()
{
    QString workerid = ui->lineEdit_workerman_id->text();
    QString workername = ui->lineEdit_workerman_name->text();
    QString workerpwd = ui->lineEdit_workerman_pwd->text();
    double workersalary = ui->lineEdit_workerman_salary->text().toFloat();
    QString workersex = ui->cbox_workerman_sex->currentText();
    QString workertype_name = ui->cbox_workerman_workertype->currentText();
    QString workerphone = ui->lineEdit_workerman_phone->text();
    QString sql_workertype = QString("select workertype_type from workertype where workertype_type_name = '%1'").arg(workertype_name);
    QSqlQuery q(db);
    QString workertype;
    q.exec(sql_workertype);
    while(q.next())
    {
        workertype = q.value(0).toString();
    }
    if(workerid==NULL||workername==NULL||workerpwd==NULL||workersalary==NULL||workersex==NULL||workertype==NULL||workerphone == NULL)
    {
        QMessageBox::information(this,"提示","输入无效,检查空值！！！");
        return;
    }

    QString sql = QString("insert into user(user_id,user_name,user_phone,user_password,user_sex,user_salary,user_type,user_type_name) values('%1','%2','%3','%4','%5','%6','%7','%8')").arg(workerid).arg(workername).arg(workerphone).arg(workerpwd)
                    .arg(workersex).arg(workersalary).arg(workertype).arg(workertype_name);
    QSqlQuery query(db);
    QString sql2 = QString("select user_id from user where user_id = '%1'").arg(workerid);
    QSqlQuery query2(db);
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
         ui->lineEdit_workerman_id->setText("");
         ui->lineEdit_workerman_name->setText("");
         ui->lineEdit_workerman_pwd->setText("");
         ui->lineEdit_workerman_salary->setText("");
         ui->lineEdit_workerman_phone->setText("");
         pModel_tableworkerinfo->select();
    }
    else
    {
        QMessageBox::information(this,"提示","失败");
        qDebug()<<db.lastError();
    }
}

void backview::on_btndelete_workerman_clicked()
{
    QItemSelectionModel *sModel = ui->tableworkerinfo->selectionModel();

    //取出模型中的索引
    QModelIndexList list = sModel->selectedRows();
    //删除所有选中的行
    bool b;
    qDebug()<<"com in";
    if(list.size()>0)
    {
        for(int i=0; i < list.size(); i++){
            pModel_tableworkerinfo->removeRow( list.at(i).row() );
        }

        int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"), QMessageBox::Yes,QMessageBox::No);

        if(ok == QMessageBox::Yes)
        {
            qDebug()<<"com in";
            pModel_tableworkerinfo->submitAll();
            b =  pModel_tableworkerinfo->database().commit();
            if(b)
            {
                QMessageBox::information(this,"提示","删除成功");

            }
            else
                QMessageBox::information(this,"提示","失败");
        }
        else
        {
            pModel_tableworkerinfo->revertAll();
        }
    }
}

void backview::on_btnupdate_workerman_clicked()
{
    int ok = QMessageBox::warning(this,tr("提交修改!"),tr("你确定提交修改吗？"), QMessageBox::Yes,QMessageBox::No);

    if(ok == QMessageBox::Yes)
    {
        qDebug()<<"com in";
        pModel_tableworkerinfo->submitAll();
        bool b;
        b =  pModel_tableworkerinfo->database().commit();
        if(b)
        {
            QMessageBox::information(this,"提示","修改成功");

        }
        else
            QMessageBox::information(this,"提示","失败");
    }
}

void backview::on_btnadd_workerman_workertype_clicked()
{
    QString str = ui->lineEdit_workerman_workertype_type->text();
    QString str2 = ui->cbox_workertype_power->currentText();
    if(str=="")
    {
        QMessageBox::information(this,"提示","输入无效");
        return;
    }
    QSqlQuery query = QSqlQuery(db);
    QSqlQuery query2 = QSqlQuery(db);
    QString sql  = QString("insert into workertype(workertype_type,workertype_type_name) values('%1','%2')").arg(str2).arg(str);
    QString sql2  = QString("select workertype_type_name from workertype where workertype_type_name = '%1'").arg(str);
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
        pModel_tableworkerinfo_worktyinfo->select();
        ui->lineEdit_workerman_workertype_type->setText("");
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(QString("select workertype_type_name from workertype"),db);
        ui->cbox_workerman_workertype->setModel(model);
    }

    else
        QMessageBox::information(this,"提示","失败");
}

void backview::on_btnupdate_workerman_workertype_clicked()
{
    int ok = QMessageBox::warning(this,tr("提交修改!"),tr("你确定提交修改吗？"), QMessageBox::Yes,QMessageBox::No);

    if(ok == QMessageBox::Yes)
    {
        qDebug()<<"com in";
        pModel_tableworkerinfo_worktyinfo->submitAll();
        bool b;
        b =  pModel_tableworkerinfo_worktyinfo->database().commit();
        if(b)
        {
            QMessageBox::information(this,"提示","修改成功");

        }
        else
            QMessageBox::information(this,"提示","失败");
    }
}

void backview::on_btndelete_workerman_workertype_clicked()
{
    QItemSelectionModel *sModel = ui->tableworkertype->selectionModel();

    //取出模型中的索引
    QModelIndexList list = sModel->selectedRows();
    //删除所有选中的行
    bool b;
    qDebug()<<"com in";
    if(list.size()>0)
    {
        for(int i=0; i < list.size(); i++){
            pModel_tableworkerinfo_worktyinfo->removeRow( list.at(i).row() );
        }

        int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"), QMessageBox::Yes,QMessageBox::No);

        if(ok == QMessageBox::Yes)
        {
            qDebug()<<"com in";
            pModel_tableworkerinfo_worktyinfo->submitAll();
            b =  pModel_tableworkerinfo_worktyinfo->database().commit();
            if(b)
            {
                QMessageBox::information(this,"提示","删除成功");

            }
            else
                QMessageBox::information(this,"提示","失败");
        }
        else
        {
            pModel_tableworkerinfo_worktyinfo->revertAll();
        }
    }
}

void backview::on_btngoodinfo_goodup_clicked()
{
      int num = ui->lineEdit_goodinfo_goodup->text().toInt();
      if(num == NULL||num == 0)
          return;

      int curRow = ui->tableGoodsinfo->currentIndex().row();

      if(curRow==-1)
      {
          QMessageBox::information(this,"提示","未选中项");
          return;
      }
      int currentstock =pModel_tablegoodinfo->data(pModel_tablegoodinfo->index(curRow,13)).toInt();
      int currentgoodid = pModel_tablegoodinfo->data(pModel_tablegoodinfo->index(curRow,0)).toInt();
      qDebug()<<currentstock;
      if(num>currentstock)
      {
           QMessageBox::information(this,"提示","库存不足");
           return;
      }

      QString sql =  QString("update goods set goods_stocknum = goods_stocknum-'%1',goods_ground = goods_ground+'%2' where good_id = '%3'")
                      .arg(num).arg(num).arg(currentgoodid);
      QSqlQuery query(db);
      bool b = query.exec(sql);
      if(b)
      {
          QMessageBox::information(this,"提示","添加成功");
          ui->lineEdit_goodinfo_goodup->setText("");
          pModel_tablegoodinfo->select();
      }
      else
      {
          QMessageBox::information(this,"提示","失败");
          qDebug()<<db.lastError();
      }


}
