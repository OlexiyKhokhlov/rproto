#pragma once

#include <com/basecomponent.h>
#include <baserect.h>
#include <iimagetile.h>
#include <fpdfview.h>

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
class ImageTile : public COM::BaseComponent, public RProto::IImageTile
{
public:
    enum ImageFormat{
        FORMAT_MONO = 1,
        FORMAT_RGB888 = 2,
        FORMAT_RGB32 = 3,
        FORMAT_ARGB32 = 4,
    };

    ImageTile(RProto::ILayout *lay, int page, double zoom, int x, int y, int width, int height, ImageFormat format = FORMAT_RGB32);
    virtual ~ImageTile();

    // IUnknown interface
    virtual int addRef() override{
        return COM::BaseComponent::addRef();
    }
    virtual int release() override{
        return COM::BaseComponent::release();
    }
    virtual COM::HResult QueryInterface(const std::string &, void **ppv) override;

    // IImageTile interface
    virtual const char* data()const override;

    FPDF_BITMAP pdfBitmap(){
        return pdf_bitmap;
    }

private:
    FPDF_BITMAP     pdf_bitmap;
    RProto::BaseRect rect;
};

