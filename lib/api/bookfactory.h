#pragma once

#include <QStringList>
#include <QHash>
#include <iunknown.h>

namespace RProto{

class IPlugin;
class IBook;

class BookFactory
{
public:
    BookFactory();
    ~BookFactory();

    bool registerPlugin(IPlugin* plug);
    QStringList supportedExtensions();
    boost::intrusive_ptr<IBook> createBook(const QString& path);

private:
    QHash<QString, IPlugin*> pluginTable;
};
}
