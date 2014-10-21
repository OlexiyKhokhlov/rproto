#pragma once

#include <com/iunknown.h>

namespace RProto {

class ILayout;

class IImageTile : public COM::IUnknown
{
public:
    virtual const char* data()const =0;

    static std::string iid;
};
}
