 #include "frmnavlistviewform.h"
#include "ui_frmnavlistviewform.h"
#include "qabstractitemmodel.h"
#include "qdebug.h"

#include <QMessageBox>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQueryModel>   //创建Query模型
#include <QSqlQuery>
#include <QTime>

frmNavListViewForm::frmNavListViewForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmNavListViewForm)
{
    ui->setupUi(this);
    this->initForm();
}

frmNavListViewForm::~frmNavListViewForm()
{
    delete ui;
}

//功能框
void frmNavListViewForm::initForm()
{

    ui->listView->setIcoColorBg(false);
    ui->listView->setColorLine(QColor(32, 53, 74));
    ui->listView->setColorBg(QColor(52, 73, 94), QColor(24, 189, 155), QColor(24, 189, 155, 150));
    ui->listView->setColorText(QColor(254, 255, 255), QColor(252, 252, 252), QColor(0, 0, 0));

    //加载xml文件形式
    ui->listView->readData(":/image/config.xml");
}

//页面跳转
void frmNavListViewForm::on_listView_pressed()
{
    QModelIndex index = ui->listView->currentIndex();
    QString text = index.data().toString();

    if (text == "结账功能") {
        ManageVipDeal();
        addVipDeal();
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if (text == "添加新会员") {
        endPayDeal();
        ManageVipDeal();
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (text == "老会员管理") {
        addVipDeal();
        endPayDeal();
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if (text == "退/换货处理"){
        endPayDeal();
        //endPayDeal();
        ui->stackedWidget->setCurrentIndex(3);
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(4);
    }

}

// ///////////////////////////////////////////////////////////////////////////////////////////////////新会员注册界面
void frmNavListViewForm::on_pB_newvipRegister_clicked()
{
    QString newvipName = ui->lineEdit_newvipName->text();
    QString newvipPhone = ui->lineEdit_newvipPhone->text();
    QString newvipContirm = ui->lineEdit_newvipContirm->text();
    QString newvipFirst = ui->lineEdit_newvipFirst->text();

    //改手机号是否被注册
    QSqlQuery query;
    QString sql = QString("select member_phone from member");
    query.exec(sql);

    QString onePhone;
    while (query.next()) {
        onePhone = query.value(0).toString();
        if(onePhone == newvipPhone)
        {
            QMessageBox::information(NULL, "错误", "改手机号已被注册",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return;
        }
    }


    //注册
    if(newvipContirm == newvipPhone)
    {
        QSqlQuery query02;
        QString sql02 = QString("insert into member(member_name,member_phone,member_count,member_totalcost,member_operator) values('%1','%2','%3','%4','%5')")
                .arg(newvipName).arg(newvipPhone).arg(newvipFirst).arg("0").arg(work_name);
        query02.exec(sql02);

        QMessageBox::information(NULL, "成功", "新会员注册成功",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else {
        QMessageBox::information(NULL, "失败", "请重新确认手机号！！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}


// ///////////////////////////////////////////////////////////////////////////////////////////////////老会员管理界面
//老会员修改手机号
void frmNavListViewForm::on_pB_changeVipphone_clicked()
{
    QString oldvipName = ui->lineEdit_oldvipName->text();
    QString oldvipPhone = ui->lineEdit_oldvipPhone->text();
    QString oldvipChange = ui->lineEdit_oldvipNewPhone->text();
    QString oldvipConfirm = ui->lineEdit_oldvipCOnfirm->text();

    //数据库中是否含有该会员
    QSqlQuery query;
    QString sql = QString("select member_name,member_phone from member");
    query.exec(sql);

    QString oneName;
    QString onePhone;
    while (query.next()) {
        oneName = query.value(0).toString();
        onePhone = query.value(1).toString();
        if(onePhone == oldvipPhone && oneName == oldvipName)
        {
            if(oldvipChange == oldvipConfirm && oldvipChange != "")
            {
                //修改手机号
                //QSqlQuery query02;
                QString sql02 = QString("update member set member_phone = '%1' where member_name = '%2' and member_phone = '%3'")
                        .arg(oldvipChange).arg(oldvipName).arg(oldvipPhone);
                query.exec(sql02);

                QMessageBox::information(NULL, "成功", "手机号修改成功！！！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            }
            else {

                 QMessageBox::information(NULL, "失败", "请重新确认手机号！！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            }

            return;
        }
    }

     QMessageBox::information(NULL, "失败", "用户名或手机号不正确！！！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

}

//老会员充值
void frmNavListViewForm::on_pB_addVipcount_clicked()
{
    QString oldvipName = ui->lineEdit_oldvipName->text();
    QString oldvipPhone = ui->lineEdit_oldvipPhone->text();
    QString oldvipAdd = ui->lineEdit_oldvipAddcount->text();
    int add = oldvipAdd.toInt();

    QSqlQuery query;
    QString sql = QString("select member_name,member_phone,member_count from member");
    query.exec(sql);

    QString oneName;
    QString onePhone;
    int oneCount;
    while (query.next()) {

        oneName = query.value(0).toString();
        onePhone = query.value(1).toString();
        oneCount = query.value(2).toInt();
        oneCount += add;

        if(onePhone == oldvipPhone && oneName == oldvipName)
        {
            //修改手机号
            //QSqlQuery query02;
            QString sql02 = QString("update member set member_count = '%1' where member_name = '%2' and member_phone = '%3'")
                            .arg(oneCount).arg(oldvipName).arg(oldvipPhone);
            query.exec(sql02);


            QMessageBox::information(NULL, "成功", "会员卡充值 "+oldvipAdd+"元 成功！！！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

            return;
        }
    }

    QMessageBox::information(NULL, "失败", "用户名或手机号不正确！！！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

}


// ///////////////////////////////////////////////////////////////////////////////////////////////////结账管理界面
//结账功能
void frmNavListViewForm::on_pushButton_5_clicked()
{
    if(isReckon)
    {
        //获取购买商品数据
        QString text = ui->textEdit_goods->toPlainText();
        number_list = text.split("\n");

        QSqlQuery query;

        //计算总价
        for(int i=0; i<number_list.size(); i+=2)
        {
            //查询goods表是否含有该商品（有：仅获取单价；没有：报错）
            QString sql02 = QString("select goods_outprice from goods where goods_barcode = '%1'").arg(number_list.at(i));
            query.exec(sql02);

            if(query.next())
            {
                //计算
                thiscost += query.value(0).toDouble() * number_list.at(i+1).toInt();
            }
            else {
                //报错
                QMessageBox::information(NULL, "失败", "不存在条形码为 "+number_list.at(i)+" 的商品",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            }

        }

        //折扣后的价格
        thisdiscount = thiscost * 0.9;

        //显示计算后的数据
        ui->lineEdit_total->setText("此次共消费 "+QString::number(thiscost)+"元 ；若会员卡结账折扣后点的价格为 "+QString::number(thisdiscount)+" 元");

        isReckon = false;

    }
    else {
        QMessageBox::information(NULL, "失败", "请勿对此次消费重复计算！！！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    }
}


//结账时修改goods数据库
void frmNavListViewForm::dealGoodsAndDealingTable()
{
    QSqlQuery query02;
    QString sql02 = QString("select goods_barcode,goods_name,goods_ground,goods_salecount from goods");
    query02.exec(sql02);

    //记录数据库goods表所有该数据
    QList<QString> barcode;
    QList<int> ground;
    QList<int> salecount;
    QList<QString> goodsname;

    //记录dealing表需要修改的数据
    QList<int> dealingNeed;

    while(query02.next())
    {
        barcode.append(query02.value(0).toString());
        goodsname.append(query02.value(1).toString());
        ground.append(query02.value(2).toInt());
        salecount.append(query02.value(3).toInt());
    }

    int j = 0;
    QString sell;
    int goodsGround;
    int goodsSalecount;

    for(int i=0; i<number_list.size(); i+=2)
    {

        while (barcode.at(j)!=NULL) {
            if(barcode.at(j) == number_list.at(i))
                break;
            j++;
        }

        //修改goods表
        sell = number_list.at(i+1);
        goodsGround = ground.at(j) - sell.toInt();
        goodsSalecount = salecount.at(j) + sell.toInt();
        dealGoodsTable(goodsGround,goodsSalecount,barcode.at(j));

        //修改dealing表
        dealingNeed.append(j);

    }

    QString dealingbarcode;
    QString dealingname;
    QString dealingnum;
    int m=0;    //顺序记录卖出商品的个数
    for(int k=0;k<dealingNeed.size();k++)
    {
        dealingbarcode += barcode.at(dealingNeed.at(k)) + " ";
        dealingname += goodsname.at(dealingNeed.at(k)) + " ";
        dealingnum += number_list.at(m+1) + " ";
        m += 2;
    }

    dealDealingTable(dealingbarcode,dealingname,dealingnum);
}

void frmNavListViewForm::dealGoodsTable(int ground,int salecount,QString barcode)
{
    QSqlQuery query;
    QString sql03 = QString("update goods set goods_ground = '%1',goods_salecount = '%2' where goods_barcode = '%3'")
            .arg(ground)
            .arg(salecount)
            .arg(barcode);
    query.exec(sql03);

}

//结账时修改dealing数据库
void frmNavListViewForm::dealDealingTable(QString barcode,QString goodsname,QString goodsnum)
{
    //当前时间
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");

    QSqlQuery query;
    QString sql03;
    if(isVip && isEnough)
    {
        sql03 = QString("insert into dealing(dealing_date,dealing_workerid,dealing_goodsbarcode,dealing_goodsname,dealing_goodsnum,dealing_totalprice,dealing_cutmoney,dealing_memberid) values('%1','%2','%3','%4','%5','%6','%7','%8')")
                .arg(current_date)
                .arg(work_name)
                .arg(barcode)
                .arg(goodsname)
                .arg(goodsnum)
                .arg(thisdiscount)
                .arg(thiscost-thisdiscount)
                .arg(vipphone);
    }
    else {

        sql03 = QString("insert into dealing(dealing_date,dealing_workerid,dealing_goodsbarcode,dealing_goodsname,dealing_goodsnum,dealing_totalprice,dealing_cutmoney) values('%1','%2','%3','%4','%5','%6','%7')")
                .arg(current_date)
                .arg(work_name)
                .arg(barcode)
                .arg(goodsname)
                .arg(goodsnum)
                .arg(thiscost)
                .arg(0);
    }
    qDebug()<<current_date<<work_name<<barcode<<goodsname<<goodsnum<<thiscost;
    query.exec(sql03);

}

//结束后全局变量还原为初始状态
void frmNavListViewForm::endPayDeal()
{
    //数据初始化
    vipname = "";
    vipphone = "";
    vipCount = 0;
    vipcost = 0;
    thiscost = 0;
    thisdiscount = 0;
    number_list.clear();

    //界面初始化
    ui->lineEdit_vip->setText("");
    ui->lineEdit_vip_2->setText("");
    ui->lineEdit_total->setText("");
    ui->lineEdit_income->setText("");
    ui->lineEdit_remain->setText("");
    ui->lineEdit_outgoing->setText("");
    ui->lineEdit_account->setText("");
    ui->textEdit_goods->clear();

    isReckon = true;
}

//会员卡结账
void frmNavListViewForm::on_pB_cardpay_clicked()
{

    //判断是否为会员
    vipname = ui->lineEdit_vip->text();
    vipphone = ui->lineEdit_vip_2->text();
    //判断会员号是否正确
    QSqlQuery query02;
    QString sql = QString("select member_name,member_phone,member_count,member_totalcost from member");
    query02.exec(sql);

    QString oneName;
    QString onePhone;

    while (query02.next()) {

        oneName = query02.value(0).toString();
        onePhone = query02.value(1).toString();
        vipCount = query02.value(2).toDouble();
        vipcost = query02.value(3).toDouble();

        if(onePhone == vipphone && oneName == vipname)
        {
            isVip = true;
            QString s1 = QString::number(vipCount, 'f', 2);
            QString s2 = QString::number(vipCount-thisdiscount, 'f', 2);
            ui->lineEdit_account->setText(s1);
            ui->lineEdit_remain->setText(s2);
            //判断余额是否够用，修改isEnough参数
            if(thisdiscount <= vipCount)
                isEnough = true;
            break;
        }
    }


    if(isVip && isEnough)
    {
        double cardCount = vipCount - thisdiscount;
        double cardCost = vipcost + thisdiscount;
        qDebug()<<cardCost;
        //修改会员卡金额和消费

        QString sql02 = QString("update member set member_count = '%1', member_totalcost = '%2' where member_name = '%3' and member_phone = '%4'")
                        .arg(cardCount).arg(cardCost).arg(vipname).arg(vipphone);
        query02.exec(sql02);

        //修改goods数据库
        dealGoodsAndDealingTable();

        //修改dealing数据库（）

        QMessageBox::information(NULL, "成功", "消费 "+QString::number(thisdiscount)+"元 ！！！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        //
        endPayDeal();
    }
    else if (isVip == true && isEnough == false) {

        QMessageBox::information(NULL, "付款失败", "余额不足！！！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else {
        QMessageBox::information(NULL, "付款失败", "会员用户名或手机号错误！！！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }


}

//现金结账
void frmNavListViewForm::on_pB_cashpay_clicked()
{
    QString getMoney = ui->lineEdit_income->text();
    //QString outGoing = ui->lineEdit_outgoing->text();

    if(getMoney!=NULL)
    {
        QString outGoing = QString::number(getMoney.toDouble() - thiscost);
        ui->lineEdit_outgoing->setText(outGoing);

        dealGoodsAndDealingTable();

        QMessageBox::information(NULL, "成功", "消费 "+QString::number(thiscost)+"元 ！！！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        endPayDeal();
    }

}

//
void frmNavListViewForm::addVipDeal()
{
    ui->lineEdit_newvipName->setText("");
    ui->lineEdit_newvipPhone->setText("");
    ui->lineEdit_newvipFirst->setText("");
    ui->lineEdit_newvipContirm->setText("");

}

//
void frmNavListViewForm::ManageVipDeal()
{
    ui->lineEdit_oldvipName->setText("");
    ui->lineEdit_oldvipPhone->setText("");
    ui->lineEdit_oldvipCOnfirm->setText("");
    ui->lineEdit_oldvipNewPhone->setText("");
    ui->lineEdit_oldvipAddcount->setText("");
}


// ///////////////////////////////////////////////////////////////////////////////////////////////////主界面
void frmNavListViewForm::createClock()
{

}


// ///////////////////////////////////////////////////////////////////////////////////////////////////退货界面
void frmNavListViewForm::on_pB_return_clicked()
{
    //获取购买商品数据
    QString text = ui->textEdit_returnGoods->toPlainText();
    QStringList return_List = text.split("\n");

    //退货产品及数量
    QString returngoods = "";
    QString returnnum;
    QSqlQuery query;
    QString sql;
    QString sql02;
    double returnTotal = 0.0;

    for(int i=0;i<return_List.size();i+=2)
    {
        returngoods = returngoods + return_List.at(i) + " ";
        returnnum = returnnum + return_List.at(i+1) + " ";

        qDebug()<<return_List.at(i);
        sql  = QString("select goods_outprice, goods_salecount from goods where goods_barcode = '%1'").arg(return_List.at(i));
        query.exec(sql);

        //退款金额
        if(query.next())
            returnTotal += query.value(0).toDouble() * return_List.at(i+1).toInt();

        //减少库存
        sql02  = QString("update goods set goods_salecount = '%1' where goods_barcode = '%2'")
                .arg(query.value(1).toDouble() - return_List.at(i+1).toDouble())
                .arg(return_List.at(i));
        query.exec(sql02);

    }

    ui->lineEdit_returnTotal->setText(QString::number( returnTotal));
    //退货原因
    QString returnReason = ui->textEdit_returnReason->toPlainText();

    //退款时间
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");

    QString sql03 = QString("insert into returngood(returngood_goodbarcode,returngood_num,returngood_money,returngood_reason,returngood_date,returngood_staff) values('%1','%2','%3','%4','%5','%6')")
            .arg(returngoods)
            .arg(returnnum)
            .arg(returnTotal)
            .arg(returnReason)
            .arg(current_date)
            .arg(work_name);
    query.exec(sql03);



}


//查看个人业绩
void frmNavListViewForm::on_pushButton_clicked()
{
    //基本薪水
    QSqlQuery query;
    QString sql03 = QString("select user_salary from user where user_name = '%1' and user_password = '%2'")
            .arg(work_name)
            .arg(work_passage);
    query.exec(sql03);

    double userSalary;
    if(query.next())
        userSalary = query.value(0).toDouble();

    //本月销售额
    sql03 = QString("select dealing_totalprice from dealing where dealing_workerid = '%1'")
                .arg(work_name);
    query.exec(sql03);

    double volume = 0.0;
    while(query.next())
    {
        volume += query.value(0).toDouble();
    }

    //经手退换货金额
    double returnMoney = 0.0;
    sql03 = QString("select returngood_money from returngood where returngood_staff = '%1'")
                .arg(work_name);
    query.exec(sql03);
    while(query.next())
    {
       returnMoney += query.value(0).toDouble();
    }

    //办理会员卡数量
    int memberNum = 0;
    sql03 = QString("select * from member where member_operator = '%1'")
                .arg(work_name);
    query.exec(sql03);
    while(query.next())
    {
       memberNum += 1;
    }


    QString information = QString("姓名："+work_name+"\n" +"本月基础工资：" +QString::number(userSalary)+"\n" + "本月在岗期间营业额："+QString::number(volume) +"\n" + "经手退换货金额："+QString::number(returnMoney)+"\n" + "办理会员卡数量："+QString::number(memberNum));

    ui->textEdit_personInfo->setText(information);
}
