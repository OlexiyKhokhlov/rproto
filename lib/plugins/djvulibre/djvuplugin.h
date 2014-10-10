#pragma once

#include <iplugin.h>
#include <baseobject.h>
#include <libdjvu/ddjvuapi.h>

namespace RProto{
class DjVuListener;

class DjVuPlugin : public IPlugin, public BaseObject
{
public:
    DjVuPlugin();
    virtual ~DjVuPlugin();

    //IUnknown
    virtual size_t addRef();
    virtual size_t release();
    virtual HResult queryInterface(const QUuid& iid, void** interface);

    //IPlugin
    virtual const QString& name()const;
    virtual boost::intrusive_ptr<IBook> createBook(const QString& file);
    virtual const QStringList& fileExtensions();

    inline ddjvu_context_t*  context(){
        return djvu_context;
    }

    inline DjVuListener*  listener(){
        return listenerThread;
    }

private:
    static QStringList extList;
    ddjvu_context_t     *djvu_context;
    DjVuListener         *listenerThread;
};
}
