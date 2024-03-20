#include "articlepad.h"

ArticlePad::ArticlePad(QWidget *parent)
    : QWidget{parent}
{

}

WordListModel::WordListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}



int WordListModel::rowCount(const QModelIndex &parent) const
{
    return wordsList.size();
}

QVariant WordListModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() || index.row() >= wordsList.size() ) {
        return QVariant();
    }

    if ( role == Qt::DisplayRole || role == Qt::ToolTipRole ) {
        return wordsList.at(index.row());
    }
    else {
        return QVariant();
    }
}

void WordListModel::historyChanged()
{
    beginResetModel();
    endResetModel();
}
