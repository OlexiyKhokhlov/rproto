#include <djvurenderer.h>
#include <ibook.h>
#include <QSize>

using namespace RProto;

DjVuRenderer::DjVuRenderer(IBook* book, ddjvu_document_t* document)
    :owner(book)
    ,djvu_document(document)
    ,djvu_format(NULL)
{
    owner->addRef();
    static unsigned int RGB32_MASKS[4] = { 0x0000FF, 0x00FF00, 0xFF0000, 0xFF000000};
    djvu_format = ddjvu_format_create(DDJVU_FORMAT_RGBMASK32, 4, RGB32_MASKS);
    ddjvu_format_set_row_order(djvu_format, 1);
    ddjvu_format_set_y_direction(djvu_format, 1);
}

DjVuRenderer::~DjVuRenderer()
{
  if(djvu_format!=NULL)
    ddjvu_format_release(djvu_format);
  owner->release();
}

//IUnknown
size_t DjVuRenderer::addRef()
{
    return internalAddRef();
}

size_t DjVuRenderer::release()
{
    return internalRelease();
}

HResult DjVuRenderer::queryInterface(const QUuid& iid, void** interface)
{
    return HResult(true, 0);
}

//IRenderer interface
QImage DjVuRenderer::renderRect(int rpage, QRect rect, float scale)
{
  ddjvu_page_t* djvu_page = NULL;
  djvu_page = ddjvu_page_create_by_pageno(djvu_document, /*rpage*/10);
  if(djvu_page == NULL) return QImage();

  ddjvu_rect_t djvu_rect = {0,0, ddjvu_page_get_width(djvu_page)/3, ddjvu_page_get_height(djvu_page)/3};
  ddjvu_rect_t djvu_rect_img = {0,0, ddjvu_page_get_width(djvu_page)/3, ddjvu_page_get_height(djvu_page)/3};
  QImage image(QSize(ddjvu_page_get_width(djvu_page)/3, ddjvu_page_get_height(djvu_page)/3), QImage::Format_RGB32);
  int ok = 0;
  ok = ddjvu_page_render(djvu_page,
             DDJVU_RENDER_COLOR,
             &djvu_rect,
             &djvu_rect_img,
             djvu_format,
             image.bytesPerLine(),
             (char*)image.bits() );
  
  return image;
}

void DjVuRenderer::redisplay(const ddjvu_message_redisplay_s *)
{

}
