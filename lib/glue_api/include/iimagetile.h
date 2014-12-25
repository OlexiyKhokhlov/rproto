#pragma once

#include <core/ibase.h>
#include <core/ref_obj_ptr.h>

namespace RProto {

class IRect;

class IImageTile : public Boss::Inherit<Boss::IBase>
{
public:
    BOSS_DECLARE_IFACEID("RProto.IImageTile")

    virtual const char* data()const =0;
    virtual const IRect* rect()const =0;
};
}

typedef Boss::RefObjPtr<RProto::IImageTile> ImageTilePtr;
