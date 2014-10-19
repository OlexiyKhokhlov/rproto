#pragma once 

#include <com/basecomponent.h>
#include <com/iunknown.h>
#include <QStringList>

namespace RProto{
class IBook;

class IPlugin : public COM::IUnknown
{
public:
    virtual ~IPlugin(){}
    
    //IPlugin
    virtual IBook* createBook(const QString& file) =0;
    virtual const QStringList& fileExtensions() =0;

    static std::string iid;
};
}
