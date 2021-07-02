#pragma once

#include <irect.h>

namespace RProto {

class BaseRect : public IRect
{
public:
    BaseRect(ILayoutPtrT lay, int page, double zoom, int x, int y, int width, int height);
    virtual ~BaseRect();

    //interface IRect
    virtual ILayoutPtrT layout()const override;
    virtual int page()const override;
    virtual double zoom()const override;
    virtual int x()const override;
    virtual int y()const override;
    virtual int width()const override;
    virtual int height()const override;

private:
    ILayoutPtrT mLayout;
    int mPage;
    double mZoom;
    int mX;
    int mY;
    int mWidth;
    int mHeight;
};
}//namespace RProto
