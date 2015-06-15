#pragma once

#include <QMainWindow>

class ContentView;

class PageView;
namespace RProto{
    class BookFactory;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget * parent = 0, Qt::WindowFlags flags = 0);
    virtual ~MainWindow();

public slots:
    void onUpdateTitle(QString new_title);
    void onOpenFile();
    void onNavigationMode(bool checked);

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    RProto::BookFactory *bookFactory;
    PageView	*pageView;
    ContentView *contentView;
};
