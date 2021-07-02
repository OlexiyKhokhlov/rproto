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
    virtual RProto::IBookPtrT createBook(const char* file) override;
    virtual const std::vector<std::string>& fileExtensions() override;

    std::vector<std::string> extensions = {"pdf"};
};
