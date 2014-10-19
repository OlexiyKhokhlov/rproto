#include <layout.h>
#include <book.h>
#include <point.h>
#include <rect.h>
#include <assert.h>

#include <fpdfview.h>

#include <QGuiApplication>
#include <QScreen>

Layout::Layout(Book *book)
{
    assert(book != nullptr);

    auto screens = QGuiApplication::screens();
    assert(screens.size() != 0);

    auto fisrt_screen = screens.first();
    dpiX = fisrt_screen->physicalDotsPerInchX();
    dpiY = fisrt_screen->physicalDotsPerInchY();

    auto page_count = FPDF_GetPageCount(book->document());
    page_vector.reserve(page_count);
    for(int i=0; i<page_count; ++i){
        Page pg={FPDF_LoadPage(book->document(),i),1};
        page_vector.push_back(pg);
    }
}

Layout::~Layout()
{
    for(auto pg : page_vector){
        FPDF_ClosePage(pg.pdf_page);
    }
}

//Iunknown interface
COM::HResult Layout::QueryInterface(const std::string& id, void** ppv)
{
    if(id == RProto::ILayout::iid){
        *ppv = (RProto::ILayout*)this;
        return COM::HResult();
    }

    return COM::BaseComponent::QueryInterface(id, ppv);
}

//ILayout interface
int Layout::pages()const
{
    return page_vector.size();
}

QSize Layout::pageSize(int rpage)const
{
    double width, height;
    auto err = FPDF_GetPageSizeByIndex(book->document(), rpage, &width, &height);
    if(err == 0)
        return QSize();

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
    for(auto pg : page_vector){
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
    return nullptr;
}
