#ifndef BACKVIEW_H
#define BACKVIEW_H

#include <QWidget>
#include "intable_model.h"
#include "frmnavlistviewform.h"

namespace Ui {
class backview;
}

class backview : public QWidget
{
    Q_OBJECT

public:
    explicit backview(QWidget *parent = 0,QString username="",QString userpwd="");
    QString username;
    QString userpwd;
    ~backview();

private slots:
        void SqlLink();
        void handlelineeditclicked();
        void on_listView_pressed(const QModelIndex &index);


        void on_btnadd_goodtype_clicked();

        void on_btndelete_goodtype_clicked();

        void on_btnupdate_goodtype_clicked();

        void on_btnupdate_goodinfo_clicked();

        void on_btndelete_goodinfo_clicked();

        void on_btnadd_goodadd_clicked();

        void on_cbox_stock_goodid_currentIndexChanged(const QString &arg1);

        void on_btnadd_stock_clicked();

        void on_btndelete_stock_clicked();

        void on_btnupdate_stock_clicked();

        void on_btndelete_stock_supplier_clicked();

        void on_btnupdate_stock_supplier_clicked();

        void on_btnadd_stock_supplier_clicked();

        void on_btnadd_workerman_clicked();

        void on_btndelete_workerman_clicked();

        void on_btnupdate_workerman_clicked();

        void on_btnadd_workerman_workertype_clicked();

        void on_btnupdate_workerman_workertype_clicked();

        void on_btndelete_workerman_workertype_clicked();

        void on_btngoodinfo_goodup_clicked();

private:
    Ui::backview *ui;
    QSqlDatabase db;

    frmNavListViewForm *f;

    intable_model *pModel_tablegoodtype;
    intable_model *pModel_tablegoodinfo;
    intable_model *pModel_tablestockinfo;
    intable_model *pModel_tablesuppliersinfo;
    intable_model *pModel_tableworkerinfo;
    intable_model *pModel_tableworkerinfo_worktyinfo;


    void SetListItem();

    void InitGoodadd();
    void InitStockman_stockinput();
    void InitSupplieradd();
    void InitWorkermanworkeradd();

    void SetGoodsTypeTable();
    void SetGoodsInfoTable();
    void SetStockInfoTable();
    void SetSuppliersInfoTable();
    void SetWorkerInfoTable();
    void SetWorkerTypeInfoTable();



    void SetModels();
    void SetBack();

};

#endif // BACKVIEW_H
