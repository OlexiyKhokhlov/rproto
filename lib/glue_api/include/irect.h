#pragma once

#include <core/ibase.h>

namespace RProto {

class ILayout;

class IRect : public Boss::Inherit<Boss::IBase>
{
public:
    BOSS_DECLARE_IFACEID("RProto.IRect")

    virtual ILayout* layout()const =0;
    virtual int page()const =0;
    virtual double zoom()const =0;

    virtual int x()const =0;
    virtual int y()const =0;
    virtual int width()const =0;
    virtual int height()const =0;
};
} //namespace RProto

