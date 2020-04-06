#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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

        void on_listView_pressed(const QModelIndex &index);

private:
    Ui::MainView *ui;
    void SqlLink();
    void SetListItem();

};

#endif // WIDGET_H
