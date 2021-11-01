#pragma once

#include <QPoint>
#include <QAbstractScrollArea>
#include <QAbstractItemDelegate>

#include <forward.h>
#include <ibook.h>
#include <ilayout.h>
#include <irenderer.h>

class DragHelper;

class PageView : public QAbstractScrollArea, private RProto::ILayoutListener
{
    Q_OBJECT

    //Q_PROPERTY(bool showCursor READ iSShowCursor WRITE setShowCursor)
    Q_PROPERTY(NavigationMode navigationMode READ navigationMode WRITE setNavigationMode)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(float zoom READ zoom WRITE setZoom NOTIFY zoomChanged)
    Q_PROPERTY(PageFit pageFitMode READ pageFitMode WRITE setPageFitMode)

public:

    enum class NavigationMode{
        NAVIGATION_POINTER,
        NAVIGATION_DRAG
    };
    Q_ENUM(NavigationMode)

    enum class PageFit {
        FIT_WIDTH,
        FIT_HEIGHT,
        FIT_PAGE,
        FIT_MANUAL
    };
    Q_ENUM(PageFit)

    explicit PageView(QWidget *parent = 0);
    virtual ~PageView();

    void setBook(RProto::IBookPtrT book);

    void setNavigationMode(NavigationMode);
    NavigationMode navigationMode()const{
        return navigation_mode;
    }

    int page()const{
        return currentPage;
    }

    int getMaxPage();

    float zoom()const;
    PageFit pageFitMode()const{
        return fitMode;
    }
    void setPageFitMode(PageFit fit);

signals:
    void pageChanged(int new_page);
    void zoomChanged(float new_zoom);

public slots:
    void pageUp();
    void pageDown();
    void toHome();
    void toEnd();
    void setPage(int pg);
    void setZoom(float zm);

protected:
   virtual void resizeEvent(QResizeEvent* event);
   virtual bool viewportEvent(QEvent* event);
   virtual void viewportPaintEvent(QPaintEvent* event);

private slots:
   void onScrollBarValueChanged(int value);

private:
   void updateViewport();
   void updateScrollBars();
   void updateBySize(const QSize& size);

    RProto::IBookPtrT               book     = nullptr;
    RProto::ILayoutPtrT             layout   = nullptr;
    RProto::IRendererPtrT           renderer = nullptr;
    QList<RProto::ImageTilePtrT>    tiles;

    QColor         background_color = Qt::gray;
    int            page_gap         = 10;
    NavigationMode navigation_mode  = NavigationMode::NAVIGATION_POINTER;
    PageFit        fitMode          = PageFit::FIT_WIDTH;
    int            currentPage      = 0;
    QPoint         currentOffset;

    bool           clearPage        = false;
    DragHelper*    dragHelper       = nullptr;

    void setNewPage(int num);
    float getPageZoom(int page, const QSize& viewport_size);

    //Interface RProto::ILayoutListener
    virtual void onPageCountChanged(int count) final;
    virtual void onPageSizeChanged(int page, int width, int height) final;
};
