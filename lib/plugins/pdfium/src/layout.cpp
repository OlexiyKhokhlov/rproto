#include <layout.h>
#include <book.h>
#include <point.h>
#include <rect.h>

#include <fpdfview.h>
#include <fpdf_doc.h>

#include <assert.h>

Layout::Layout(std::shared_ptr<Book> b, double dpix, double dpiy)
    : bookOwner(b)
    , dpiX(dpix)
    , dpiY(dpiy)
    , listenerPtr(nullptr)
{
    assert(bookOwner != nullptr);
}

//ILayout interface
void Layout::addListener(RProto::ILayoutListener* listener){
    listenerPtr = listener;
}

RProto::IBookPtrT Layout::book(){
    return bookOwner;
}

void Layout::startLayouting() {
    int page_count = 0;
    {
        std::scoped_lock<Library>  lock(Singletone<Library>::instance());
        page_count = FPDF_GetPageCount(bookOwner->document());
    }
    page_vector.resize(page_count, {1.0, {}});
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
    {
        std::scoped_lock<Library>  lock(Singletone<Library>::instance());
        FPDF_GetPageSizeByIndex(bookOwner->document(), rpage, &width, &height);
    }

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

RProto::IPointPtrT Layout::createPoint(int rpage, int x, int y)
{
    if((std::size_t)rpage >= page_vector.size())
        return nullptr;

    auto zoom = page_vector[rpage].zoom;
    return std::make_shared<Point>(shared_from_this(), rpage, zoom, x, y);
}

RProto::IRectPtrT Layout::createRect(int rpage, int x, int y, int width, int height)
{
    if((std::size_t)rpage >= page_vector.size())
        return nullptr;

    auto zoom = page_vector[rpage].zoom;
    return std::make_shared<Rect>(shared_from_this(), rpage, zoom, x, y, width, height);
}

IInternalLayout::PageDescriptor& Layout::getPageDescr(int rpage){
    return page_vector[rpage];
}

void Layout::readPageLinks(int page) {
    auto pdf_page = bookOwner->getPage(page);
    {
        std::scoped_lock<Library>  lock(Singletone<Library>::instance());

        IInternalLayout::Link link;
        FPDF_BOOL hasXCoord = 0;
        FPDF_BOOL hasYCoord = 0;
        FPDF_BOOL hasZoom   = 0;

        FPDF_LINK linkAnnot;
        int link_pos = 0;
        while (FPDFLink_Enumerate(pdf_page->pdf_page, &link_pos, &linkAnnot)) {
            FPDF_DEST dest = nullptr;
            if (FPDFLink_GetAnnotRect(linkAnnot, &link.rect)) {
                dest = FPDFLink_GetDest(bookOwner->document(), linkAnnot);
                link.page = FPDFDest_GetPageIndex(bookOwner->document(), dest);
                if (FPDFDest_GetLocationInPage(dest, &hasXCoord, &hasYCoord, &hasZoom,
                                               &link.x, &link.y, &link.zoom)) {
                            page_vector[page].links.push_back(link);
                }
            }
        }
    }
}
//        auto pdf_text = FPDFText_LoadPage(pdf_page);
//        auto pdf_link_page = FPDFLink_LoadWebLinks(pdf_text);
//        auto links_count = FPDFLink_CountWebLinks(pdf_link_page);
//        for(int l=0; l < links_count; ++l) {
//            unsigned short buf[1000];
//            FPDFLink_GetURL(pdf_link_page, l, buf, 1000);
//        }
//        FPDFLink_CloseWebLinks(pdf_link_page);
//        FPDFText_ClosePage(pdf_text);
