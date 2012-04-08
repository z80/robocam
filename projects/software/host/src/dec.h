
#ifndef __DEC_H_
#define __DEC_H_

#include <QtGui>
#include "types.h"

class CDec
{
public:
    CDec();
    CDec( int width, int height );
    ~CDec();
    CDec( const CDec & inst );
    const CDec & operator=( const CDec & inst );
    bool decodeYuyv( const ::Types::TByteArray & raw, QImage & img );
    bool decodePjpg( const ::Types::TByteArray & raw, QImage & img );

    bool encodePng( const QImage & img, ::Types::TByteArray & data );
private:
    void verifySize( QImage & img );
    int verifyDhtTable( const ::Types::TByteArray & raw );
    int m_width, 
        m_height;

    QByteArray m_data;
    QByteArray m_rawJpg;
};





#endif


