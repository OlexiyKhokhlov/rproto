#pragma once

#include "ipoint.h"
#include "forward.h"

namespace RProto {

class BasePoint : public RProto::IPoint
{
public:
    BasePoint(ILayoutPtrT lay, int page, double zoom, int x, int y);
    virtual ~BasePoint();

private:
    //Interface IPoint
    virtual ILayoutPtrT layout()const override;
    virtual int page()const override;
    virtual double zoom()const override;
    virtual int x()const override;
    virtual int y()const override;

private:
    ILayoutPtrT mLayout;
    int mPage;
    double mZoom;
    int mX;
    int mY;
};
} //namespace RProto
