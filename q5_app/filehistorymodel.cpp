#include "filehistorymodel.h"
#include "contentmodel.h"

#include <icontent.h>
#include <QSettings>
#include <utility>

constexpr char SettingsKey[]{"FileHistory"};

Q_DECLARE_METATYPE(QStringList)

FileHistoryModel::FileHistoryModel(QObject* parent)
    : QAbstractItemModel(parent)
{}

FileHistoryModel::~FileHistoryModel(){
}

void FileHistoryModel::loadFrom(QSettings& settings) {
    beginResetModel();
    file_list = settings.value(SettingsKey).toStringList();
    endResetModel();
}

void FileHistoryModel::saveTo(QSettings& settings) const {
    settings.setValue(SettingsKey, QVariant::fromValue(file_list));
}

//Interface QAbstractItemModel
int FileHistoryModel::columnCount(const QModelIndex& /*parent*/) const{
    return 1;
}

int FileHistoryModel::rowCount(const QModelIndex& parent) const{
    return parent.isValid()? 0 : file_list.size();
}

QModelIndex FileHistoryModel::index(int row, int column, const QModelIndex& parent) const {
    return parent.isValid()? QModelIndex() : createIndex(row, column);
}

QVariant FileHistoryModel::data(const QModelIndex& index, int role) const{
    if(!index.isValid())
        return QVariant();

    switch(role){
    case Qt::DisplayRole:
    case Qt::ToolTipRole:
        if (index.column() == 0 && index.row() < file_list.size())
        return file_list[index.row()];
        break;
    }
    return QVariant();
}

QModelIndex FileHistoryModel::parent(const QModelIndex& /*child*/) const{
    return QModelIndex();
}

QVariant FileHistoryModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation == Qt::Vertical || role != Qt::DisplayRole)
        return QAbstractItemModel::headerData(section, orientation, role);
    switch(section){
    case 0:
        return tr("File");
    }

    return QAbstractItemModel::headerData(section, orientation, role);
}

void FileHistoryModel::onFileOpened(QString file_path) {
    int i = 0;
    for(const auto& p : file_list){
        if(p == file_path) {
            if (i == 0) return;
            beginMoveRows(QModelIndex(), i, i, QModelIndex(), 0);
            file_list.removeAt(i);
            file_list.push_front(file_path);
            endMoveRows();
            return;
        }
        i++;
    }
    beginInsertRows(QModelIndex(), 0, 0);
    file_list.push_front(file_path);
    endInsertRows();
}
