#pragma once

#include <irenderer.h>

class Book;

class Renderer : public RProto::IRenderer
{
public:
    explicit Renderer(std::shared_ptr<Book> book);
    virtual ~Renderer() = default;

    // IRenderer interface
    //void renderRectAsync(RProto::IRectPtrT rect, )
    RProto::ImageTilePtrT renderRect(RProto::IRectPtrT rect) override;
    RProto::ImageTilePtrT renderThumbnail(RProto::IRectPtrT rect) override;

private:
    std::shared_ptr<Book>      bookOwner;
};


