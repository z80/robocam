
#include "res_dlg.h"

ResDlg::ResDlg( QWidget * parent )
    : QDialog( parent )
{
    ui.setupUi( this );
}

ResDlg::~ResDlg()
{

}

void ResDlg::setRes( const QSize & sz )
{
    QRegExp re( "(\\d+) ?x ?(\\d+)" );

    int cnt = ui.res->count();
    for ( int i=0; i<cnt; i++ )
    {
        QString stri = ui.res->itemText( i );
        if ( re.indexIn( stri ) >= 0 )
        {
            QString w  = re.cap( 1 );
            QString h  = re.cap( 2 );
            int width  = w.toInt();
            int height = h.toInt();
            if ( ( sz.width() == width ) && ( sz.height() == height ) )
            {
                ui.res->setCurrentIndex( i );
                return;
            }
        }
    }
}

const QSize ResDlg::res() const
{
    QRegExp re( "(\\d+) ?x ?(\\d+)" );

    int index = ui.res->currentIndex();
    QString stri = ui.res->itemText( index );
    if ( re.indexIn( stri ) >= 0 )
    {
        QString w  = re.cap( 1 );
        QString h  = re.cap( 2 );
        int width  = w.toInt();
        int height = h.toInt();
        return QSize( width, height );
    }
    return QSize( 80, 60 );
}





