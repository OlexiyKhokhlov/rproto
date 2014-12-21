#pragma once

#include <util/visibility.h>
#include <com/basecomponent.h>
#include <iplugin.h>

#include <libdjvu/ddjvuapi.h>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace RProto {
    class IBook;
}

class DjVuBook;

class DLL_PUBLIC DjVuPlugin : public COM::BaseComponent, public RProto::IPlugin
{
public:
    DjVuPlugin();
    virtual ~DjVuPlugin();

    //Iunknown interface
    virtual COM::HResult QueryInterface(const std::string& id, void** ppv) override;
    virtual int addRef(){
        return COM::BaseComponent::addRef();
    }
    virtual int release() {
        return COM::BaseComponent::release();
    }

    //IPlugin interface
    virtual RProto::IBook* createBook(const char* file) override;
    virtual const std::vector<std::string>& fileExtensions() override;

    //Plugin private
    void removeBook(ddjvu_document_t* book);

private:
    std::vector<std::string> extensions;
    ddjvu_context_t     *djvu_context;
    std::unordered_map<ddjvu_document_t*, DjVuBook*> bookTable;

    std::thread     message_thread;
    std::mutex      msgMutex;
    std::condition_variable msgConditional;
    volatile bool stopListener;

    void messageLoop();
    static void msg_callback(ddjvu_context_t *context, void *closure);
};
