#include "contentview.h"
#include "contentmodel.h"

ContentView::ContentView(QWidget* parent)
    :QTreeView(parent)
{
    cmodel = new ContentModel(this);
    setModel(cmodel);

    connect(this, SIGNAL(activated(QModelIndex)), this, SLOT(onActivated(QModelIndex)));
}

void ContentView::setContent(RProto::IContentPtrT c){
    cmodel->setContent(c);
}

void ContentView::setPage(int p){
    current_page = p;
    emit pageChanged(p);
}

void ContentView::onActivated(const QModelIndex& index){
    if(index.isValid()){
        auto pindex = index.model()->index(index.row(), 1, index.parent());
        auto p = index.model()->data(pindex, Qt::DisplayRole).toInt();
        setPage(p);
    }
}
