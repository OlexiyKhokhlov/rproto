#pragma once

#include <QSize>
#include <com/iunknown.h>

class QObject;

namespace RProto {

class IPoint;
class IRect;

class ILayout : public COM::IUnknown
{
public:
    virtual ~ILayout(){}

    virtual int pages()const =0;

    virtual QSize pageSize(int rpage=0)const =0;
    virtual double pageZoom(int rpage=0)const =0;
    virtual void setPageZoom(int rpage=0, double zoom=1) =0;
    virtual void setDocumentZoom(double zoom=1) =0;

    virtual IPoint* createPoint(int rpage, int x, int y)const =0;
    //TODO create a point by link
    //virtual IPoint* createPoint(ILink *link)const =0;
    virtual IRect* createRect(int rpage, int x, int y, int width, int height)const =0;

    virtual QObject* qobject()=0;

    static std::string iid;
};
}