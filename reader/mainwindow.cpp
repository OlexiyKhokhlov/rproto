#include "mainwindow.h"
#include "pageview.h"

#include <util/singletone.h>
//#include <bookfactory.h>
//#include <djvuplugin.h>
//#include <djvubook.h>
//#include <djvupagelayout.h>

#include <g3log/g2log.hpp>

#include <QSettings>
#include <QFileDialog>
#include <QAction>

MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags)
{
//    bookFactory = new RProto::BookFactory();
//    RProto::DjVuPlugin* plug = new RProto::DjVuPlugin();
//    bookFactory->registerPlugin(plug);

    setMinimumWidth(600);
    setMinimumHeight(400);

    restoreGeometry(Singletone<QSettings>::instance().value("MainWindow/geometry").toByteArray());
    restoreState(Singletone<QSettings>::instance().value("MainWindow/state").toByteArray());
    
    pageView = new PageView(this);
    setCentralWidget(pageView);

    onUpdateTitle(QString());

    QAction* openFile = new QAction(tr("&Open file"), this);
    openFile->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    addAction(openFile);
    connect(openFile, SIGNAL(triggered(bool)), this, SLOT(onOpenFile()));

    QAction* pageUp = new QAction(tr("&pageUp"), this);
    pageUp->setShortcut(QKeySequence(Qt::Key_PageUp));
    addAction(pageUp);
    connect(pageUp, SIGNAL(triggered(bool)), pageView, SLOT(pageUp()));

    QAction* pageDown = new QAction(tr("&pageDown"), this);
    pageDown->setShortcut(QKeySequence(Qt::Key_PageDown));
    addAction(pageDown);
    connect(pageDown, SIGNAL(triggered(bool)), pageView, SLOT(pageDown()));
}

MainWindow::~MainWindow()
{
    delete bookFactory;
}

void MainWindow::closeEvent( QCloseEvent* )
{
    Singletone<QSettings>::instance().setValue("MainWindow/geometry", saveGeometry());
    Singletone<QSettings>::instance().setValue("MainWindow/state", saveState());
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
                                                    tr("Book Files (%1)").arg("*.djvu"),
                                                    0,
                                                    QFileDialog::DontUseNativeDialog );
    if(fileName.isEmpty())
      return;

//    LOG(INFO) << "Start open file" << fileName;
//    auto book = bookFactory->createBook(fileName);
//    pageView->setBook(book);
}
