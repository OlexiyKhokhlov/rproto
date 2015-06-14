#include "contentmodel.h"
#include <icontent.h>

ContentModel::ContentModel(QObject* parent)
    :QAbstractItemModel(parent)
    ,content(nullptr)
{}

ContentModel::~ContentModel(){
}

void ContentModel::setContent(RProto::IContent *c){
    beginResetModel();
    content = c;
    endResetModel();
}

//Interface QAbstractItemModel
int ContentModel::columnCount(const QModelIndex& parent) const{
    return content == nullptr? 0 : 2;
}

int ContentModel::rowCount(const QModelIndex& parent) const{
    if(content == nullptr)
        return 0;

    auto id = 0;
    if(parent.isValid())
        id = content->childsId(parent.internalId(), parent.row());
    if(id == -1)
        return 0;
    return content->rowCount(id);
}

QModelIndex ContentModel::index(int row, int column, const QModelIndex& parent) const{
    if(content == nullptr)
        return QModelIndex();

    auto id = 0;
    if(parent.isValid())
        id = content->childsId(parent.internalId(), parent.row());
    return createIndex(row, column, id);
}

QVariant ContentModel::data(const QModelIndex& index, int role) const{
    if(!index.isValid() || content == nullptr)
        return QVariant();

    switch(role){
    case Qt::DisplayRole:
    case Qt::ToolTipRole:
        if(index.column() == 0)
            return QString::fromUtf8(content->title(index.internalId(), index.row()).c_str());
        return content->pageNumber(index.internalId(), index.row());
        break;
    }
    return QVariant();
}

QModelIndex ContentModel::parent(const QModelIndex& child) const{
    if(!child.isValid() || content == nullptr)
        return QModelIndex();

    auto p = content->parentId(child.internalId());
    return createIndex(p.second, 1, p.first);
}

QVariant ContentModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation == Qt::Vertical || role != Qt::DisplayRole)
        return QAbstractItemModel::headerData(section, orientation, role);
    switch(section){
    case 0:
        return tr("Content");
    case 1:
        return tr("Page");
    }

    return QAbstractItemModel::headerData(section, orientation, role);
}
