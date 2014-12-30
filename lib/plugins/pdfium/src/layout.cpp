#include <layout.h>
#include <book.h>
#include <point.h>
#include <rect.h>

#include <core/base.h>

#include <fpdfview.h>

#include <assert.h>

Layout::Layout(Book *b, double dpix, double dpiy)
    :bookOwner(b)
    ,dpiX(dpix)
    ,dpiY(dpiy)
    ,listenerPtr(nullptr)
{
    assert(bookOwner != nullptr);
}

Layout::~Layout()
{
    for(auto pg : page_vector){
        if(pg.isValid)
            FPDF_ClosePage(pg.pdf_page);
    }
}

//ILayout interface
void Layout::addListener(RProto::ILayoutListener *listener){
    listenerPtr = listener;
}

RProto::IBook* Layout::book(){
    return (RProto::IBook*)bookOwner;
}

void Layout::startLayouting(){
    auto page_count = FPDF_GetPageCount(bookOwner->document());
    page_vector.reserve(page_count);

    for(int i=0; i<page_count; ++i){
        IInternalLayout::PageDescriptor pg={false, 0, 1};
        page_vector.push_back(pg);
    }

    //emit pageCountChanged(page_count);
}

void Layout::cancelLayouting(){

}

int Layout::pages()const
{
    return page_vector.size();
}

std::pair<int,int> Layout::pageSize(int rpage)const
{
    if((std::size_t)rpage >= page_vector.size())
        return std::make_pair(-1,-1);

    double width=0;
    double height=0;
    FPDF_GetPageSizeByIndex(bookOwner->document(), rpage, &width, &height);

    width = width/72*dpiX;
    height = height/72*dpiY;

    return std::make_pair((int)width, (int)height);
}

double Layout::pageZoom(int rpage)const
{
    if((std::size_t)rpage >= page_vector.size())
        return -1;
    return page_vector[rpage].zoom;
}

void Layout::setPageZoom(int rpage, double zoom)
{
    if((std::size_t)rpage >= page_vector.size())
        return;

    page_vector[rpage].zoom = zoom;
}

void Layout::setDocumentZoom(double zoom)
{
    for(IInternalLayout::PageDescriptor& pg : page_vector){
        pg.zoom = zoom;
    }
}

RProto::IPoint* Layout::createPoint(int rpage, int x, int y)const
{
    if((std::size_t)rpage >= page_vector.size())
        return nullptr;

    auto zoom = page_vector[rpage].zoom;
    return Boss::Base<Point>::CreatePtr((RProto::ILayout*)this, rpage, zoom, x, y);
}

RProto::IRect* Layout::createRect(int rpage, int x, int y, int width, int height)const
{
    if((std::size_t)rpage >= page_vector.size())
        return nullptr;

    auto zoom = page_vector[rpage].zoom;
    return Boss::Base<Rect>::CreatePtr((RProto::ILayout*)this, rpage, zoom, x, y, width, height);
}

IInternalLayout::PageDescriptor& Layout::getPageDescr(int rpage){
    return page_vector[rpage];
}
