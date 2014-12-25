#pragma once

#include <core/ibase.h>
#include <core/co_class.h>
#include <core/base.h>
#include <core/ref_obj_ptr.h>
#include <core/module.h>


namespace RProto {

class ILayout;

class IPoint : public Boss::Inherit<Boss::IBase>
{
public:
    //BOSS_DECLARE_IFACEID("RProto.IPoint")
    BOSS_DECLARE_IFACEID_HEX(0xFACA896C)

    virtual ILayout* layout()const =0;
    virtual int page()const =0;
    virtual double zoom()const =0;
    virtual int x()const =0;
    virtual int y()const =0;
};
} //namespace RProto
