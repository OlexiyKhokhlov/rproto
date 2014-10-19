#pragma once

#include <com/basecomponent.h>
#include <ipoint.h>

namespace RProto {

class BasePoint : public COM::BaseComponent, public IPoint
{
public:
    BasePoint(ILayout *lay, int page, double zoom, int x, int y);
    virtual ~BasePoint();

    //Interface IUnknown
    virtual int addRef() override {
        return COM::BaseComponent::addRef();
    }
    int release() override {
        return COM::BaseComponent::release();
    }
    COM::HResult QueryInterface(const std::string &, void **ppv);

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
