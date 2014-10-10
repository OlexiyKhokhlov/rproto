#include "api/bookfactory.h"
#include "api/iplugin.h"
#include "api/ibook.h"

#include <QFileInfo>
#include <QDebug>

using namespace RProto;

BookFactory::BookFactory()
{
}

BookFactory::~BookFactory()
{
    for(IPlugin* plug : pluginTable.values()){
        delete plug;
    }
}

bool BookFactory::registerPlugin(IPlugin* plug)
{
    if(plug == nullptr)
        return false;

    qDebug() << plug->fileExtensions();
    for(const QString& str : plug->fileExtensions()){
        pluginTable.insert(str, plug);
    }
    return true;
}

QStringList BookFactory::supportedExtensions()
{
    return pluginTable.keys();
}

boost::intrusive_ptr<IBook> BookFactory::createBook(const QString& path)
{
    QFileInfo finfo(path);
    if(finfo.exists() && finfo.isFile()){
        auto it = pluginTable.find(finfo.completeSuffix());
        if(it != pluginTable.end()){
            IPlugin* plug = it.value();
            return plug->createBook(path);
        }
    }
    return nullptr;
}
