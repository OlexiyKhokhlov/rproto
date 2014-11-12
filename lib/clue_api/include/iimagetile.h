#pragma once

#include <com/iunknown.h>

namespace RProto {

class IRect;

class IImageTile : public COM::IUnknown
{
public:
    virtual const char* data()const =0;
    virtual const IRect* rect()const =0;

    static std::string iid;
};
}

typedef boost::intrusive_ptr<RProto::IImageTile>    ImageTilePtr;
