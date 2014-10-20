#include "imagetile.h"

ImageTile::ImageTile(RProto::ILayout *lay, int page, double zoom, int x, int y, int width, int height)
    :rect(lay, page, zoom, x, y, width, height)
{
    //pdf_bitmap = FPDFBitmap_CreateEx();
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
        *ppv = (RProto::IRect*)this;
        return COM::HResult();
    }

    return COM::BaseComponent::QueryInterface(id, ppv);
}
