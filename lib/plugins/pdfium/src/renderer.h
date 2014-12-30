#pragma once

#include <core/co_class.h>

#include <irenderer.h>

class Book;

class Renderer : public Boss::CoClass<Boss::MakeId("PDFium.Renderer"), RProto::IRenderer>
{
public:
    explicit Renderer(Book *book);
    virtual ~Renderer();

    // IRenderer interface
    virtual ImageTilePtr renderRect(RProto::IRect *rect) override;
    virtual ImageTilePtr renderThumbnail(RProto::IRect* rect) override;
    virtual void addListener(RProto::IRendererListener *listener) override;

private:
    Book *bookOwner;
};


