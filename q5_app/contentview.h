#pragma once

#include <QTreeView>

namespace RProto{
    class IContent;
}
class ContentModel;

class ContentView : public QTreeView
{
    Q_OBJECT
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
public:
    ContentView(QWidget* parent=0);
    void setContent(RProto::IContent* c);

    int page()const{
        return current_page;
    }

    void setPage(int p);

signals:
    void pageChanged(int page);

private slots:
    void onActivated(const QModelIndex& index);

private:
    ContentModel *cmodel;
    int current_page;
};
