
#ifndef __CAM_CTRL_EML_H_
#define __CAM_CTRL_EML_H_

#include "cam_ctrl.h"
#include <QtGui>
class CCamThreadEml;

class CCamCtrlEml: public CCamCtrl
{
public:
    CCamCtrlEml( CHostIceThread * owner );
	~CCamCtrlEml();

    bool isOpen();
    void setResolution( ::Ice::Int & width, ::Ice::Int & height );
	void resolution( ::Ice::Int & width, ::Ice::Int & height );
    ::Ice::Double period();
    bool image( ::Types::TByteArray & data );
    void setReceiveImages(bool en);
    bool receiveImages();
    ::std::string deviceName();
    void setPeriod(::Ice::Double value);
    void setDeviceName(const ::std::string& stri);
    bool open();
    void close();
protected:

    void postImage();

	bool m_open;
    CCamThreadEml * m_camThread;
    QImage m_img;
    QByteArray m_imgArray;
    ::Types::TByteArray m_byteArray;
    QMutex m_mut;
    // Ёмул€ци€ камеры.
    QStringList m_files;
    int         m_fileIndex;

    friend class CCamThreadEml;
};

#endif

