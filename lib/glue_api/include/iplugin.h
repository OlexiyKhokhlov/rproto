#pragma once 

#include <string>
#include <vector>

#include <core/ibase.h>
#include <core/error_codes.h>

namespace RProto{
class IBook;

class IPlugin : public Boss::Inherit<Boss::IBase>
{
public:
    BOSS_DECLARE_IFACEID("RProto.IPlugin")
     
    virtual ~IPlugin(){}
    
    //IPlugin
    virtual IBook* createBook(const char* file) =0;
    virtual const std::vector<std::string>& fileExtensions() =0;
};
}
