
#ifndef __RES_DLG_H_
#define __RES_DLG_H_

#include <QtGui>
#include "ui_res_dlg.h"

class ResDlg: public QDialog
{
    Q_OBJECT
public:
    ResDlg( QWidget * parent = 0 );
    ~ResDlg();

    void setRes( const QSize & sz );
    const QSize res() const;
private:
    Ui_ResDlg ui;
};



#endif




