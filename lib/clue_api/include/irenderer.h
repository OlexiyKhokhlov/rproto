#pragma once

#include <com/iunknown.h>
#include <iimagetile.h>

namespace RProto {

class IRect;

class IRendererListener{
public:
    //void
};

class IRenderer : public COM::IUnknown
{
public:
    virtual ~IRenderer(){}
  
    virtual ImageTilePtr renderRect(IRect* rect) =0;
    virtual ImageTilePtr renderThumbnail(IRect* rect) =0;
    virtual void addListener(IRendererListener *listener)=0;

    static std::string iid;
};
}
