#pragma once

#include <ilayout.h>
#include <iinternallayout.h>
#include <com/basecomponent.h>
#include <fpdfview.h>
#include <vector>
#include <thread>

#include <QObject>

class Book;

class Layout : public QObject, public COM::BaseComponent, public RProto::ILayout, public IInternalLayout
{
    Q_OBJECT

public:
    explicit Layout(Book *book, double dpix, double dpiy);
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
    virtual RProto::IBook* book() override;
    virtual void startLayouting() override;
    virtual void cancelLayouting() override;
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

    //IInternalLayout interface
    virtual IInternalLayout::PageDescriptor& getPageDescr(int rpage=0) override;

signals:
    void pageCountChanged(int);
    void pageSizeChanged(int page, QSize size);

private:
    Book *bookOwner;
    double dpiX, dpiY;
    std::vector<IInternalLayout::PageDescriptor> page_vector;
    volatile bool stopLayouting;
    std::thread thread;

    void createPages();
};
