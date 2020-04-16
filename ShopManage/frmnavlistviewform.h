#ifndef FRMNAVLISTVIEWFORM_H
#define FRMNAVLISTVIEWFORM_H

#include <QWidget>

namespace Ui {
class frmNavListViewForm;
}

class frmNavListViewForm : public QWidget
{
    Q_OBJECT

public:
    explicit frmNavListViewForm(QWidget *parent = 0);
    ~frmNavListViewForm();

    QString work_name;
    QString work_passage;



private slots:
    void initForm();
    //void on_listView_pressed();
    void on_listView_pressed();

    void on_pB_newvipRegister_clicked();

    void on_pB_changeVipphone_clicked();

    void on_pB_addVipcount_clicked();

    void on_pushButton_5_clicked();

    void on_pB_cardpay_clicked();

    void on_pB_cashpay_clicked();


    void on_pB_return_clicked();

    void on_pushButton_clicked();

private:
    Ui::frmNavListViewForm *ui;

    //结账功能使用
    QString vipname = "";
    QString vipphone = "";
    double vipCount = 0;   //消费前卡上余额
    double vipcost = 0;    //消费后卡上余额
    double thiscost = 0;
    double thisdiscount = 0;
    QStringList number_list;

    bool isReckon = true;
    bool isVip = false;
    bool isEnough = false;

    void dealGoodsAndDealingTable();

    void dealGoodsTable(int ground,int salecount,QString barcode);

    void dealDealingTable(QString barcode,QString goodsname,QString goodsnum);

    void endPayDeal();

    void addVipDeal();

    void ManageVipDeal();

    void createClock();


};

#endif // FRMNAVLISTVIEWFORM_H

