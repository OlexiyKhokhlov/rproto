#pragma once

#include <iplugin.h>

#include <util/visibility.h>

class DLL_PUBLIC Plugin : public RProto::IPlugin
{
public:
    Plugin();
    ~Plugin();

private:
    //IPlugin interface
    RProto::IBookPtrT createBook(const char* file) override;
    const std::vector<std::string>& fileExtensions() const override;

    std::vector<std::string> extensions = {"pdf"};
};
