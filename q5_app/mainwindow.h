#pragma once

#include <QMainWindow>
#include <memory>

class QComboBox;
class ContentView;
class QSpinBox;
class QLabel;

class PageView;
namespace RProto{
    class BookFactory;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = Qt::WindowFlags());
    virtual ~MainWindow();

public slots:
    void onUpdateTitle(QString new_title);
    void onOpenFile();
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
    QComboBox*           zoomCombo = nullptr;
    QSpinBox*            page_spin = nullptr;
    QLabel*              max_page = nullptr;


};
