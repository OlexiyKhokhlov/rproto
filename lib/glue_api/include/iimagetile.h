#pragma once

#include  "forward.h"

namespace RProto {

class IRect;

class IImageTile
{
public:
    virtual const char* data()const =0;
    virtual const IRectPtrT rect()const =0;
};
}
