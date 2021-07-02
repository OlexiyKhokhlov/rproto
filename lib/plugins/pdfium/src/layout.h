#pragma once

#include <ibook.h>
#include <ilayout.h>
#include <iinternallayout.h>
#include <fpdfview.h>
#include <vector>

class Book;

class Layout : public RProto::ILayout, IInternalLayout, public std::enable_shared_from_this<Layout>
{
public:
    explicit Layout(std::shared_ptr<Book> book, double dpix, double dpiy);
    virtual ~Layout();

    //ILayout interface
    virtual void addListener(RProto::ILayoutListener* listener) override;
    virtual RProto::IBookPtrT book() override;
    virtual void startLayouting() override;
    virtual void cancelLayouting() override;
    virtual int pages()const override;
    virtual std::pair<int,int> pageSize(int rpage=0)const override;
    virtual double pageZoom(int rpage=0)const override;
    virtual void setPageZoom(int rpage=0, double zoom=1) override;
    virtual void setDocumentZoom(double zoom=1) override;
    virtual RProto::IPointPtrT createPoint(int rpage, int x, int y) override;
    //TODO create a point by link
    //virtual IPoint* createPoint(ILink *link)const override;
    virtual RProto::IRectPtrT createRect(int rpage, int x, int y, int width, int height) override;

    //IInternalLayout interface
    virtual IInternalLayout::PageDescriptor& getPageDescr(int rpage=0) override;

private:
    std::shared_ptr<Book> bookOwner;
    double dpiX, dpiY;
    std::vector<IInternalLayout::PageDescriptor> page_vector;
    RProto::ILayoutListener* listenerPtr = nullptr;
};
