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
  ,fitMode(FIT_HEIGHT)
  ,currentPage(0)
  ,clearPage(false)
{
    viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
//    viewport()->setAttribute(Qt::WA_PaintOnScreen);
    viewport()->setAttribute(Qt::WA_NoSystemBackground);
    viewport()->setMouseTracking(true);

    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));
    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));
}

PageView::~PageView()
{
}

void PageView::setBook(RProto::IBook*  bk)
{
    book = bk;
    if(book.Get() == nullptr)
        return;

    auto dpiX = QApplication::desktop()->physicalDpiX();
    auto dpiY = QApplication::desktop()->physicalDpiY();

    layout = book->createLayout(dpiX, dpiY);
    renderer = book->createRenderer();

    auto listener = static_cast<RProto::ILayoutListener*>(this);
    layout->addListener(listener);

    layout->startLayouting();
    currentOffset = QPoint(0,0);
    setNewPage(0);
}

void PageView::setPage(int pg){
    if(layout.Get() == nullptr)
        return;

    auto page = std::max(0, pg);
    page = std::min(page, layout->pages()-1);
    if(currentPage != page){
        currentPage = page;
        currentOffset = QPoint(0,0);

        emit pageChanged(currentPage);
    }
}

float PageView::zoom()const{
    if(layout.Get() == nullptr)
        return 1.0;
    return layout->pageZoom(currentPage);
}

void PageView::setZoom(float zm){
    if(layout.Get() == nullptr)
        return;

    layout->setPageZoom(zm);

    updateScrollBars();
    updateViewport();
}

void PageView::setPageFitMode(PageFit fit){
    fitMode = fit;
}

void PageView::pageUp()
{
    if(layout.Get() == nullptr)
        return;

    int page_height = layout->pageSize().second * layout->pageZoom(currentPage);
    if(viewport()->height() < page_height){
        auto oldY = currentOffset.y();
        auto newY = std::max(0, oldY-viewport()->height());
        if(oldY != newY){
            verticalScrollBar()->setValue(newY);
            return;
        }
    }

    auto newPage = std::max(0, currentPage-1);
    if(newPage != currentPage){
        setNewPage(newPage);
    }
}

void PageView::pageDown()
{
    if(layout.Get() == nullptr)
        return;

    int page_height = layout->pageSize().second * layout->pageZoom(currentPage);
    int wp_height = viewport()->height();
    if(wp_height < page_height){
        auto oldY = currentOffset.y();
        auto newY = std::min(page_height-viewport()->height()
                               ,oldY+viewport()->height());
        if(oldY != newY){
            verticalScrollBar()->setValue(newY);
            return;
        }
    }

    auto newPage = std::min(currentPage+1, layout->pages()-1);
    if(newPage != currentPage){
        setNewPage(newPage);
    }
}

void PageView::toHome(){
    if(layout.Get() == nullptr)
        return;

    if(currentPage != 0){
        setNewPage(0);
    }
}

void PageView::toEnd(){
    if(layout.Get() == nullptr)
        return;

    if(currentPage != layout->pages()-1){
        setNewPage(layout->pages()-1);
    }
}

void PageView::resizeEvent(QResizeEvent* /*event*/)
{
    tiles.clear();
    updateScrollBars();
    updateViewport();
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
    if(clearPage || tiles.empty()){
        QPainter    painter(viewport());
        painter.fillRect(event->rect(), Qt::gray);
        if(!clearPage)
            return;
        clearPage = false;
    }

    if(tiles.empty())
        return;

    auto tile =tiles.front();
    QImage img((uchar*)tile->data(), tile->rect()->width(), tile->rect()->height(), QImage::Format_RGB32);
    QPainter  painter(viewport());
    auto dx = std::max(0, (viewport()->width()-tile->rect()->width())/2);
    auto dy = std::max(0, (viewport()->height()-tile->rect()->height())/2);
    auto dstRect = event->rect();
    dstRect.moveTo(dx, dy);
    auto srcRect = event->rect();
    srcRect.moveTo(currentOffset);
    painter.drawImage(dstRect, img, srcRect);
}

void PageView::onScrollBarValueChanged(int /*value*/)
{
    QPoint offset(horizontalScrollBar()->value(),
                           verticalScrollBar()->value());
    if(currentOffset != offset){
        currentOffset = offset;
        viewport()->update();
    }
}

void PageView::updateViewport()
{
    if(layout.Get() == nullptr)
        return;

    auto sz = layout->pageSize(currentPage);
    auto lrect = layout->createRect(currentPage,
                                     0, 0,
                                     sz.first, sz.second);
    lrect->AddRef();
    auto tile = renderer->renderRect(lrect);
    lrect->Release();
    tiles.push_back(tile);
}

void PageView::updateScrollBars()
{
    if(layout.Get() == nullptr)
        return;

    auto sz = layout->pageSize(currentPage);
    auto zoomFactor = layout->pageZoom(currentPage);
    QSize size(sz.first*zoomFactor, sz.second*zoomFactor);
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

void PageView::onPageCountChanged(int /*count*/){
    //ignore
}

void PageView::onPageSizeChanged(int page, int /*width*/, int /*height*/)
{
    if(currentPage == page){
        updateScrollBars();
        updateViewport();
    }
}

void PageView::setNewPage(int num){
    tiles.clear();

    currentPage = num;
    currentOffset.setY(0);

    auto size = layout->pageSize(currentPage);
    float zoomFactor = 1.0;

    switch (fitMode) {
    case FIT_WIDTH:
        zoomFactor = (float)viewport()->width()/size.first;
        break;
    case FIT_HEIGHT:
        zoomFactor = (float)viewport()->height()/size.second;
        break;
    case FIT_PAGE:
        zoomFactor = std::min((float)viewport()->width()/size.first
                 ,(float)viewport()->height()/size.second);
        break;
    case FIT_MANUAL:
        //nothing to do
        break;
    default:
        break;
    }

    layout->setPageZoom(currentPage, zoomFactor);

    updateScrollBars();
    clearPage = true;
    updateViewport();
    viewport()->update();

    emit pageChanged(currentPage);
}
