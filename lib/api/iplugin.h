#pragma once 

#include <baseobject.h>
#include <iunknown.h>
#include <boost/intrusive_ptr.hpp>
#include <QStringList>

namespace RProto{
class IBook;

class IPlugin : public IUnknown
{
public:
    virtual ~IPlugin(){}
    
    //IPlugin
    virtual const QString& name()const =0;
    virtual boost::intrusive_ptr<RProto::IBook> createBook(const QString& file) =0;
    virtual const QStringList& fileExtensions() =0;
};
}
