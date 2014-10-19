#pragma once

#include <QRect>

#include <com/iunknown.h>

namespace RProto {
class IRect;
class IImageTile;

class IRenderer : public COM::IUnknown
{
public:
    virtual ~IRenderer(){}
  
    virtual void renderRect(IRect* rect) =0;

    static std::string iid;
};
}
