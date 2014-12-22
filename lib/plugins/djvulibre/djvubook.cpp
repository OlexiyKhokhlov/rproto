#include <djvubook.h>
#include <djvuplugin.h>

DjVuBook::DjVuBook(DjVuPlugin *plugin, ddjvu_document_t* doc)
    :owner(plugin)
    ,djvu_document(doc)
    ,pageCache(sizeof(std::shared_ptr<Page>)*10, 0.75f) //10 pages max
{
    owner->addRef();
}

DjVuBook::~DjVuBook()
{
  owner->removeBook(djvu_document);
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
RProto::ILayout* DjVuBook::createLayout(double /*dpix*/, double /*dpiy*/)
{
    return nullptr;
}

RProto::IRenderer* DjVuBook::createRenderer()
{
    return nullptr;
}

void DjVuBook::processMessage(const ddjvu_message_t *msg){
    switch(msg->m_any.tag){
    case DDJVU_ERROR:
        error(msg);
        break;
    case DDJVU_INFO:
        info(msg);
        break;
    case DDJVU_NEWSTREAM:
        newstream(msg);
        break;
    case DDJVU_DOCINFO:
        docinfo(msg);
        break;
    case DDJVU_PAGEINFO:
        pageinfo(msg);
        break;
    case DDJVU_RELAYOUT:
        relayout(msg);
        break;
    case DDJVU_REDISPLAY:
        redisplay(msg);
        break;
    case DDJVU_CHUNK:
        chunk(msg);
        break;
    case DDJVU_THUMBNAIL:
        thumbnail(msg);
        break;
    case DDJVU_PROGRESS:
        progress(msg);
        break;
//    default:

    }
}

//DjVu message handlers
void DjVuBook::error(const ddjvu_message_t* msg)
{
    if(msg->m_any.document != djvu_document)
        return;
}

void DjVuBook::info(const ddjvu_message_t* msg)
{
    if(msg->m_any.document != djvu_document)
        return;
}

void DjVuBook::newstream(const ddjvu_message_t* msg)
{
    if(msg->m_any.document != djvu_document)
        return;
}

void DjVuBook::docinfo(const ddjvu_message_t * msg)
{
    if(msg->m_any.document != djvu_document)
        return;
    //notify all layouts
}

void DjVuBook::pageinfo(const ddjvu_message_t * msg)
{
    if(msg->m_any.document != djvu_document)
        return;

    for(DjVuPageLayout *layout : layouts){
        //layout->layoutChangedInternal(page, QSize(info.width, info.height));
    }
}

void DjVuBook::relayout(const ddjvu_message_t * msg)
{
    if(msg->m_any.document != djvu_document)
        return;
//    qDebug() << (quint64)ddjvu_page_get_user_data(msg->any.page);
}

void DjVuBook::redisplay(const ddjvu_message_t * msg)
{
    if(msg->m_any.document != djvu_document)
        return;

//    renderer->redisplay(msg);
}

void DjVuBook::chunk(const ddjvu_message_t * msg)
{
    if(msg->m_any.document != djvu_document)
        return;
}

void DjVuBook::thumbnail(const ddjvu_message_t * msg)
{
    if(msg->m_any.document != djvu_document)
        return;
}

void DjVuBook::progress(const ddjvu_message_t *msg)
{
    if(msg->m_any.document != djvu_document)
        return;
}
