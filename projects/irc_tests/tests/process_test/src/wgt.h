
#ifndef __WGT_H_
#define __WGT_H_

#include <QtGui>
#include "ui_wgt.h"
#include "fsw_process.h"

class Wgt: public QWidget
{
    Q_OBJECT
public:
   Wgt( QWidget * parent = 0 );
   ~Wgt();
   
private slots:
    void slotRun();
private:
    Ui_Wgt ui;
    //QProcess * ps;
    FswProcess * ps;
};


#endif




