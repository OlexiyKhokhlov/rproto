#include "contentmodel.h"
#include <icontent.h>

ContentModel::ContentModel()
{

}

ContentModel::~ContentModel(){

}

//Interface QAbstractItemModel
int ContentModel::columnCount(const QModelIndex& parent) const{
    return 0;
}

int ContentModel::rowCount(const QModelIndex& parent) const{
    return 0;
}

QModelIndex ContentModel::index(int row, int column, const QModelIndex& parent) const{
    return QModelIndex();
}

QVariant ContentModel::data(const QModelIndex& index, int role) const{
    return QVariant();
}

QModelIndex ContentModel::parent(const QModelIndex& child) const{
    return QModelIndex();
}
