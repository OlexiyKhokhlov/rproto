#pragma once

#include <util/visibility.h>
#include <com/basecomponent.h>
#include <iplugin.h>

#include <libdjvu/ddjvuapi.h>
#include <thread>

namespace RProto {
    class IBook;
}

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
//    void unregisterBook();

private:
    std::vector<std::string> extensions;
    ddjvu_context_t     *djvu_context;
    volatile bool stopListener;
    std::thread     message_thread;

    void messageLoop();
};
