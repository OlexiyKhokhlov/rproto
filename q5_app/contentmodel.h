#pragma once

#include <QAbstractItemModel>

class ContentModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    ContentModel();
    virtual ~ContentModel();

    //Interface QAbstractItemModel
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;

private:

};
