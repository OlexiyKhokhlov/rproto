#pragma once

#include <QAbstractItemModel>

namespace RProto{
    class IContent;
}

class ContentModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    ContentModel(QObject* parent=0);
    virtual ~ContentModel();

    void setContent(RProto::IContent *c);

    //Interface QAbstractItemModel
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    RProto::IContent *content;
};
