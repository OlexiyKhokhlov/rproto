#pragma once

#include <iimagetile.h>

namespace RProto {

class IRect;

class IRendererListener{
public:
    //void
};

class IRenderer
{
public:
    virtual ~IRenderer(){}
  
    virtual ImageTilePtrT renderRect(IRectPtrT rect) =0;
    virtual ImageTilePtrT renderThumbnail(IRectPtrT rect) =0;
    virtual void addListener(IRendererListener *listener)=0;
};
}
