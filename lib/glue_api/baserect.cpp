#include <baserect.h>
#include <assert.h>

using namespace RProto;

BaseRect::BaseRect(ILayoutPtrT lay, int page, double zoom, int x, int y, int width, int height)
    : mLayout(lay)
    ,mPage(page)
    ,mZoom(zoom)
    ,mX(x)
    ,mY(y)
    ,mWidth(width)
    ,mHeight(height)
{
    assert(mLayout != nullptr);
}

//interface IRect
ILayoutPtrT BaseRect::layout()const
{
    return mLayout;
}

int BaseRect::page()const
{
    return mPage;
}

double BaseRect::zoom()const
{
    return mZoom;
}

int BaseRect::x()const
{
    return mX;
}

int BaseRect::y()const
{
    return mY;
}

int BaseRect::width()const
{
    return mWidth;
}

int BaseRect::height()const
{
    return mHeight;
}
