#include <layout.h>
#include <book.h>
#include <point.h>
#include <rect.h>
#include <assert.h>

#include <fpdfview.h>

#include <QDebug>

Layout::Layout(Book *b, double dpix, double dpiy)
    :bookOwner(b)
    ,dpiX(dpix)
    ,dpiY(dpiy)
    ,stopLayouting(false)
{
    assert(bookOwner != nullptr);
}

Layout::~Layout()
{
    qDebug() << __FUNCTION__;

    stopLayouting = true;
    //thread.join();
    for(auto pg : page_vector){
        if(pg.isValid)
            FPDF_ClosePage(pg.pdf_page);
    }
}

//Iunknown interface
COM::HResult Layout::QueryInterface(const std::string& id, void** ppv)
{
    //IInternalLayout
    if(id == IInternalLayout::iid){
        *ppv = (IInternalLayout*)this;
        return COM::HResult();
    }

    if(id == RProto::ILayout::iid){
        *ppv = (RProto::ILayout*)this;
        return COM::HResult();
    }

    return COM::BaseComponent::QueryInterface(id, ppv);
}

//ILayout interface
RProto::IBook* Layout::book(){
    return (RProto::IBook*)bookOwner;
}

void Layout::startLayouting(){
    stopLayouting = false;
    auto page_count = FPDF_GetPageCount(bookOwner->document());
    page_vector.reserve(page_count);

    for(int i=0; i<page_count; ++i){
        IInternalLayout::PageDescriptor pg={false, 0, 1};
        page_vector.push_back(pg);
    }

    emit pageCountChanged(page_count);

    //thread = std::thread(&Layout::createPages, this);
    //thread.join();
}

void Layout::cancelLayouting(){
    stopLayouting = true;
}

int Layout::pages()const
{
    return page_vector.size();
}

QSize Layout::pageSize(int rpage)const
{
    if((std::size_t)rpage >= page_vector.size())
        return QSize();

//    double width  = FPDF_GetPageWidth(page_vector[rpage].pdf_page);
//    double height = FPDF_GetPageHeight(page_vector[rpage].pdf_page);

    double width=0;
    double height=0;
    FPDF_GetPageSizeByIndex(bookOwner->document(), rpage, &width, &height);

    width = width/72*dpiX;
    height = height/72*dpiY;

    width *= page_vector[rpage].zoom;
    height *= page_vector[rpage].zoom;

    return QSize((int)width, (int)height);
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
    return new Point((RProto::ILayout*)this, rpage, zoom, x, y);
}

RProto::IRect* Layout::createRect(int rpage, int x, int y, int width, int height)const
{
    if((std::size_t)rpage >= page_vector.size())
        return nullptr;

    auto zoom = page_vector[rpage].zoom;
    return new Rect((RProto::ILayout*)this, rpage, zoom, x, y, width, height);
}

QObject* Layout::qobject()
{
    return (QObject*)this;
}

IInternalLayout::PageDescriptor& Layout::getPageDescr(int rpage){
    return page_vector[rpage];
}

void Layout::createPages(){
    size_t i=0;
    for(IInternalLayout::PageDescriptor& pd : page_vector){
        if(stopLayouting)
            break;
        pd.pdf_page = FPDF_LoadPage(bookOwner->document(), i);
        pd.isValid = true;
        emit pageSizeChanged(i, pageSize(i));
        ++i;
    }
}
