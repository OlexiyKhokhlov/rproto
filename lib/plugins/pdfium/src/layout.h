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
    virtual ~Layout() = default;

    //ILayout interface
    void addListener(RProto::ILayoutListener* listener) override;
    RProto::IBookPtrT book() override;
    void startLayouting() override;
    void cancelLayouting() override;
    int pages()const override;
    std::pair<int,int> pageSize(int rpage=0)const override;
    double pageZoom(int rpage=0)const override;
    void setPageZoom(int rpage=0, double zoom=1) override;
    void setDocumentZoom(double zoom=1) override;
    RProto::IPointPtrT createPoint(int rpage, int x, int y) override;
    //TODO create a point by link
    //virtual IPoint* createPoint(ILink *link)const override;
    RProto::IRectPtrT createRect(int rpage, int x, int y, int width, int height) override;

    //IInternalLayout interface
    IInternalLayout::PageDescriptor& getPageDescr(int rpage=0) override;

private:
    std::shared_ptr<Book> bookOwner;
    double dpiX, dpiY;
    std::vector<IInternalLayout::PageDescriptor> page_vector;
    RProto::ILayoutListener* listenerPtr = nullptr;

    void readPageLinks(int page);
};
