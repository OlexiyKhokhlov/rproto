#include "mainwindow.h"
#include "pageview.h"
#include "contentview.h"
#include "filehistoryview.h"

#include <bookfactory.h>
#include <ibook.h>

#include <QLineEdit>
#include <QLabel>
#include <QSettings>
#include <QFileDialog>
#include <QAction>
#include <QDockWidget>
#include <QToolBar>
#include <QToolButton>
#include <QHBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QListView>
#include <QDebug>

MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
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

    QDockWidget* historyDoc = new QDockWidget(tr("History"), nullptr);
    historyDoc->setObjectName("HistoryDock");
    historyView = new FileHistoryView(historyDoc);
    historyView->loadFrom(settings);
    connect(historyView, SIGNAL(openFile(const QString&)), this, SLOT(onOpenFile(const QString&)));
    historyDoc->setWidget(historyView);
    addDockWidget(Qt::LeftDockWidgetArea, historyDoc);

    QDockWidget* contentDock = new QDockWidget(tr("Content"), nullptr);
    contentDock->setObjectName("ContentDock");
    contentView = new ContentView(contentDock);
    contentDock->setWidget(contentView);
    addDockWidget(Qt::LeftDockWidgetArea, contentDock);

    tabifyDockWidget(contentDock, historyDoc);

    QToolBar *toolbar = new QToolBar(tr("Main Toolbar"));
    toolbar->setObjectName("MainToolBar");

    QAction* openFile = toolbar->addAction(QIcon(":/icons/open"), tr("&Open File"), this, SLOT(onOpenFile()));
    openFile->setShortcut(QKeySequence(QKeySequence::Open));

    QAction* fullscreenMode = toolbar->addAction(QIcon(":/icons/fullscreen"), tr("&Fullscreen Mode"), this, SLOT(onFullScreen(bool)));
    fullscreenMode->setShortcut(QKeySequence(QKeySequence::FullScreen));
    fullscreenMode->setCheckable(true);

    QAction* navMode = toolbar->addAction(QIcon(":/icons/mouse"), tr("&Navigation Mode"), this, SLOT(onNavigationMode(bool)));
    navMode->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    navMode->setCheckable(true);

    QAction* zoomOut = toolbar->addAction(QIcon(":/icons/zoom_out"), tr("&Zoom Out"), this, SLOT(onZoomOut()));
    zoomOut->setShortcut(QKeySequence(QKeySequence::ZoomOut));

    zoomCombo = new QComboBox(toolbar);
    zoomCombo->addItem(tr("Fit width"),  QVariant::fromValue(PageView::PageFit::FIT_WIDTH));
    zoomCombo->addItem(tr("Fit height"), QVariant::fromValue(PageView::PageFit::FIT_HEIGHT));
    zoomCombo->addItem(tr("Fit page"),   QVariant::fromValue(PageView::PageFit::FIT_PAGE));
    zoomCombo->addItem(tr("Manual"),     QVariant::fromValue(PageView::PageFit::FIT_MANUAL));
    connect(zoomCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onFitChanged(int)));
    toolbar->addWidget(zoomCombo);

    QAction* zoomIn = toolbar->addAction(QIcon(":/icons/zoom_in"), tr("&Zoom In"), this, SLOT(onZoomIn()));
    zoomIn->setShortcut(QKeySequence(QKeySequence::ZoomIn));

    QAction* rotateCCW = toolbar->addAction(QIcon(":/icons/rotate_ccw"), tr("&Rotate Counterclockwise"), this, SLOT(onRotateCCW()));
    rotateCCW->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));

    QAction* rotateCW = toolbar->addAction(QIcon(":/icons/rotate_cw"), tr("&Rotate Clockwise"), this, SLOT(onRotateCW()));
    rotateCW->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));

    toolbar->addSeparator();
    toolbar->addWidget(new QLabel(tr("Page"), toolbar));
    page_spin = new QSpinBox(toolbar);
    page_spin->setRange(1, 1);
    connect(page_spin, SIGNAL(valueChanged(int)), this, SLOT(onPageChanged(int)));
    toolbar->addWidget(page_spin);
    max_page = new QLabel("/1", toolbar);
    toolbar->addWidget(max_page);

    toolbar->addSeparator();
//    toolbar->addWidget(new QLabel(tr("Search:"), toolbar));
//    toolbar->addWidget(new QLineEdit(toolbar));

    addToolBar(toolbar);

    connect(contentView, SIGNAL(pageChanged(int)), pageView, SLOT(setPage(int)));

    bookFactory = std::make_unique<RProto::BookFactory>();
}

MainWindow::~MainWindow()
{
    contentView->setContent(nullptr);
    pageView->setBook(nullptr);
}

void MainWindow::closeEvent( QCloseEvent* )
{
    QSettings settings;
    settings.setValue("MainWindow/geometry", saveGeometry());
    settings.setValue("MainWindow/state", saveState());
    historyView->saveTo(settings);
}

void MainWindow::onUpdateTitle(const QString& new_title)
{
    QString title( tr("R-Proto"));
    if(!new_title.isEmpty()){
        title += " - " + new_title;
    }

    setWindowTitle(title);
}

void MainWindow::onOpenFile()
{
    QString file_path = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "",
                                                    tr("Book Files (%1)").arg("*.pdf"),
                                                    0,
                                                    QFileDialog::DontUseNativeDialog );
    if(!file_path.isEmpty())
      onOpenFile(file_path);
}

void MainWindow::onOpenFile(const QString& file_path) {
    auto book = bookFactory->createBook(file_path);
    if (book == nullptr) {
        return;
    }

    auto content = book->createContent();
    contentView->setContent(content);
    pageView->setBook(book);

    auto mpg = pageView->getMaxPage()+1;
    page_spin->setRange(1, mpg);
    max_page->setText(QString("/%1").arg(mpg));

    historyView->onFileOpened(file_path);
}

void MainWindow::onNavigationMode(bool checked){
    if(checked)
        pageView->setNavigationMode(PageView::NavigationMode::NAVIGATION_DRAG);
    else
        pageView->setNavigationMode(PageView::NavigationMode::NAVIGATION_POINTER);
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

void MainWindow::onFitChanged(int index) {
    if (index != -1) {
        auto fit = zoomCombo->itemData(index).value<PageView::PageFit>();
        pageView->setPageFitMode(fit);
    }
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

void MainWindow::onPageChanged(int nr) {
    pageView->setPage(nr-1);
}
