#pragma once 

#include "forward.h"

#include <string>
#include <vector>

namespace RProto{
class IPlugin
{
public:
    virtual ~IPlugin(){}
    
    //IPlugin
    virtual IBookPtrT createBook(const char* file) = 0;
    virtual const std::vector<std::string>& fileExtensions() = 0;
};
}
