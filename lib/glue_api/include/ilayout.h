#pragma once

#include <core/ibase.h>
#include <core/ref_obj_ptr.h>

namespace RProto {

class IPoint;
class IRect;
class IBook;

class ILayoutListener{
public:
    virtual ~ILayoutListener(){}
    virtual void onPageCountChanged(int page_count)=0;
    virtual void onPageSizeChanged(int page, int width, int height)=0;
};

class ILayout : public Boss::Inherit<Boss::IBase>
{
public:
    BOSS_DECLARE_IFACEID("RProto.ILayout")

    virtual ~ILayout(){}

    virtual void addListener(RProto::ILayoutListener *listener) =0;
    virtual RProto::IBook* book() =0;
    virtual void startLayouting() =0;
    virtual void cancelLayouting() =0;
    virtual int pages()const =0;
    virtual std::pair<int,int> pageSize(int rpage=0)const =0;
    virtual double pageZoom(int rpage=0)const =0;
    virtual void setPageZoom(int rpage=0, double zoom=1) =0;
    virtual void setDocumentZoom(double zoom=1) =0;

    virtual IPoint* createPoint(int rpage, int x, int y)const =0;
    //TODO create a point by link
    //virtual IPoint* createPoint(ILink *link)const =0;
    virtual IRect* createRect(int rpage, int x, int y, int width, int height)const =0;
};
}

typedef Boss::RefObjPtr<RProto::ILayout> ILayoutPtr;
