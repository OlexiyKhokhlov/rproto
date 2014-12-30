#include <imagetile.h>

ImageTile::ImageTile(RProto::ILayout *lay, int page, double zoom, int x, int y, int width, int height, ImageFormat format)
    :imgRect(lay, page, zoom, x, y, width, height, (COM::BaseComponent*)this)
{
    pdf_bitmap = FPDFBitmap_CreateEx(width, height, format, nullptr, 0);
    FPDFBitmap_FillRect(pdf_bitmap, 0, 0, width, height, -1);
}

ImageTile::~ImageTile()
{
    FPDFBitmap_Destroy(pdf_bitmap);
}

// IImageTile interface
const char* ImageTile::data()const{
    return (const char*)FPDFBitmap_GetBuffer(pdf_bitmap);
}

const RProto::IRect* ImageTile::rect()const{
    return imgRect;
}
