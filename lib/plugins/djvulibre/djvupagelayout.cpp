#include <djvupagelayout.h>
#include "djvubook.h"

DjVuPageLayout::DjVuPageLayout(DjVuBook *book, ddjvu_document_t* document)
    :owner(book)
    ,djvu_document(document)
{
    owner->addRef();
}

DjVuPageLayout::~DjVuPageLayout()
{
    //owner->layoutRemoved(this);
    owner->release();
}

//Iunknown interface
COM::HResult DjVuPageLayout::QueryInterface(const std::string& id, void** ppv)
{
    if(id == RProto::ILayout::iid){
        *ppv = (RProto::ILayout*)this;
        return COM::HResult();
    }

    return COM::BaseComponent::QueryInterface(id, ppv);
}

//void DjVuPageLayout::layoutChangedInternal(int page, QSize size)
//{
//    emit layoutChanged(page, size);
//}

//ILayout interface
void DjVuPageLayout::addListener(RProto::ILayoutListener *listener){
    listenerPtr = listener;
}

RProto::IBook* DjVuPageLayout::book(){
    return (RProto::IBook*)owner;
}

void DjVuPageLayout::startLayouting(){
}

void DjVuPageLayout::cancelLayouting(){

}

int DjVuPageLayout::pages()const
{
    //return page_vector.size();
    return 0;
}

std::pair<int,int> DjVuPageLayout::pageSize(int rpage)const
{
    ddjvu_page_t* djvu_page = NULL;
    djvu_page = ddjvu_page_create_by_pageno(djvu_document, rpage);
    if(djvu_page == NULL) return std::make_pair(-1,-1);

    auto page_width  = ddjvu_page_get_width(djvu_page);
    auto page_height = ddjvu_page_get_height(djvu_page);

    return std::make_pair(page_width, page_height);
}

double DjVuPageLayout::pageZoom(int rpage)const
{
    return 1;
//    if((std::size_t)rpage >= page_vector.size())
//        return -1;
//    return page_vector[rpage].zoom;
}

void DjVuPageLayout::setPageZoom(int rpage, double zoom)
{
//    if((std::size_t)rpage >= page_vector.size())
//        return;

//    page_vector[rpage].zoom = zoom;
}

void DjVuPageLayout::setDocumentZoom(double zoom)
{
//    for(IInternalLayout::PageDescriptor& pg : page_vector){
//        pg.zoom = zoom;
//    }
}

RProto::IPoint* DjVuPageLayout::createPoint(int rpage, int x, int y)const
{
//    if((std::size_t)rpage >= page_vector.size())
//        return nullptr;

//    auto zoom = page_vector[rpage].zoom;
//    return new Point((RProto::ILayout*)this, rpage, zoom, x, y);
    return nullptr;
}

RProto::IRect* DjVuPageLayout::createRect(int rpage, int x, int y, int width, int height)const
{
//    if((std::size_t)rpage >= page_vector.size())
//        return nullptr;

//    auto zoom = page_vector[rpage].zoom;
//    return new Rect((RProto::ILayout*)this, rpage, zoom, x, y, width, height);
        return nullptr;
}
