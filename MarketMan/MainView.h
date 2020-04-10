#ifndef WIDGET_H
#define WIDGET_H

#include "intable_model.h"

#include <QWidget>
#include <qsqldatabase.h>

namespace Ui {
class MainView;
}


class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = nullptr);

    ~MainView();

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

private:
    Ui::MainView *ui;
    QSqlDatabase db;
    intable_model *pModel_tablegoodtype;
    intable_model *pModel_tablegoodinfo;
    intable_model *pModel_tablestockinfo;
    intable_model *pModel_tablesuppliersinfo;


    void SetListItem();

    void InitGoodadd();
    void InitStockman_stockinput();
    void InitSupplieradd();

    void SetGoodsTypeTable();
    void SetGoodsInfoTable();
    void SetStockInfoTable();
    void SetSuppliersInfoTable();

    void SetModels();

};

#endif // WIDGET_H
