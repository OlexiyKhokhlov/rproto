#include <bookfactory.h>
#include <iplugin.h>
#include <ibook.h>

#include "../lib/plugins/pdfium/src/plugin.h"

#include <QFileInfo>

using namespace RProto;

BookFactory::BookFactory()
{
    registerPlugin(new Plugin());
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

    for(const std::string& str : plug->fileExtensions()){
        pluginTable.insert(str.data(), plug);
    }
    return true;
}

QStringList BookFactory::supportedExtensions()
{
    return pluginTable.keys();
}

RProto::IBookPtrT BookFactory::createBook(const QString& path)
{
    QFileInfo finfo(path);
    if(finfo.exists() && finfo.isFile()){
        auto it = pluginTable.find(finfo.suffix());
        if(it != pluginTable.end()){
            IPlugin* plug = it.value();
            return plug->createBook(path.toLocal8Bit().constData());
        }
    }
    return nullptr;
}
