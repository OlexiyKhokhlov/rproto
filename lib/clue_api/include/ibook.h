#pragma once

#include <com/iunknown.h>

namespace RProto{

class ILayout;
class IRenderer;

class IBook : public COM::IUnknown
{
public:
    virtual ~IBook(){}

    virtual ILayout* createLayout(double dpix, double dpiy) =0;
    virtual IRenderer* createRenderer() =0;

    static std::string iid;
};
}
