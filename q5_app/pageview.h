#pragma once

#include <QPoint>
#include <QAbstractScrollArea>

#include <ibook.h>
#include <ilayout.h>
#include <irenderer.h>

class DragHelper;

class PageView : public QAbstractScrollArea, private RProto::ILayoutListener
{
    Q_OBJECT

    Q_ENUMS(NavigationMode)
    Q_ENUMS(PageFit)

    //Q_PROPERTY(bool showCursor READ iSShowCursor WRITE setShowCursor)
    Q_PROPERTY(NavigationMode navigationMode READ navigationMode WRITE setNavigationMode)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(float zoom READ zoom WRITE setZoom NOTIFY zoomChanged)
    Q_PROPERTY(PageFit pageFitMode READ pageFitMode WRITE setPageFitMode)

public:

    enum NavigationMode{
        NAVIGATION_POINTER,
        NAVIGATION_DRAG
    };

    enum PageFit {
        FIT_WIDTH,
        FIT_HEIGHT,
        FIT_PAGE,
        FIT_MANUAL
    };

    explicit PageView(QWidget *parent = 0);
    virtual ~PageView();

    void setBook(RProto::IBook*  book);

    void setNavigationMode(NavigationMode);
    NavigationMode navigationMode()const{
        return navigation_mode;
    }

    int page()const{
        return currentPage;
    }
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

    IBookPtr   book;
    ILayoutPtr layout;
    IRendererPtr renderer;
    QList<ImageTilePtr>    tiles;
    QColor     background_color;

    NavigationMode navigation_mode;
    PageFit  fitMode;
    int      currentPage;
    QPoint   currentOffset;

    bool     clearPage;
    DragHelper *dragHelper;

    void setNewPage(int num);

    //Interface RProto::ILayoutListener
    virtual void onPageCountChanged(int count) override;
    virtual void onPageSizeChanged(int page, int width, int height) override;
};
