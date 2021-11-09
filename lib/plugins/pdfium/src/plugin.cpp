
#include "library.h"

#include <util/singletone.h>
#include <plugin.h>
#include <book.h>

Plugin::Plugin() {
    Singletone<Library>::instance().Init();
}

Plugin::~Plugin() {
    Singletone<Library>::instance().Close();
}

//IPlugin interface
RProto::IBookPtrT Plugin::createBook(const char* file) {
    FPDF_DOCUMENT pdf_doc = nullptr;
    {
        std::scoped_lock<Library>  lock(Singletone<Library>::instance());
        pdf_doc = FPDF_LoadDocument(file, nullptr);
    }
    if(pdf_doc == nullptr)
        return nullptr;
    return std::make_shared<Book>(pdf_doc);
}

const std::vector<std::string>& Plugin::fileExtensions() const {
    return extensions;
}
