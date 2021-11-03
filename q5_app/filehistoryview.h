#pragma once

#include <QListView>

class FileHistoryModel;
class QSettings;

class FileHistoryView : public QListView
{
    Q_OBJECT
public:
    FileHistoryView(QWidget* parent = nullptr);

    void loadFrom(QSettings& settings);
    void saveTo(QSettings& settings) const;

signals:
    void openFile(QString path);

public slots:
    void onFileOpened(const QString& file_path);

private slots:
    void onActivated(const QModelIndex&);

private:
    FileHistoryModel*   model = nullptr;
};
