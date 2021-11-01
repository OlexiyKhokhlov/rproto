#include "djvuplugin.h"
#include "djvubook.h"
//#include "djvupagelayout.h"

DjVuPlugin::DjVuPlugin()
    : djvu_context(nullptr)
    , stopListener(false)
{
    djvu_context = ddjvu_context_create("RProto DjVuLibre Plugin");
    if(djvu_context != nullptr){
        extensions.push_back("djv");
        extensions.push_back("djvu");
        message_thread = std::thread(&DjVuPlugin::messageLoop, this);
        ddjvu_message_set_callback(djvu_context, DjVuPlugin::msg_callback, this);
    }
}

DjVuPlugin::~DjVuPlugin()
{
    stopListener = true;
    message_thread.join();
    ddjvu_context_release(djvu_context);
}

//IPlugin interface
RProto::IBook* DjVuPlugin::createBook(const char* file)
{
    auto doc = ddjvu_document_create_by_filename_utf8(djvu_context, file, 1);
    if(doc == nullptr)
        return nullptr;
    return bookTable[doc] = Boss::Base<DjVuBook>::CreatePtr(this, doc);
}

const std::vector<std::string>& DjVuPlugin::fileExtensions()
{
    return extensions;
}

void DjVuPlugin::removeBook(ddjvu_document_t* book){
    bookTable.erase(book);
}

void DjVuPlugin::messageLoop(){
    while(true){
        {
            std::unique_lock<std::mutex> lk(msgMutex);
            msgConditional.wait(lk, [this]{return ddjvu_message_peek(djvu_context)!=nullptr;});
        }
        if(stopListener)
            break;
        const ddjvu_message_t *msg;
        while ((msg = ddjvu_message_peek(djvu_context)))
        {
            auto it = bookTable.find(msg->m_any.document);
            if(it != bookTable.end()){
                it->second->processMessage(msg);
            }
            ddjvu_message_pop(djvu_context);
        }
    }
}

void DjVuPlugin::msg_callback(ddjvu_context_t *context, void *closure){
    if(closure != nullptr){
        DjVuPlugin *owner = reinterpret_cast<DjVuPlugin*>(closure);
        owner->msgConditional.notify_one();
    }

}
