#pragma once

#include "forward.h"
#include <memory>

namespace RProto {

class IBook
{
public:
    virtual ~IBook(){}

    virtual ILayoutPtrT   createLayout(double dpix, double dpiy) = 0;
    virtual IRendererPtrT createRenderer() = 0;
    virtual IContentPtrT  createContent() = 0;
};
}
