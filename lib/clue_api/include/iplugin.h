#pragma once 

#include <com/basecomponent.h>
#include <com/iunknown.h>
#include <string>
#include <vector>

namespace RProto{
class IBook;

class IPlugin : public COM::IUnknown
{
public:
    virtual ~IPlugin(){}
    
    //IPlugin
    virtual IBook* createBook(const char* file) =0;
    virtual const std::vector<std::string>& fileExtensions() =0;

    static std::string iid;
};
}
