#include "pageview.h"

#include <utility>
#include <QAction>
#include <QPaintEvent>
#include <QPixmap>
#include <QPainter>
#include <QScrollBar>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QDebug>

#include <iimagetile.h>
#include <irect.h>
#include <ipoint.h>

PageView::PageView(QWidget *parent) :
    QAbstractScrollArea(parent)
  ,book(nullptr)
  ,layout(nullptr)
  ,renderer(nullptr)
  ,screenPixmap(nullptr)
  ,currentPage(0)
  ,clearPage(false)
{
    viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
    viewport()->setAttribute(Qt::WA_PaintOnScreen);
    viewport()->setAttribute(Qt::WA_NoSystemBackground);
    viewport()->setMouseTracking (true);

    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));
    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));

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
    qDebug() << __FUNCTION__;

    delete screenPixmap;
}

void PageView::setBook(RProto::IBook*  bk)
{
    book = bk;
    if(book == nullptr)
        return;

    auto dpiX = QApplication::desktop()->physicalDpiX();
    auto dpiY = QApplication::desktop()->physicalDpiY();

    layout = book->createLayout(dpiX, dpiY);
    renderer = book->createRenderer();

    //connect(layout->qobject(), SIGNAL(pageSizeChanged(int,QSize)), this, SLOT(onLayoutChanged(int,QSize)));
//    connect(layout->qobject(),
//            SIGNAL(pageSizeChanged(int,QSize)), this,
//            SLOT(onLayoutChanged(int,QSize)),
//            Qt::QueuedConnection);

    layout->startLayouting();
    currentPage = 0;
    currentOffset = QPoint(0,0);
    updateScrollBars();
    updateViewport();
}

void PageView::pageUp()
{
    if(layout == nullptr)
        return;

    if(viewport()->height() < layout->pageSize().second){
        auto oldY = currentOffset.y();
        auto newY = std::max(0, oldY-viewport()->height());
        if(oldY != newY){
            verticalScrollBar()->setValue(newY);
            return;
        }
    }

    auto newPage = std::max(0, currentPage-1);
    if(newPage != currentPage){
        currentPage = newPage;
        auto y = std::max(0, layout->pageSize(currentPage).second-viewport()->height());
        currentOffset.setY(y);
        updateScrollBars();
        updateViewport();
        clearPage = true;
        viewport()->update();
    }
}

void PageView::pageDown()
{
    if(layout == nullptr)
        return;

    if(viewport()->height() < layout->pageSize().second){
        auto oldY = currentOffset.y();
        auto newY = std::min(layout->pageSize().second-viewport()->height()
                               , oldY+viewport()->height());
        if(oldY != newY){
            verticalScrollBar()->setValue(newY);
            return;
        }
    }

    auto newPage = std::min(currentPage+1, layout->pages()-1);
    if(newPage != currentPage){
        currentPage = newPage;
        currentOffset.setY(0);
        updateScrollBars();
        updateViewport();
        clearPage = true;
        viewport()->update();
    }
}

void PageView::resizeEvent(QResizeEvent* event)
{
    qDebug() << __FUNCTION__;
    updateScrollBars();
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
    qDebug() << __FUNCTION__;

    if( screenPixmap == NULL
            || clearPage){
        QPainter    painter(viewport());
        painter.fillRect(event->rect(), Qt::gray);
        if(!clearPage)
            return;
        clearPage = false;
    }

    QPainter    painter(viewport());
    auto dx = std::max(0, (viewport()->width()-screenPixmap->width())/2);
    auto dy = std::max(0, (viewport()->height()-screenPixmap->height())/2);
    auto dstRect = event->rect();
    dstRect.moveTo(dx, dy);
    auto srcRect = event->rect();
    srcRect.moveTo(currentOffset);
    painter.drawPixmap(dstRect, *screenPixmap, srcRect);
}

void PageView::onScrollBarValueChanged(int /*value*/)
{
    qDebug() << __FUNCTION__;

    QPoint offset(horizontalScrollBar()->value(),
                           verticalScrollBar()->value());
    if(currentOffset != offset){
        currentOffset = offset;
        viewport()->update();
    }
}

void PageView::onLayoutChanged(int page, QSize /*size*/)
{
    qDebug() << __FUNCTION__;

    if(currentPage == page){
        updateScrollBars();
        updateViewport();
    }
}

void PageView::updateViewport()
{
    if(layout == nullptr)
        return;

    delete screenPixmap;
    auto sz = layout->pageSize(currentPage);
    screenPixmap = new QPixmap(sz.first, sz.second);
    screenPixmap->fill(Qt::gray);

    auto lrect = layout->createRect(currentPage,
                                     0, 0,
                                     viewport()->size().width(), viewport()->size().height());
    lrect->addRef();
    auto tile = renderer->renderRect(lrect);

    assert(tile != nullptr);
    tile->addRef();

    RProto::IRect *r = nullptr;
    tile->QueryInterface(RProto::IRect::iid, (void**)&r);
    QImage img = QImage((const unsigned char*)tile->data(),
                        r->width(), r->height()
                        ,QImage::Format_RGB32);
    {
        QPainter painter(screenPixmap);
        painter.drawImage(0, 0, img, 0,0, r->width(), r->height());
    }

    lrect->release();
    tile->release();
}

void PageView::updateScrollBars()
{
    if(layout == nullptr)
        return;

    auto sz = layout->pageSize(currentPage);
    QSize size(sz.first, sz.second);
    verticalScrollBar()->setPageStep(viewport()->size().height());
    horizontalScrollBar()->setPageStep(viewport()->size().width());

    verticalScrollBar()->setRange(0, size.height() - viewport()->size().height());
    verticalScrollBar()->setValue(currentOffset.y());
    if(size.height() <= viewport()->size().height())
        verticalScrollBar()->setVisible(false);
    else
        verticalScrollBar()->setVisible(true);

    horizontalScrollBar()->setRange(0, size.width() - viewport()->size().width());
    horizontalScrollBar()->setValue(currentOffset.x());
    if(size.width() <= viewport()->size().width())
        horizontalScrollBar()->setVisible(false);
    else
        horizontalScrollBar()->setVisible(true);
}
