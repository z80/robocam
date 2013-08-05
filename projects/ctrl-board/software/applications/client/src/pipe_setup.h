
#include <QtGui>
#include "ui_pipe_setup.h"

class PipeSetup: public QDialog
{
    Q_OBJECT
public:
    PipeSetup( QWidget * p );
    ~PipeSetup();

    void setPipe( int localPort, int remotePort, const QString & remoteHost );
    void pipe( int & localPort, int & remotePort, QString & remoteHost ) const;
private:
    Ui_PipeSetup ui;
};



