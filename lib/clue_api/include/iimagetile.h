#pragma once

#include <com/iunknown.h>
#include <QRect>

namespace RProto {

class ILayout;

class IImageTile : public COM::IUnknown
{
public:

    virtual const char* data()const =0;
    virtual ILayout* layout()const =0;

    virtual int page()const =0;
    virtual double zoom()const =0;

    static std::string iid;
};
}
