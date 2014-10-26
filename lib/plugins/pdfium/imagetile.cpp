#include <imagetile.h>
#include <QDebug>

ImageTile::ImageTile(RProto::ILayout *lay, int page, double zoom, int x, int y, int width, int height, ImageFormat format)
    :rect(lay, page, zoom, x, y, width, height, (COM::BaseComponent*)this)
{
    qDebug() << __FUNCTION__ << width << height;
    pdf_bitmap = FPDFBitmap_CreateEx(width, height, format, nullptr, 0);
    //pdf_bitmap = FPDFBitmap_Create(width, height, 0);
    FPDFBitmap_FillRect(pdf_bitmap, x, y, width, height, -1);
}

ImageTile::~ImageTile()
{
    qDebug() << __FUNCTION__;

    FPDFBitmap_Destroy(pdf_bitmap);
}

COM::HResult ImageTile::QueryInterface(const std::string &id, void **ppv)
{
    if(id == RProto::IImageTile::iid){
        *ppv = (RProto::IImageTile*)this;
        return COM::HResult();
    }

    if(id == RProto::IRect::iid){
        *ppv = (RProto::IRect*)&rect;
        return COM::HResult();
    }

    return COM::BaseComponent::QueryInterface(id, ppv);
}

// IImageTile interface
const char* ImageTile::data()const{
    return (const char*)FPDFBitmap_GetBuffer(pdf_bitmap);
}
