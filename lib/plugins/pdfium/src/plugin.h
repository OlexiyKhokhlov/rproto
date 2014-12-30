#pragma once

#include <iplugin.h>
#include <core/co_class.h>

namespace RProto {
    class IBook;
}

class Plugin : public Boss::CoClass<Boss::MakeId("PDFium.Plugin"), RProto::IPlugin>
{
public:
    Plugin();
    ~Plugin();

private:
    //IPlugin interface
    virtual RProto::IBook* createBook(const char* file) override;
    virtual const std::vector<std::string>& fileExtensions() override;

    std::vector<std::string> extensions;
};
