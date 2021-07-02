#pragma once

#include "forward.h"

namespace RProto {

class IRect
{
public:
    virtual ILayoutPtrT layout()const =0;
    virtual int page()const =0;
    virtual double zoom()const =0;

    virtual int x()const =0;
    virtual int y()const =0;
    virtual int width()const =0;
    virtual int height()const =0;
};
} //namespace RProto

