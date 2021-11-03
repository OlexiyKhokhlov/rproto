#pragma once

#include <forward.h>
#include <QMainWindow>
#include <memory>

namespace RProto{
    class BookFactory;
}

class PageView;
class ContentView;
class FileHistoryView;
class PageSpinBox;

class QComboBox;
class QSpinBox;
class QLabel;
class QListView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = Qt::WindowFlags());
    virtual ~MainWindow();

public slots:
    void onUpdateTitle(const QString& new_title);
    void onOpenFile();
    void onOpenFile(const QString& path);
    void onNavigationMode(bool checked);
    void onFullScreen(bool checked);
    void onZoomIn();
    void onFitChanged(int index);
    void onZoomOut();
    void onRotateCW();
    void onRotateCCW();
    void onPageChanged(int nr);

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    std::unique_ptr<RProto::BookFactory> bookFactory;;
    PageView*            pageView  = nullptr;
    ContentView*         contentView = nullptr;
    FileHistoryView*     historyView = nullptr;

    QComboBox*           zoomCombo = nullptr;
    PageSpinBox*         pageSpinBox = nullptr;
};
