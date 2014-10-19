#pragma once

#include <QStringList>
#include <QHash>
#include <com/iunknown.h>

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
    IBook* createBook(const QString& path);

private:
    QHash<QString, IPlugin*> pluginTable;
};
}
