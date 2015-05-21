#pragma once

#include <QPoint>
#include <QAbstractScrollArea>

#include <ibook.h>
#include <ilayout.h>
#include <irenderer.h>

class PageView : public QAbstractScrollArea, private RProto::ILayoutListener
{
    Q_OBJECT

    Q_ENUMS(PageFit)

    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(float zoom READ zoom WRITE setZoom NOTIFY zoomChanged)
    Q_PROPERTY(PageFit pageFitMode READ pageFitMode WRITE setPageFitMode)

public:
    enum PageFit { FIT_WIDTH,
                   FIT_HEIGHT,
                   FIT_PAGE,
                   FIT_MANUAL
                 };

    explicit PageView(QWidget *parent = 0);
    virtual ~PageView();

    void setBook(RProto::IBook*  book);

    int page()const{
        return currentPage;
    }
    void setPage(int pg);
    float zoom()const;
    void setZoom(float zm);
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

protected:
   virtual void resizeEvent ( QResizeEvent * event );
   virtual bool viewportEvent ( QEvent * event );
   virtual void viewportPaintEvent ( QPaintEvent * event );

private slots:
   void onScrollBarValueChanged(int value);

private:
   void updateViewport();
   void updateScrollBars();

    IBookPtr   book;
    ILayoutPtr layout;
    IRendererPtr renderer;
    QList<ImageTilePtr>    tiles;

    PageFit  fitMode;
    int      currentPage;
    QPoint   currentOffset;

    bool     clearPage;

    void setNewPage(int num);

    //Interface RProto::ILayoutListener
    virtual void onPageCountChanged(int count) override;
    virtual void onPageSizeChanged(int page, int width, int height) override;
};
