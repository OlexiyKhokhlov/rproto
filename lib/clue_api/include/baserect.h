#pragma once

#include <com/basecomponent.h>
#include <irect.h>

namespace RProto {

class BaseRect : public COM::BaseComponent, public IRect
{
public:
    BaseRect(ILayout *lay, int page, double zoom, int x, int y, int width, int height);
    virtual ~BaseRect();

    // IUnknown interface
    virtual int addRef() override{
        return COM::BaseComponent::addRef();
    }
    virtual int release() override{
        return COM::BaseComponent::release();
    }
    COM::HResult QueryInterface(const std::string &, void **ppv) override;

    //interface IRect
    virtual ILayout* layout()const override;
    virtual int page()const override;
    virtual double zoom()const override;
    virtual int x()const override;
    virtual int y()const override;
    virtual int width()const override;
    virtual int height()const override;

private:
    ILayout *mLayout;
    int mPage;
    double mZoom;
    int mX;
    int mY;
    int mWidth;
    int mHeight;
};
}//namespace RProto
