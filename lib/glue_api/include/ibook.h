#pragma once

#include <core/ibase.h>
#include <core/ref_obj_ptr.h>

namespace RProto{

class ILayout;
class IRenderer;
class IContent;

class IBook : public Boss::Inherit<Boss::IBase>
{
public:
    BOSS_DECLARE_IFACEID("RProto.IBook")

    virtual ~IBook(){}

    virtual ILayout* createLayout(double dpix, double dpiy) =0;
    virtual IRenderer* createRenderer() =0;
    virtual IContent* createContent() =0;
};
}

typedef Boss::RefObjPtr<RProto::IBook> IBookPtr;
