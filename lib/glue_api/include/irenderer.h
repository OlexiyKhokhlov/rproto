#pragma once

#include <iimagetile.h>

namespace RProto {

class IRect;

class IRenderer
{
public:
    virtual ~IRenderer() = default;
  
    virtual ImageTilePtrT renderRect(IRectPtrT rect) =0;
    virtual ImageTilePtrT renderThumbnail(IRectPtrT rect) =0;
};
}
