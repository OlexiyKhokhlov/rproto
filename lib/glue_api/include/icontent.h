#pragma once

#include <core/ibase.h>
#include <core/ref_obj_ptr.h>

namespace RProto{

class IContent : public Boss::Inherit<Boss::IBase>
{
public:
    BOSS_DECLARE_IFACEID("RProto.IContent")

    virtual ~IContent(){}

};

}//namespace RProto
