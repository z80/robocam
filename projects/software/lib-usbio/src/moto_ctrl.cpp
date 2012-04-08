
#include "moto_ctrl.h"
#include <sstream>

CMotoCtrl::CMotoCtrl()
: CUsbIo(),
  m_motoEn( false ),
  m_servoEn( false )
{
}

CMotoCtrl::~CMotoCtrl()
{
}

void CMotoCtrl::setMotoEn( bool en )
{
    std::ostringstream os;
    os << "setMotoEn " << ( en ? 1 : 0 );
    std::string cmd = os.str();
    if ( io( cmd, m_res ) > 0 )
        m_motoEn = en;
}

bool CMotoCtrl::motoEn() const
{
    return m_motoEn;
}

void CMotoCtrl::setMoto( int dir1, int dir2 )
{
    std::ostringstream os;
    os << "setMoto " << dir1 << " " << dir2;
    std::string cmd = os.str();
    io( cmd, m_res );
}

void CMotoCtrl::setServoEn( bool en )
{
    std::ostringstream os;
    os << "setServoEn " << (en ? 1 : 0);
    std::string cmd = os.str();
    if ( io( cmd, m_res ) > 0 )
        m_servoEn = en;
}

bool CMotoCtrl::servoEn() const
{
    return m_servoEn;
}

void CMotoCtrl::setServo( int val1, int val2 )
{
    std::ostringstream os;
    os << "setServo " << val1 << " " << val2;
    std::string cmd = os.str();
    io( cmd, m_res );
}

void CMotoCtrl::setWatchdog( int period )
{
    std::ostringstream os;
    os << "setWatchdog " << period;
    std::string cmd = os.str();
    io( cmd, m_res );
}

void CMotoCtrl::resetWatchdog()
{
    std::ostringstream os;
    os << "resetWatchdog";
    std::string cmd = os.str();
    io( cmd, m_res );
}





