#pragma once

#include <memory>

namespace RProto {
    class IPlugin;
    class IBook;
    class ILayout;
    class IRenderer;
    class IContent;
    class IPoint;
    class IRect;
    class IImageTile;
    class ILayoutListener;


    using IBookPtrT     = std::shared_ptr<IBook>;
    using ILayoutPtrT   = std::shared_ptr<ILayout>;
    using IRendererPtrT = std::shared_ptr<IRenderer>;
    using IContentPtrT  = std::shared_ptr<IContent>;
    using IPointPtrT    = std::shared_ptr<IPoint>;
    using IRectPtrT     = std::shared_ptr<IRect>;
    using ImageTilePtrT  = std::shared_ptr<RProto::IImageTile>;
    using ILayoutListenerPtrT = std::shared_ptr<RProto::ILayoutListener>;
}
