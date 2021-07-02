#include <util/singletone.h>
#include <plugin.h>
#include <book.h>
#include "library.h"

Plugin::Plugin()
{
    Singletone<Library>::instance().Init();
}

Plugin::~Plugin()
{
    Singletone<Library>::instance().Close();
}

//IPlugin interface
RProto::IBookPtrT Plugin::createBook(const char* file)
{
    Singletone<Library>::instance().BLL_lock();
    FPDF_DOCUMENT pdf_doc = FPDF_LoadDocument(file, nullptr);
    Singletone<Library>::instance().BLL_unlock();
    if(pdf_doc == nullptr)
        return nullptr;

    return std::make_shared<Book>(pdf_doc);
}

const std::vector<std::string>& Plugin::fileExtensions()
{
    return extensions;
}
