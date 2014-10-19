#pragma once

#include <ilayout.h>
#include <com/basecomponent.h>
#include <fpdfview.h>
#include <vector>

class Book;

class Layout : public COM::BaseComponent, public RProto::ILayout
{
public:
    explicit Layout(Book *book);
    virtual ~Layout();

    //Iunknown interface
    virtual COM::HResult QueryInterface(const std::string& id, void** ppv) override;
    virtual int addRef(){
        return COM::BaseComponent::addRef();
    }
    virtual int release() {
        return COM::BaseComponent::release();
    }

    //ILayout interface
    virtual int pages()const override;

    virtual QSize pageSize(int rpage=0)const override;
    virtual double pageZoom(int rpage=0)const override;
    virtual void setPageZoom(int rpage=0, double zoom=1) override;
    virtual void setDocumentZoom(double zoom=1) override;

    virtual RProto::IPoint* createPoint(int rpage, int x, int y)const override;
    //TODO create a point by link
    //virtual IPoint* createPoint(ILink *link)const override;
    virtual RProto::IRect* createRect(int rpage, int x, int y, int width, int height)const override;

    virtual QObject* qobject() override;

private:
    Book *book;
    double dpiX, dpiY;
    struct Page{
        FPDF_PAGE  pdf_page;
        double zoom;
    };
    std::vector<Page> page_vector;
};
