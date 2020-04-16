#include "widget.h"
#include <QApplication>
#include "frmnavlistviewform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Widget w;
    w.show();

    //frmNavListViewForm f;
    //f.show();

    return a.exec();
}
