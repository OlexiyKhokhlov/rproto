#pragma once

#include <core/ibase.h>
#include <core/ref_obj_ptr.h>

namespace RProto{

class IContentNode : public Boss::Inherit<Boss::IBase>
{
public:
    BOSS_DECLARE_IFACEID("RProto.IContentNode")

    virtual ~IContentNode(){}

    virtual std::string title()const =0;
};

}//namespace RProto
