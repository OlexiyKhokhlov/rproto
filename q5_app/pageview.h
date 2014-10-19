#pragma once

#include <QPoint>
#include <QAbstractScrollArea>
//#include <ibook.h>
//#include <ilayout.h>
//#include <irenderer.h>

class QPixmap;

class PageView : public QAbstractScrollArea
{
    Q_OBJECT
public:
    explicit PageView(QWidget *parent = 0);
    virtual ~PageView();

    //void setBook(boost::intrusive_ptr<RProto::IBook>  book);

public slots:
    void pageUp();
    void pageDown();

protected:
   virtual void resizeEvent ( QResizeEvent * event );
   virtual bool viewportEvent ( QEvent * event );
   virtual void viewportPaintEvent ( QPaintEvent * event );

private slots:
   void onScrollBarValueChanged(int value);
   void onLayoutChanged(int page, QSize size);

private:
   void updateViewport();
   void updateScrollBars();

//    boost::intrusive_ptr<RProto::ILayout> layout;
//    boost::intrusive_ptr<RProto::IAsyncRenderer> renderer;
    QPixmap*    screenPixmap;

    int      currentPage;
    QPoint      currentOffset;
};
