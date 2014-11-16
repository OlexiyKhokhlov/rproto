#pragma once

#include <com/basecomponent.h>
#include <irenderer.h>

class Book;

class Renderer : public COM::BaseComponent, public RProto::IRenderer
{
public:
    explicit Renderer(Book *book);
    virtual ~Renderer();

    // IUnknown interface
    virtual int addRef() override{
        return COM::BaseComponent::addRef();
    }
    virtual int release() override{
        return COM::BaseComponent::release();
    }
    virtual COM::HResult QueryInterface(const std::string &, void **ppv) override;

    // IRenderer interface
    virtual ImageTilePtr renderRect(RProto::IRect *rect) override;
    virtual ImageTilePtr renderThumbnail(RProto::IRect* rect) override;
    virtual void addListener(RProto::IRendererListener *listener) override;

private:
        Book *bookOwner;
};


