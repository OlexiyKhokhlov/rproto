#include "mainwindow.h"
#include "pageview.h"
#include "contentview.h"

#include <util/singletone.h>
#include <bookfactory.h>
#include <ibook.h>

//#include <g3log/g2log.hpp>

#include <QSettings>
#include <QFileDialog>
#include <QAction>
#include <QDockWidget>
#include <QToolBar>
#include <QToolButton>
#include <QHBoxLayout>
#include <QDebug>

MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags)
    ,bookFactory(nullptr)
{
//    bookFactory = new RProto::BookFactory();
//    RProto::DjVuPlugin* plug = new RProto::DjVuPlugin();
//    bookFactory->registerPlugin(plug);

    setMinimumWidth(600);
    setMinimumHeight(400);

    QSettings settings;
    restoreGeometry(settings.value("MainWindow/geometry").toByteArray());
    restoreState(settings.value("MainWindow/state").toByteArray());
    
    pageView = new PageView(this);
    setCentralWidget(pageView);

    onUpdateTitle(QString());

    QAction* pageUp = new QAction(tr("&pageUp"), this);
    pageUp->setShortcut(QKeySequence(Qt::Key_PageUp));
    addAction(pageUp);
    connect(pageUp, SIGNAL(triggered(bool)), pageView, SLOT(pageUp()));

    QAction* pageDown = new QAction(tr("&pageDown"), this);
    pageDown->setShortcut(QKeySequence(Qt::Key_PageDown));
    addAction(pageDown);
    connect(pageDown, SIGNAL(triggered(bool)), pageView, SLOT(pageDown()));

    QAction* home = new QAction(tr("&home"), this);
    home->setShortcut(QKeySequence(Qt::Key_Home));
    addAction(home);
    connect(home, SIGNAL(triggered(bool)), pageView, SLOT(toHome()));

    QAction* end = new QAction(tr("&end"), this);
    end->setShortcut(QKeySequence(Qt::Key_End));
    addAction(end);
    connect(end, SIGNAL(triggered(bool)), pageView, SLOT(toEnd()));

    QDockWidget* contentDock = new QDockWidget("Contents", nullptr);
    contentDock->setObjectName("ContentDock");
    contentView = new ContentView(contentDock);
    contentDock->setWidget(contentView);
    addDockWidget(Qt::LeftDockWidgetArea, contentDock);

    QToolBar *toolbar = new QToolBar(tr("Main Toolbar"));
    toolbar->setObjectName("MainToolBar");

    QAction* openFile = toolbar->addAction(QIcon(":/icons/open"), tr("&Open File"), this, SLOT(onOpenFile()));
    openFile->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));

    QAction* fullscreenMode = toolbar->addAction(QIcon(":/icons/fullscreen"), tr("&Fullscreen Mode"), this, SLOT(onFullScreen(bool)));
    fullscreenMode->setShortcut(QKeySequence(Qt::Key_F11));
    fullscreenMode->setCheckable(true);

    QAction* navMode = toolbar->addAction(QIcon(":/icons/mouse"), tr("&Navigation Mode"), this, SLOT(onNavigationMode(bool)));
    navMode->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    navMode->setCheckable(true);

    QAction* zoomOut = toolbar->addAction(QIcon(":/icons/zoom_out"), tr("&Zoom Out"), this, SLOT(onZoomOut()));
    zoomOut->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus));

    QAction* zoomIn = toolbar->addAction(QIcon(":/icons/zoom_in"), tr("&Zoom In"), this, SLOT(onZoomIn()));
    zoomIn->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Plus));

    QAction* rotateCCW = toolbar->addAction(QIcon(":/icons/rotate_ccw"), tr("&Rotate Counterclockwise"), this, SLOT(onRotateCCW()));
    rotateCCW->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));

    QAction* rotateCW = toolbar->addAction(QIcon(":/icons/rotate_cw"), tr("&Rotate Clockwise"), this, SLOT(onRotateCW()));
    rotateCW->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));

    addToolBar(toolbar);

    connect(contentView, SIGNAL(pageChanged(int)), pageView, SLOT(setPage(int)));
    bookFactory = new RProto::BookFactory();
}

MainWindow::~MainWindow()
{
    qDebug() << __FUNCTION__;
    contentView->setContent(nullptr);
    pageView->setBook(nullptr);
    delete bookFactory;
}

void MainWindow::closeEvent( QCloseEvent* )
{
    QSettings settings;
    settings.setValue("MainWindow/geometry", saveGeometry());
    settings.setValue("MainWindow/state", saveState());
}

void MainWindow::onUpdateTitle(QString new_title)
{
    QString title( tr("R-Proto"));
    if(!new_title.isEmpty()){
        title += " - " + new_title;
    }

    setWindowTitle(title);
}

void MainWindow::onOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "",
                                                    tr("Book Files (%1)").arg("*.pdf"),
                                                    0,
                                                    QFileDialog::DontUseNativeDialog );
    if(fileName.isEmpty())
      return;

//    Plugin *pl = new Plugin();

//    auto book = pl->createBook(fileName.toLocal8Bit().constData());

////    LOG(INFO) << "Start open file" << fileName;
    auto book = bookFactory->createBook(fileName);
    if (book == nullptr)
        return;

    auto content = book->createContent();
    contentView->setContent(content);
    pageView->setBook(book);
}

void MainWindow::onNavigationMode(bool checked){
    if(checked)
        pageView->setNavigationMode(PageView::NAVIGATION_DRAG);
    else
        pageView->setNavigationMode(PageView::NAVIGATION_POINTER);
}

void MainWindow::onFullScreen(bool checked){
    if(checked)
        setWindowState(Qt::WindowFullScreen);
    else
        setWindowState(Qt::WindowActive);
}

void MainWindow::onZoomIn(){
    pageView->setZoom(pageView->zoom()*1.1);
}

void MainWindow::onZoomOut(){
    pageView->setZoom(pageView->zoom()*0.9);
}

void MainWindow::onRotateCW(){
//not impl
}

void MainWindow::onRotateCCW(){
//not impl
}

