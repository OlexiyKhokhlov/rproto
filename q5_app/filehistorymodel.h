#pragma once

#include <QAbstractItemModel>
#include <QList>
#include <QStringList>

class QSettings;

class FileHistoryModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    using FileListT = QStringList;

    FileHistoryModel(QObject* parent=nullptr);
    virtual ~FileHistoryModel();

    void loadFrom(QSettings& settings);
    void saveTo(QSettings& settings) const;

    //Interface QAbstractItemModel
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

public slots:
    void onFileOpened(QString file_path);

private:
    FileListT  file_list;
};
