#include <QApplication>
#include <QCoreApplication>
#include <QTranslator>
#include <QLocale>
#include <QSettings>

//#include <g3log/g2log.hpp>
//#include <g3log/g2logworker.hpp>
#include <util/singletone.h>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
/*    using namespace g2;
    std::unique_ptr<LogWorker> logworker{ LogWorker::createWithNoSink() };
    // initialize the logger before it can receive LOG calls
    initializeLogging(logworker.get());
*/
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
   }else if(translator.load(QCoreApplication::applicationDirPath()+"/"+QLocale::system().name())){
         app.installTranslator(&translator);
   }

    MainWindow *mwindow = new MainWindow();
    mwindow->show();

    auto retcode = app.exec();
    delete mwindow;
    return retcode;
}
