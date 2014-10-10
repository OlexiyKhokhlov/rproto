#include <djvupagelayout.h>
#include "djvubook.h"

using namespace RProto;

DjVuPageLayout::DjVuPageLayout(DjVuBook *book, ddjvu_document_t* document, QObject *parent)
    :QObject(parent)
    ,owner(book)
    ,djvu_document(document)
{
    owner->addRef();
}

DjVuPageLayout::~DjVuPageLayout()
{
    owner->layoutRemoved(this);
    owner->release();
}

//IUnknown
size_t DjVuPageLayout::addRef()
{
    return internalAddRef();
}

size_t DjVuPageLayout::release()
{
    return internalRelease();
}

HResult DjVuPageLayout::queryInterface(const QUuid& iid, void** interface)
{
    return HResult(true, 0);
}

QObject* DjVuPageLayout::qobject()
{
    return (QObject*)this;
}

void DjVuPageLayout::layoutChangedInternal(int page, QSize size)
{
    emit layoutChanged(page, size);
}

//ILayout interface
void DjVuPageLayout::setViewportSize(const QSize& /*sz*/)
{
  
}

int DjVuPageLayout::pages()const
{
  return ddjvu_document_get_pagenum(djvu_document);
}

QSize DjVuPageLayout::pageSize(int rpage)
{
  ddjvu_page_t* djvu_page = NULL;
  djvu_page = ddjvu_page_create_by_pageno(djvu_document, rpage);
  if(djvu_page == NULL) return QSize();
  
  int page_width  = ddjvu_page_get_width(djvu_page);
  int page_height = ddjvu_page_get_height(djvu_page);
  
  return QSize(page_width, page_height);
}
