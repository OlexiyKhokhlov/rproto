#pragma once

#include <irenderer.h>

class Book;

class Renderer : public RProto::IRenderer
{
public:
    explicit Renderer(std::shared_ptr<Book> book);
    virtual ~Renderer();

    // IRenderer interface
    virtual RProto::ImageTilePtrT renderRect(RProto::IRectPtrT rect) override;
    virtual RProto::ImageTilePtrT renderThumbnail(RProto::IRectPtrT rect) override;
    virtual void addListener(RProto::IRendererListener *listener) override;

private:
    std::shared_ptr<Book> bookOwner;
};


