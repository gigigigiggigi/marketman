#include "intable_model.h"
#include <QColor>
#include <QFont>

intable_model::intable_model(QObject * parent, QSqlDatabase db) : QSqlTableModel(parent,db)
{

}

intable_model::~intable_model()
{

}

QVariant intable_model::data(const QModelIndex &idx, int role) const
{
    QVariant value  = QSqlTableModel::data(idx,role);
    if(Qt::TextAlignmentRole == role)
    {
        value   = int(Qt::AlignCenter | Qt::AlignHCenter);
        return value;
    }
    if(Qt::ForegroundRole == role)
    {
        if(3 == idx.column())
            return QVariant(QColor(255,144,144));
    }
    if(Qt::FontRole == role)
    {
        if(3 == idx.column())
        {
            QFont font;
            font.setBold(true);
            return QVariant(font);
        }
    }
    return value;
}
