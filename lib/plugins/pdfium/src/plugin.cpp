#include <util/singletone.h>
#include <plugin.h>
#include <book.h>
#include "library.h"

Plugin::Plugin()
{
    Singletone<Library>::instance().Init();
    extensions.push_back("pdf");
}

Plugin::~Plugin()
{
    Singletone<Library>::instance().Close();
}

//Iunknown interface
COM::HResult Plugin::QueryInterface(const std::string& id, void** ppv)
{
    if(id == RProto::IPlugin::iid){
        *ppv = (RProto::IPlugin*)this;
        return COM::HResult();
    }

    return COM::BaseComponent::QueryInterface(id, ppv);
}

//IPlugin interface
RProto::IBook* Plugin::createBook(const char* file)
{
    Singletone<Library>::instance().BLL_lock();
    FPDF_DOCUMENT pdf_doc = FPDF_LoadDocument(file, nullptr);
    Singletone<Library>::instance().BLL_unlock();
    if(pdf_doc == nullptr)
        return nullptr;

    return new Book(pdf_doc);
}

const std::vector<std::string>& Plugin::fileExtensions()
{
    return extensions;
}
