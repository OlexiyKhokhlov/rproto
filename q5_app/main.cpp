#include <QApplication>
#include <QCoreApplication>
#include <QTranslator>
#include <QLocale>
#include <QSettings>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath()+"/plugins");

    app.setOrganizationName("localhost");
    app.setOrganizationDomain("localdomain.com");
    app.setApplicationName("R-proto");

    QSettings settings;
    QString translationsPath = settings.value("RProto/translations", QCoreApplication::applicationDirPath()+"/translations/").toString();
    QTranslator translator;
    if(translator.load(translationsPath+QLocale::system().name())){
        app.installTranslator(&translator);
    } else if(translator.load(QCoreApplication::applicationDirPath()+"/"+QLocale::system().name())){
        app.installTranslator(&translator);
    }

    auto mwindow = std::make_unique<MainWindow>();
    mwindow->show();

    return app.exec();
}
