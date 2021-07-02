#pragma once

#include <functional>
#include <baserect.h>
#include <iimagetile.h>

#include <fpdfview.h>

class Layout;

/**
1 -  Gray scale bitmap, one byte per pixel
  -  QImage::Format_Mono
2 -  3 bytes per pixel, byte order: blue, green, red
  -  QImage::Format_RGB888
3 -  4 bytes per pixel, byte order: blue, green, red, unused
  -  QImage::Format_RGB32
4 -  4 bytes per pixel, byte order: blue, green, red, alpha
  -  QImage::Format_ARGB32
*/
class ImageTile : public RProto::IImageTile
{
public:
    enum ImageFormat{
        FORMAT_MONO   = 1,
        FORMAT_RGB888 = 2,
        FORMAT_RGB32  = 3,
        FORMAT_ARGB32 = 4
    };

    ImageTile(RProto::ILayoutPtrT lay, int page, double zoom, int x, int y, int width, int height, ImageFormat format = FORMAT_RGB32);
    virtual ~ImageTile();

    // IImageTile interface
    virtual const char* data() const override;
    virtual const RProto::IRectPtrT rect() const override;

    FPDF_BITMAP pdfBitmap(){
        return pdf_bitmap;
    }

private:
    FPDF_BITMAP         pdf_bitmap;
    RProto::IRectPtrT   imgRect;
};

namespace std {
template<>
struct hash<RProto::ImageTilePtrT>{
    typedef RProto::ImageTilePtrT argument_type;
    typedef std::size_t result_type;
    result_type operator()(argument_type const& tile)const{
        return std::hash<int>()(tile->rect()->page());
    }
};
}
