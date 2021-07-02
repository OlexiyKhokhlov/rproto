#include "layout.h"
#include <imagetile.h>
#include <rect.h>

ImageTile::ImageTile(RProto::ILayoutPtrT lay, int page, double zoom, int x, int y, int width, int height, ImageFormat format)
    :imgRect(nullptr)
{
    imgRect = std::make_shared<Rect>(lay, page, zoom, x, y, width, height);
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

const RProto::IRectPtrT ImageTile::rect()const{
    return imgRect;
}
