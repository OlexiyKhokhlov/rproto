#pragma once

#include <irect.h>

namespace RProto {

class ILayout;

class IImageTile : public IRect
{
public:
    virtual const char* data()const =0;

    static std::string iid;
};
}
