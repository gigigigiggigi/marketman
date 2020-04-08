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
        void on_listView_pressed(const QModelIndex &index);


        void on_btnadd_goodtype_clicked();

        void on_btndelete_goodtype_clicked();

        void on_btnupdate_goodtype_clicked();

        void on_btnupdate_goodinfo_clicked();

        void on_btndelete_goodinfo_clicked();



        void on_btnadd_goodadd_clicked();

private:
    Ui::MainView *ui;
    QSqlDatabase db;
    intable_model *pModel_tablegoodtype;
    intable_model *pModel_tablegoodinfo;

    void SetModels();
    void SetListItem();

    void InitGoodadd();

    void SetGoodsTypeTable();
    void SetGoodsInfoTable();

};

#endif // WIDGET_H
