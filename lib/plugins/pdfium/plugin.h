#pragma once

#include <util/visibility.h>
#include <com/basecomponent.h>
#include <iplugin.h>

namespace RProto {
    class IBook;
}

class DLL_PUBLIC Plugin : public COM::BaseComponent, public RProto::IPlugin
{
public:
    Plugin();
    ~Plugin();

    //Iunknown interface
    virtual COM::HResult QueryInterface(const std::string& id, void** ppv) override;
    virtual int addRef(){
        return COM::BaseComponent::addRef();
    }
    virtual int release() {
        return COM::BaseComponent::release();
    }

    //IPlugin interface
    virtual RProto::IBook* createBook(const QString& file) override;
    virtual const QStringList& fileExtensions() override;

private:
    QStringList extensions;
};
