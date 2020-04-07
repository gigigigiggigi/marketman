#ifndef WIDGET_H
#define WIDGET_H

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


        void on_pushButton_clicked();

private:
    Ui::MainView *ui;
    QSqlDatabase db;

    void SetListItem();
    void SetGoodsTypeTable();

};

#endif // WIDGET_H
