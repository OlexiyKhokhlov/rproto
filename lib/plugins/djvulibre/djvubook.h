#pragma once

#include <vector>
#include <QObject>
#include <QSet>

#include <libdjvu/ddjvuapi.h>

#include <ibook.h>
#include <baseobject.h>

namespace RProto {

class DjVuPlugin;
class ILayout;
class IAsyncRenderer;
class DjVuRenderer;
class DjVuPageLayout;
class DjVuListener;

class DjVuBook : public QObject, public IBook, public BaseObject
{
    Q_OBJECT
public:
    DjVuBook(RProto::DjVuPlugin *plugin, QObject* parent=nullptr);
    virtual ~DjVuBook();

    //IUnknown
    virtual size_t addRef();
    virtual size_t release();
    virtual HResult queryInterface(const QUuid& iid, void** interface);
    
    bool open(const QString& file);

    //IBook interface
    virtual boost::intrusive_ptr<ILayout> createLayout();
    //TODO: replace via queryInterface
    virtual boost::intrusive_ptr<IAsyncRenderer> createRenderer();

    void layoutRemoved(DjVuPageLayout* layout);

private slots:
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
    DjVuPlugin                 *owner;
    DjVuRenderer            *renderer;
    ddjvu_document_t     *djvu_document;
    std::vector<ddjvu_page_t*>  pages;
    QSet<DjVuPageLayout*>   layouts;

//    void doLayout();
};
}
