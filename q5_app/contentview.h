#pragma once

#include <forward.h>
#include <QTreeView>

class ContentModel;

class ContentView : public QTreeView
{
    Q_OBJECT
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)

public:
    ContentView(QWidget* parent=nullptr);

    void setContent(RProto::IContentPtrT c);

    int page()const{
        return current_page;
    }

    void setPage(int p);

signals:
    void pageChanged(int page);

public slots:
    void onPageHasChanged(int page);

private slots:
    void onActivated(const QModelIndex& index);

private:
    ContentModel *cmodel = nullptr;
    int current_page = 0;
};
