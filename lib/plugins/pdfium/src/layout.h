#pragma once

#include <ilayout.h>
#include <iinternallayout.h>
#include <fpdfview.h>
#include <vector>

#include <core/base.h>

class Book;

class Layout : public Boss::CoClass<Boss::MakeId("PDFium.Layout"), RProto::ILayout, IInternalLayout>
{
public:
    explicit Layout(Book *book, double dpix, double dpiy);
    virtual ~Layout();

    //ILayout interface
    virtual void addListener(RProto::ILayoutListener *listener) override;
    virtual RProto::IBook* book() override;
    virtual void startLayouting() override;
    virtual void cancelLayouting() override;
    virtual int pages()const override;
    virtual std::pair<int,int> pageSize(int rpage=0)const override;
    virtual double pageZoom(int rpage=0)const override;
    virtual void setPageZoom(int rpage=0, double zoom=1) override;
    virtual void setDocumentZoom(double zoom=1) override;
    virtual RProto::IPoint* createPoint(int rpage, int x, int y)const override;
    //TODO create a point by link
    //virtual IPoint* createPoint(ILink *link)const override;
    virtual RProto::IRect* createRect(int rpage, int x, int y, int width, int height)const override;

    //IInternalLayout interface
    virtual IInternalLayout::PageDescriptor& getPageDescr(int rpage=0) override;

private:
    Book *bookOwner;
    double dpiX, dpiY;
    std::vector<IInternalLayout::PageDescriptor> page_vector;
    RProto::ILayoutListener *listenerPtr;
};
