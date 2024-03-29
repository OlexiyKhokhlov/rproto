#include "contentview.h"
#include "contentmodel.h"

#include <QHeaderView>

ContentView::ContentView(QWidget* parent)
    : QTreeView(parent)
{
    cmodel = new ContentModel(this);
    setModel(cmodel);

    connect(this, SIGNAL(activated(QModelIndex)), this, SLOT(onActivated(QModelIndex)));
}

void ContentView::setContent(RProto::IContentPtrT c){
    cmodel->setContent(c);

    if (c != nullptr) {
        auto* h = header();
        h->setStretchLastSection(false);
        h->setSectionResizeMode(0, QHeaderView::Stretch);
        h->setSectionResizeMode(h->count()-1, QHeaderView::ResizeToContents);
        h->resetDefaultSectionSize();
        setHeaderHidden(true);
    }
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

void ContentView::onPageHasChanged(int page) {
    auto index = currentIndex();
    if (index.isValid()) {
        index = cmodel->index(index.row(), 1, index.parent());
        if (cmodel->data(index, Qt::DisplayRole).toInt() == page - 1)
            return;
    }
    index = cmodel->indexByPage(page);
    if (index.isValid()) {
        blockSignals(true);
        setCurrentIndex(index);
        blockSignals(false);
    }
}
