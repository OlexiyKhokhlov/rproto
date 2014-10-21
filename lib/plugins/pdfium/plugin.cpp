#include <plugin.h>
#include <book.h>
#include <fpdfview.h>

Plugin::Plugin()
{
    FPDF_InitLibrary(nullptr);
    extensions << "pdf";
}

Plugin::~Plugin()
{
    FPDF_DestroyLibrary();
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
RProto::IBook* Plugin::createBook(const QString& file)
{
    FPDF_DOCUMENT pdf_doc = FPDF_LoadDocument(file.toUtf8().constData(), nullptr);
    if(pdf_doc == nullptr)
        return nullptr;

    return new Book(pdf_doc);
}

const QStringList& Plugin::fileExtensions()
{
    return extensions;
}
