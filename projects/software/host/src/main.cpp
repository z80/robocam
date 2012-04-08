

#include <QtGui>
#include "host_tray.h"
#include "host_ice_thread.h"
// Logging
#include "QsLog.h"
#include "QsLogDest.h"


int main( int argc, char * argv[] )
{
    QString fileName = CHostTray::iniFileName();
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
    
    const QString sLogPath = QString( "host-%1.log" ).arg( QDateTime(QDateTime::currentDateTime() ).toString( "yyyy.MM.dd-hh.mm.ss" ) );
    QsLogging::DestinationPtr fileDestination(
       QsLogging::DestinationFactory::MakeFileDestination(sLogPath) );
    
    QsLogging::DestinationPtr debugDestination(
       QsLogging::DestinationFactory::MakeDebugOutputDestination() );
    
    logger.addDestination( debugDestination.get() );
    logger.addDestination( fileDestination.get() );

    QLOG_INFO() << "Host started";

    if ( !console )
    {
        QApplication a( argc, argv );

        QLOG_INFO() << "GUI mode";

        CHostTray * ht = new CHostTray();
        ht->show();

        int ret = a.exec();
        
        QLOG_INFO() << "Host exited with code " << ret;
        return ret;
    }
    else
    {
        QCoreApplication a( argc, argv );
        QLOG_INFO() << "Console mode";

        QString listen  = s.value( "listen",  "tcp -p 26001 -t 5000" ).toString();
        QString connect = s.value( "connect", "default -p 12345 -t 5000" ).toString();
        QString passwd  = s.value( "passwd", "qwertyqwerty" ).toString();
        bool    emulation = s.value( "emulation", true ).toBool();
        CHostIceThread * host = new CHostIceThread( listen.toStdString(), 
                                                    connect.toStdString(), 
                                                    passwd.toStdString() );
        if ( !host->listen() )
        {
            QLOG_INFO() << "host->losten() failed";
            return 1;
        }
        if ( !host->connect( emulation ) )
            QLOG_INFO() << "host->connect() failed";
            return 2;
        int res = a.exec();
        QLOG_INFO() << "Host exited with code " << res;
        return res;
    }
}











