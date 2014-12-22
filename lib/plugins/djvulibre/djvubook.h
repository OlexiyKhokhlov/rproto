#pragma once

#include <libdjvu/ddjvuapi.h>
#include <vector>
#include <mutex>
#include <memory>
#include <com/basecomponent.h>
#include <util/rlucache.h>
#include <ibook.h>

class DjVuPlugin;
class DjVuPageLayout;

class DjVuBook : public COM::BaseComponent, public RProto::IBook
{
public:
    DjVuBook(DjVuPlugin *plugin, ddjvu_document_t* doc);
    virtual ~DjVuBook();

    //Iunknown interface
    virtual COM::HResult QueryInterface(const std::string& id, void** ppv) override;
    virtual int addRef(){
        return COM::BaseComponent::addRef();
    }
    virtual int release() {
        return COM::BaseComponent::release();
    }
    
    //IBook interface
    virtual RProto::ILayout* createLayout(double dpix, double dpiy) override;
    virtual RProto::IRenderer* createRenderer() override;

    //Internal interface
    struct Page{
        explicit Page(ddjvu_document_t *doc, int  num)
            :djvu_page(nullptr)
        {
            djvu_page = ddjvu_page_create_by_pageno(doc, num);
         }

        ~Page(){
            ddjvu_page_release(djvu_page);
        }

        ddjvu_page_t *djvu_page;
    };

    std::shared_ptr<DjVuBook::Page> getPage(int num);
    void processMessage(const ddjvu_message_t *);

private:
    void error(const ddjvu_message_t*);
    void info(const ddjvu_message_t*);
    void newstream(const ddjvu_message_t*);
    void docinfo(const ddjvu_message_t *);
    void pageinfo(const ddjvu_message_t *);
    void relayout(const ddjvu_message_t *);
    void redisplay(const ddjvu_message_t *);
    void chunk(const ddjvu_message_t *);
    void thumbnail(const ddjvu_message_t *);
    void progress(const ddjvu_message_t *);
    
private:
    DjVuPlugin           *owner;
    ddjvu_document_t     *djvu_document;
    std::mutex cacheMutex;
    RLUCache<int, std::shared_ptr<DjVuBook::Page> >  pageCache;
    std::vector<DjVuPageLayout*>    layouts;
};
