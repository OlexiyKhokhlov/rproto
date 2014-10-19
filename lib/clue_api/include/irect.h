#pragma once

#include <com/iunknown.h>

namespace RProto {

class ILayout;

class IRect : public COM::IUnknown
{
public:
    virtual ILayout* layout()const =0;
    virtual int page()const =0;
    virtual double zoom()const =0;

    virtual int x()const =0;
    virtual int y()const =0;
    virtual int width()const =0;
    virtual int height()const =0;

    static std::string iid;
};
} //namespace RProto

