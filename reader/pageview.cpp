#include "pageview.h"

#include <utility>
#include <QAction>
#include <QPaintEvent>
#include <QPixmap>
#include <QPainter>
#include <QScrollBar>
#include <QRect>

PageView::PageView(QWidget *parent) :
    QAbstractScrollArea(parent)
  ,screenPixmap(nullptr)
{
    viewport()->setAttribute(Qt::WA_PaintOnScreen);
    viewport()->setAttribute(Qt::WA_NoSystemBackground);
    viewport()->setMouseTracking (true);

    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));
    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));

    QAction *nextPageAction =new  QAction(QIcon(), tr("Next Page"), this);
    nextPageAction->setShortcut(QKeySequence("PgDown"));
    connect(nextPageAction, SIGNAL(triggered()), this, SLOT(pageDown()));
    addAction(nextPageAction);

    QAction *prevPageAction =new  QAction(QIcon(), tr("Previous Page"), this);
    prevPageAction->setShortcut(QKeySequence("PgUp"));
    connect(prevPageAction, SIGNAL(triggered()), this, SLOT(pageUp()));
    addAction(prevPageAction);

//    QAction *homePageAction =new  QAction(QIcon(), tr("Home"), this);
//    homePageAction->setShortcut(QKeySequence("Home"));
//    connect(homePageAction, SIGNAL(triggered()), this, SLOT(homePage()));
//    addAction(homePageAction);

//    QAction *endPageAction =new  QAction(QIcon(), tr("End"), this);
//    endPageAction->setShortcut(QKeySequence("End"));
//    connect(endPageAction, SIGNAL(triggered()), this, SLOT(endPage()));
//    addAction(endPageAction);

}

PageView::~PageView()
{
    delete screenPixmap;
}

//void PageView::setBook(boost::intrusive_ptr<RProto::IBook>  book)
//{
//    if(book == nullptr)
//        return;

//    layout = book->createLayout();
//    renderer = book->createRenderer();
//    connect(layout->qobject(), SIGNAL(layoutChanged(int,QSize)), this, SLOT(onLayoutChanged(int,QSize)));
//    update();
//}

void PageView::pageUp()
{
}

void PageView::pageDown()
{
    currentPage = std::max((size_t)0, currentPage-1);
    update();
}

void PageView::resizeEvent(QResizeEvent* event)
{
    //qDebug() << __FUNCTION__;
    delete screenPixmap;

    updateScrollBars();

    screenPixmap = new QPixmap(event->size());
    screenPixmap->fill(Qt::gray);

//    if(renderer ==nullptr) return;

//    QRect rect(QPoint(0,0), event->size());
//    QImage img = renderer->renderRect(0, rect);
//    {
//        QPainter painter(screenPixmap);
//        painter.drawImage(0,0, img);
//    }
}

bool PageView::viewportEvent(QEvent* event)
{
    switch(event->type())
    {
    case QEvent::Paint:
        event->accept();
        viewportPaintEvent(reinterpret_cast<QPaintEvent *>(event));
        return true;

//    QEvent::MouseButtonDblClick
//    case QEvent::MouseButtonPress:
//        event->accept();
//        onMousePress(dynamic_cast<QMouseEvent*>(event));
//        return true;
//    case QEvent::MouseButtonRelease:
//        event->accept();
//        onMouseRelease(dynamic_cast<QMouseEvent*>(event));
//        return true;
//    case QEvent::MouseMove:
//        event->accept();
//        onMouseMove(dynamic_cast<QMouseEvent*>(event));
//        return true;
////    QEvent::MouseTrackingChange
//     case QEvent::ToolTip:
//        if(!currentLink.isEmpty() && !currentLink.startsWith("pbr:")){
//            event->accept();
//            QToolTip::showText(helpEvent->globalPos(),     currentLink);
//        }else{
//            QToolTip::hideText();
//            event->ignore();
//        }
//        return true;

     default:
        return QAbstractScrollArea::viewportEvent(event);
    }
    return QAbstractScrollArea::viewportEvent(event);
}

void PageView::viewportPaintEvent(QPaintEvent * event)
{
    if( screenPixmap == NULL )
        return;

    QPainter    painter(viewport());
    painter.drawPixmap(event->rect(), *screenPixmap, event->rect());
}

void PageView::onScrollBarValueChanged(int /*value*/)
{
    //qDebug() << __FUNCTION__;

    QPoint offset(horizontalScrollBar()->value(),
                           verticalScrollBar()->value());
    if(currentOffset != offset){
        currentOffset = offset;
        updateViewport();
    }
}

void PageView::onLayoutChanged(int page, QSize size)
{
    if(currentPage == page){
        updateScrollBars();
    }
}

void PageView::updateViewport()
{
    QRect rect(currentOffset, viewport()->size());
//    QImage img = renderer->renderRect(currentPage, rect);
//    {
//        QPainter painter(screenPixmap);
//        painter.drawImage(0,0, img);
//    }
}

void PageView::updateScrollBars()
{
//    if(layout == nullptr)
//        return;

//    QSize size = layout->pageSize(currentPage);
//    verticalScrollBar()->setPageStep(viewport()->size().height());
//    horizontalScrollBar()->setPageStep(viewport()->size().width());

//    verticalScrollBar()->setRange(0, size.height() - viewport()->size().height());
//    //verticalScrollBar()->setValue(currentPage->offset().y());
//    if(size.height() <= viewport()->size().height())
//        verticalScrollBar()->setVisible(false);
//    else
//        verticalScrollBar()->setVisible(true);

//    horizontalScrollBar()->setRange(0, size.width() - viewport()->size().width());
//    //horizontalScrollBar()->setValue(currentPage->offset().x());
//    if(size.width() <= viewport()->size().width())
//        horizontalScrollBar()->setVisible(false);
//    else
//        horizontalScrollBar()->setVisible(true);
}
