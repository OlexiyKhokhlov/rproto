#pragma once

#include <com/basecomponent.h>
#include <irenderer.h>

class Renderer : public COM::BaseComponent, public RProto::IRenderer
{
public:
    Renderer();

    // IUnknown interface
    virtual int addRef() override{
        return COM::BaseComponent::addRef();
    }
    virtual int release() override{
        return COM::BaseComponent::release();
    }
    virtual COM::HResult QueryInterface(const std::string &, void **ppv) override;

    // IRenderer interface
    virtual RProto::IImageTile* renderRect(RProto::IRect *rect) override;
};


