#include <djvubook.h>
#include <djvuplugin.h>
//#include <djvupagelayout.h>
//#include <djvurenderer.h>
//#include <djvulistener.h>

DjVuBook::DjVuBook(DjVuPlugin *plugin, ddjvu_document_t* doc)
    :owner(plugin)
    ,djvu_document(doc)
{
    owner->addRef();

//    connect(owner->listener(), SIGNAL(error(const ddjvu_message_error_s*)), this, SLOT(error(const ddjvu_message_error_s*)), Qt::BlockingQueuedConnection);
//    connect(owner->listener(), SIGNAL(info(const ddjvu_message_info_s*)), this, SLOT(info(const ddjvu_message_info_s*)), Qt::BlockingQueuedConnection);
//    connect(owner->listener(), SIGNAL(newstream(const ddjvu_message_newstream_s*)), this, SLOT(newstream(const ddjvu_message_newstream_s*)), Qt::BlockingQueuedConnection);
//    connect(owner->listener(), SIGNAL(docinfo(const ddjvu_message_docinfo_s*)), this, SLOT(docinfo(const ddjvu_message_docinfo_s*)), Qt::BlockingQueuedConnection);
//    connect(owner->listener(), SIGNAL(pageinfo(const ddjvu_message_pageinfo_s*)), this, SLOT(pageinfo(const ddjvu_message_pageinfo_s*)), Qt::BlockingQueuedConnection);
//    connect(owner->listener(), SIGNAL(relayout(const ddjvu_message_relayout_s*)), this, SLOT(relayout(const ddjvu_message_relayout_s*)), Qt::BlockingQueuedConnection);
//    connect(owner->listener(), SIGNAL(redisplay(const ddjvu_message_redisplay_s*)), this, SLOT(redisplay(const ddjvu_message_redisplay_s*)), Qt::BlockingQueuedConnection);
//    connect(owner->listener(), SIGNAL(chunk(const ddjvu_message_chunk_s*)), this, SLOT(chunk(const ddjvu_message_chunk_s*)), Qt::BlockingQueuedConnection);
//    connect(owner->listener(), SIGNAL(thumbnail(const ddjvu_message_thumbnail_s*)), this, SLOT(thumbnail(const ddjvu_message_thumbnail_s*)), Qt::BlockingQueuedConnection);
//    connect(owner->listener(), SIGNAL(progress(const ddjvu_message_progress_s*)), this, SLOT(progress(const ddjvu_message_progress_s*)), Qt::BlockingQueuedConnection);
}

DjVuBook::~DjVuBook()
{
  if(djvu_document != nullptr)
    ddjvu_document_release(djvu_document);

//  delete renderer;
  owner->release();
}

//Iunknown interface
COM::HResult DjVuBook::QueryInterface(const std::string& id, void** ppv)
{
    if(id == RProto::IBook::iid){
        *ppv = (RProto::IBook*)this;
        return COM::HResult();
    }

    return COM::BaseComponent::QueryInterface(id, ppv);
}

//IBook interface
RProto::ILayout* DjVuBook::createLayout(double dpix, double dpiy)
{
    return nullptr;
}

RProto::IRenderer* DjVuBook::createRenderer()
{
    return nullptr;
}

//DjVu message handlers
void DjVuBook::error(const ddjvu_message_error_s* msg)
{
    if(msg->any.document != djvu_document)
        return;
}

void DjVuBook::info(const ddjvu_message_info_s* msg)
{
    if(msg->any.document != djvu_document)
        return;
}

void DjVuBook::newstream(const ddjvu_message_newstream_s* msg)
{
    if(msg->any.document != djvu_document)
        return;
}

void DjVuBook::docinfo(const ddjvu_message_docinfo_s * msg)
{
    if(msg->any.document != djvu_document)
        return;

    auto count = ddjvu_document_get_pagenum(djvu_document);
//    pages.reserve(count);
    auto page = ddjvu_page_create_by_pageno(djvu_document, 0);
//    ddjvu_page_set_user_data(page, (void*)pages.size());
//    pages.push_back(page);
}

void DjVuBook::pageinfo(const ddjvu_message_pageinfo_s * msg)
{
//    if(msg->any.document != djvu_document)
//        return;
//    for(DjVuPageLayout *layout : layouts){
//        void* ptr = ddjvu_page_get_user_data(msg->any.page);
//        int page = *((int*)(&ptr));
//        ddjvu_pageinfo_t info;
//        ddjvu_document_get_pageinfo(djvu_document, page, &info);
//        layout->layoutChangedInternal(page, QSize(info.width, info.height));
//    }
//    auto count = ddjvu_document_get_pagenum(djvu_document);
//    if(pages.size() < count){
//        auto page = ddjvu_page_create_by_pageno(djvu_document, pages.size());
//        ddjvu_page_set_user_data(page, (void*)pages.size());
//        pages.push_back(page);
//    }
}

void DjVuBook::relayout(const ddjvu_message_relayout_s * msg)
{
    if(msg->any.document != djvu_document)
        return;
//    qDebug() << (quint64)ddjvu_page_get_user_data(msg->any.page);
}

void DjVuBook::redisplay(const ddjvu_message_redisplay_s * msg)
{
    if(msg->any.document != djvu_document)
        return;

//    renderer->redisplay(msg);
}

void DjVuBook::chunk(const ddjvu_message_chunk_s * msg)
{
    if(msg->any.document != djvu_document)
        return;
}

void DjVuBook::thumbnail(const ddjvu_message_thumbnail_s * msg)
{
    if(msg->any.document != djvu_document)
        return;
}

void DjVuBook::progress(const ddjvu_message_progress_s *msg)
{
    if(msg->any.document != djvu_document)
        return;
}
