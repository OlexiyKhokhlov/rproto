#pragma once

#include <vector>
#include <com/basecomponent.h>
#include <ibook.h>
#include <libdjvu/ddjvuapi.h>

class DjVuPlugin;
//class ILayout;
//class DjVuPageLayout;
//class DjVuListener;

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
    void processMessage(const ddjvu_message_t *);

private:
    void error(const ddjvu_message_error_s*);
    void info(const ddjvu_message_info_s*);
    void newstream(const ddjvu_message_newstream_s*);
    void docinfo(const ddjvu_message_docinfo_s *);
    void pageinfo(const ddjvu_message_pageinfo_s *);
    void relayout(const ddjvu_message_relayout_s *);
    void redisplay(const ddjvu_message_redisplay_s *);
    void chunk(const ddjvu_message_chunk_s *);
    void thumbnail(const ddjvu_message_thumbnail_s *);
    void progress(const ddjvu_message_progress_s *);
    
private:
    DjVuPlugin           *owner;
    ddjvu_document_t     *djvu_document;
};
