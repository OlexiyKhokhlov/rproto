#include "pageview.h"
#include "draghelper.h"

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

PageView::PageView(QWidget *parent)
    : QAbstractScrollArea(parent)
{
    viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
    viewport()->setAttribute(Qt::WA_NoSystemBackground);
    viewport()->setMouseTracking(true);

    verticalScrollBar()->setSingleStep(10);
    horizontalScrollBar()->setSingleStep(10);

    dragHelper = new DragHelper(this, this);

    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));
    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));
}

PageView::~PageView() {
}

void PageView::setBook(RProto::IBookPtrT  bk)
{
    book = bk;
    if(book == nullptr) {
        layout = nullptr;
        renderer = nullptr;
        tiles.clear();
        return;
    }

    auto dpiX = QApplication::desktop()->physicalDpiX();
    auto dpiY = QApplication::desktop()->physicalDpiY();

    layout = book->createLayout(dpiX, dpiY);
    renderer = book->createRenderer();

    layout->addListener(this);

    layout->startLayouting();
    currentOffset = QPoint(0,0);
    setNewPage(0);
}

void PageView::setNavigationMode(NavigationMode mode){
    navigation_mode = mode;
    if(navigation_mode == NavigationMode::NAVIGATION_DRAG){
        dragHelper->setEnabled(true);
        viewport()->setCursor(Qt::OpenHandCursor);
    }else{
        dragHelper->setEnabled(false);
        viewport()->setCursor(Qt::ArrowCursor);
    }
}

void PageView::setPage(int pg){
    if(layout == nullptr)
        return;

    auto page = std::max(0, pg-1);
    page = std::min(page, layout->pages()-1);
    if(currentPage != page){
        currentPage = page;
        currentOffset = QPoint(0,0);
        setNewPage(currentPage);
        emit pageChanged(currentPage+1);
    }
}

int PageView::getMaxPage() {
    return layout == nullptr? 1 : layout->pages();
}

float PageView::zoom()const{
    if(layout == nullptr)
        return 1.0;
    return layout->pageZoom(currentPage);
}

void PageView::setZoom(float zm){
    if(layout == nullptr)
        return;

    layout->setPageZoom(zm);

    updateScrollBars();
    updateViewport();
}

void PageView::setPageFitMode(PageFit fit){
    fitMode = fit;
    updateBySize(viewport()->size());
}

void PageView::pageUp()
{
    if(layout == nullptr)
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

void PageView::pageDown() {
    if(layout == nullptr)
        return;

    int page_height = layout->pageSize(currentPage).second * layout->pageZoom(currentPage);
    int wp_height = viewport()->height();
    if(wp_height < page_height){
        auto oldY = currentOffset.y();
        auto newY = std::min(page_height-viewport()->height(),
                             oldY+viewport()->height());
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
    if(layout == nullptr)
        return;

    if(currentPage != 0){
        setNewPage(0);
    }
}

void PageView::toEnd(){
    if(layout == nullptr)
        return;

    if(currentPage != layout->pages()-1){
        setNewPage(layout->pages()-1);
    }
}

void PageView::resizeEvent(QResizeEvent* event)
{
    updateBySize(event->size());
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
        painter.fillRect(event->rect(), background_color);
        if(!clearPage)
            return;
        clearPage = false;
    }

    if(tiles.empty())
        return;

    auto tile = tiles.front();
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
    if(layout == nullptr)
        return;

    auto sz = layout->pageSize(currentPage);
    auto lrect = layout->createRect(currentPage,
                                     0, 0,
                                     sz.first, sz.second);
    auto tile = renderer->renderRect(lrect);
    tiles.push_back(tile);
}

void PageView::updateScrollBars()
{
    if(layout == nullptr)
        return;

    //auto pages = layout->pages();

    auto sz = layout->pageSize(currentPage);
    auto zoomFactor = layout->pageZoom(currentPage);
    QSize size(sz.first*zoomFactor, sz.second*zoomFactor);
    verticalScrollBar()->setPageStep(viewport()->height());
    horizontalScrollBar()->setPageStep(viewport()->width());

    verticalScrollBar()->setValue(currentOffset.y());
    verticalScrollBar()->setRange(0, size.height() - viewport()->height());
    if(size.height() <= viewport()->height())
        verticalScrollBar()->setVisible(false);
    else
        verticalScrollBar()->setVisible(true);

    horizontalScrollBar()->setValue(currentOffset.x());
    horizontalScrollBar()->setRange(0, size.width() - viewport()->width());
    if(size.width() <= viewport()->width())
        horizontalScrollBar()->setVisible(false);
    else
        horizontalScrollBar()->setVisible(true);
}

void PageView::updateBySize(const QSize& size) {
    if(layout == nullptr)
        return;

    tiles.clear();
    auto zoom = getPageZoom(currentPage, size);
    layout->setPageZoom(currentPage, zoom);

    updateScrollBars();
    clearPage = true;
    updateViewport();
}

void PageView::onPageCountChanged(int count) {
    qDebug() << __FUNCTION__ << "count = " << count;
    updateScrollBars();
    updateViewport();
}

void PageView::onPageSizeChanged(int /*page*/, int width, int height) {
    qDebug() << __FUNCTION__ << "width = " << width << "height = " << height;
//    if(currentPage == page){
//        updateScrollBars();
//        updateViewport();
//    }
    updateScrollBars();
    updateViewport();
}

void PageView::setNewPage(int num){
    tiles.clear();

    currentPage = num;
    currentOffset.setY(0);

    layout->setPageZoom(currentPage, getPageZoom(currentPage, viewport()->size()));

    updateScrollBars();
    clearPage = true;
    updateViewport();
    viewport()->update();

    emit pageChanged(currentPage+1);
}

float PageView::getPageZoom(int page, const QSize& viewport_size) {
    auto size = layout->pageSize(page);
    float zoomFactor = 1.0;

    switch (fitMode) {
    case PageFit::FIT_WIDTH:
        zoomFactor = (float)viewport_size.width()/size.first;
        break;
    case PageFit::FIT_HEIGHT:
        zoomFactor = (float)viewport_size.height()/size.second;
        break;
    case PageFit::FIT_PAGE:
        zoomFactor = std::min((float)viewport_size.width()/size.first
                 ,(float)viewport_size.height()/size.second);
        break;
    case PageFit::FIT_MANUAL:
        //nothing to do
        break;
    default:
        break;
    }
    return zoomFactor;
}
