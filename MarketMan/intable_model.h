#ifndef INCOME_MODEL_H
#define INCOME_MODEL_H


#include <QSqlTableModel>

class intable_model : public QSqlTableModel
{
public:
    intable_model(QObject * parent = 0, QSqlDatabase db = QSqlDatabase());
    ~intable_model();
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;
};


#endif // INCOME_MODEL_H
