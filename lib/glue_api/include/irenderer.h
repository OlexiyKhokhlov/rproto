#pragma once

#include <iimagetile.h>
#include <core/ibase.h>
#include <core/ref_obj_ptr.h>

namespace RProto {

class IRect;

class IRendererListener{
public:
    //void
};

class IRenderer : public Boss::Inherit<Boss::IBase>
{
public:
    BOSS_DECLARE_IFACEID("RProto.IRenderer")

    virtual ~IRenderer(){}
  
    virtual ImageTilePtr renderRect(IRect* rect) =0;
    virtual ImageTilePtr renderThumbnail(IRect* rect) =0;
    virtual void addListener(IRendererListener *listener)=0;
};
}

typedef Boss::RefObjPtr<RProto::IRenderer> IRendererPtr;
