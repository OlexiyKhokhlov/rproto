#pragma once

#include <com/iunknown.h>

namespace RProto {
class IRect;
class IImageTile;

class IRenderer : public COM::IUnknown
{
public:
    virtual ~IRenderer(){}
  
    virtual IImageTile* renderRect(IRect* rect) =0;

    static std::string iid;
};
}
