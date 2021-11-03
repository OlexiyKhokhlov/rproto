#include "filehistoryview.h"
#include "filehistorymodel.h"

FileHistoryView::FileHistoryView(QWidget* parent)
    : QListView(parent)
{
    model = new FileHistoryModel(this);
    setModel(model);
    connect(this, SIGNAL(activated(const QModelIndex&)), this, SLOT(onActivated(const QModelIndex&)));
}

void FileHistoryView::loadFrom(QSettings& settings) {
    model->loadFrom(settings);
}

void FileHistoryView::saveTo(QSettings& settings) const {
    model->saveTo(settings);
}

void FileHistoryView::onFileOpened(const QString& file_path) {
    model->onFileOpened(file_path);
}

void FileHistoryView::onActivated(const QModelIndex& index) {
    if (index.isValid()) {
        emit openFile(model->data(index, Qt::DisplayRole).toString());
    }
}
