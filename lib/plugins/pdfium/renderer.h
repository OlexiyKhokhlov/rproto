#pragma once

#include <com/basecomponent.h>
#include <irenderer.h>

/**
flags
-
0 for normal display, or combination of flags defined below
0x01 -  Set if annotations are to be rendered
0x02 -  Set if using text rendering optimized for LCD display
0x04 -  Set if you don't want to use GDI+ (Applicable to desktop Windows systems only)
0x08 -  Grayscale output
0x80 -  Set if you want to get some debug info.
0x100 - Set if you don't want to catch exception
 */
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
    virtual void renderRect(RProto::IRect *rect) override;
};


