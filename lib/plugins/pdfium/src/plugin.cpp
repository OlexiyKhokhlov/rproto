#include <util/singletone.h>
#include <plugin.h>
#include <book.h>
#include "library.h"

#include <core/base.h>

Plugin::Plugin()
{
    Singletone<Library>::instance().Init();
    extensions.push_back("pdf");
}

Plugin::~Plugin()
{
    Singletone<Library>::instance().Close();
}

//IPlugin interface
RProto::IBook* Plugin::createBook(const char* file)
{
    Singletone<Library>::instance().BLL_lock();
    FPDF_DOCUMENT pdf_doc = FPDF_LoadDocument(file, nullptr);
    Singletone<Library>::instance().BLL_unlock();
    if(pdf_doc == nullptr)
        return nullptr;

    auto book = Boss::Base<Book>::CreatePtr(pdf_doc);
    book->AddRef();
    return book;
}

const std::vector<std::string>& Plugin::fileExtensions()
{
    return extensions;
}
