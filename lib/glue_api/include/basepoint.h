#pragma once

#include <ipoint.h>
#include <core/co_class.h>

namespace RProto {

class BasePoint : public Boss::SimpleCoClass<RProto::IPoint>
{
public:
    BasePoint(ILayout *lay, int page, double zoom, int x, int y);
    virtual ~BasePoint();

private:
    //Interface IPoint
    virtual ILayout* layout()const override;
    virtual int page()const override;
    virtual double zoom()const override;
    virtual int x()const override;
    virtual int y()const override;

private:
    ILayout *mLayout;
    int mPage;
    double mZoom;
    int mX;
    int mY;
};
} //namespace RProto
