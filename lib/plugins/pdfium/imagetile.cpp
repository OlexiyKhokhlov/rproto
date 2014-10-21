#include <imagetile.h>

ImageTile::ImageTile(RProto::ILayout *lay, int page, double zoom, int x, int y, int width, int height, ImageFormat format)
    :rect(lay, page, zoom, x, y, width, height, (COM::BaseComponent*)this)
{
    pdf_bitmap = FPDFBitmap_CreateEx(width, height, format, nullptr, 0);
}

ImageTile::~ImageTile()
{
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
