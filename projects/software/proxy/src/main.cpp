
#include <QtGui>
#include "tray.h"
#include "proxy.h"
// Logging
#include "QsLog.h"
#include "QsLogDest.h"

int main( int argc, char * argv[] )
{
    QString fileName = CTray::iniFileName();
    QSettings s( fileName, QSettings::IniFormat );
    bool logging = s.value( "logging", true ).toBool();
    s.setValue( "logging", logging );
    bool console = s.value( "console", false ).toBool();
    s.setValue( "console", console );
    s.sync();

    QsLogging::Logger& logger = QsLogging::Logger::instance();
    if ( logging )
        logger.setLoggingLevel(QsLogging::TraceLevel);
    else
        logger.setLoggingLevel(QsLogging::InfoLevel);
    
    const QString sLogPath = QString( "proxy-%1.log" ).arg( QDateTime(QDateTime::currentDateTime() ).toString( "yyyy.MM.dd-hh.mm.ss" ) );
    QsLogging::DestinationPtr fileDestination(
       QsLogging::DestinationFactory::MakeFileDestination(sLogPath) );
    
    QsLogging::DestinationPtr debugDestination(
       QsLogging::DestinationFactory::MakeDebugOutputDestination() );
    
    logger.addDestination( debugDestination.get() );
    logger.addDestination( fileDestination.get() );

    QLOG_INFO() << "Proxy started";

    if ( !console )
    {
        QApplication a( argc, argv );

        QLOG_INFO() << "GUI mode";

        CTray * ht = new CTray();
        ht->show();

        int ret = a.exec();

        return ret;
    }
    else
    {
        QCoreApplication a( argc, argv );

        QLOG_INFO() << "Console mode";

        QString listenHost  = s.value( "listenHost",  "" ).toString();
        QString connectHost = s.value( "connectHost", "localhost" ).toString();
        int listenPort  = s.value( "listenPort",  "1234" ).toInt();
        int connectPort = s.value( "connectPort", "26001" ).toInt();

        CProxy * proxy = new CProxy( 0, listenHost, listenPort, connectHost, connectPort );
        if ( !proxy->isListening() )
        {
            QLOG_INFO() << "Listen failed";
            return 1;
        }
        int res = a.exec();
        return res;
    }
}

