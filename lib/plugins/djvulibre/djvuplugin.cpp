#include "djvuplugin.h"
#include "djvubook.h"
#include "djvupagelayout.h"
#include "djvulistener.h"

namespace RProto{

QStringList DjVuPlugin::extList;

DjVuPlugin::DjVuPlugin()
    :djvu_context(nullptr)
    ,listenerThread(nullptr)
{
    djvu_context = ddjvu_context_create("DjVuLibre Plugin");
    if(djvu_context != nullptr){
            extList << "djv" << "djvu";
            listenerThread = new DjVuListener(djvu_context);
            listenerThread->start();
    }
}

DjVuPlugin::~DjVuPlugin()
{
    delete djvu_context;
    listenerThread->deleteLater();
}

//IUnknown
size_t DjVuPlugin::addRef()
{
    return internalAddRef();
}

size_t DjVuPlugin::release()
{
    return internalRelease();
}

HResult DjVuPlugin::queryInterface(const QUuid& iid, void** interface)
{
    return HResult(true, 0);
}

//IPlugin
const QString& DjVuPlugin::name()const
{
    static QString name("DjVuLibre plugin");
    return name;
}

boost::intrusive_ptr<IBook> DjVuPlugin::createBook(const QString& file)
{
    RProto::DjVuBook* book = new RProto::DjVuBook(this);
    if(book->open(file)){
        return book;
    }
    return nullptr;
}

const QStringList& DjVuPlugin::fileExtensions()
{
    return extList;
}

}
