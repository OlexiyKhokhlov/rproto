#include <basepoint.h>
#include <ilayout.h>
#include <assert.h>

using namespace RProto;

BasePoint::BasePoint(ILayout *lay, int page, double zoom, int x, int y)
    :mLayout(lay)
    ,mPage(page)
    ,mZoom(zoom)
    ,mX(x)
    ,mY(y)
{
    assert(mLayout != nullptr);
    mLayout->addRef();
}

BasePoint::~BasePoint()
{
    mLayout->release();
}

COM::HResult BasePoint::QueryInterface(const std::string &iid, void **ppv){
    if(iid == RProto::IPoint::iid){
        *ppv = (RProto::IPoint*)this;
        return COM::HResult();
    }
    return COM::BaseComponent::QueryInterface(iid, ppv);
}

//Interface IPoint
ILayout* BasePoint::layout()const
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
