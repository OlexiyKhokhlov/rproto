#include <basepoint.h>
#include <forward.h>
#include <assert.h>

using namespace RProto;

BasePoint::BasePoint(ILayoutPtrT lay, int page, double zoom, int x, int y)
    :mLayout(lay)
    ,mPage(page)
    ,mZoom(zoom)
    ,mX(x)
    ,mY(y)
{
    assert(mLayout != nullptr);
}

BasePoint::~BasePoint()
{
}

//Interface IPoint
RProto::ILayoutPtrT BasePoint::layout()const
{
    return mLayout;
}

int BasePoint::page()const
{
    return mPage;
}

double BasePoint::zoom()const
{
    return mZoom;
}

int BasePoint::x()const
{
    return mX;
}

int BasePoint::y()const
{
    return mY;
}
