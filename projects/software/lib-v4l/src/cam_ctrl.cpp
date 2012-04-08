
#include "cam_ctrl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <asm/types.h>
#include <linux/videodev2.h>

#include <sstream>

#define CLEAR(x) memset (&(x), 0, sizeof (x))

class CCamCtrl::PD
{
public:
    PD() {}
    ~PD() {}
    v4l2_buffer buf;
};

CCamCtrl::CCamCtrl()
{
    pd = new PD();
    m_devName = "/dev/video0";
    m_dev     = -1;
    m_width   = -1;
    m_height  = -1;
    m_index   = -1;
    m_capture = false;
}

CCamCtrl::~CCamCtrl()
{
    CCamCtrl::close();
    delete pd;
}

void CCamCtrl::setDeviceName( const std::string & devName )
{
    m_devName = devName;
}

bool CCamCtrl::open()
{
    if ( isOpen() )
        close();
    m_dev = ::open( m_devName.data(), O_RDWR /* required */ | O_NONBLOCK );
    return (m_dev != -1);
}

void CCamCtrl::close()
{
    if ( m_dev != -1 )
    {
        if ( m_capture )
            stopCapture();
        freeBuffer();
        ::close( m_dev );
        m_dev = -1;
    }
}

bool CCamCtrl::isOpen() const
{
     return ( m_dev != -1 );
}

static int xioctl( int dev, int request, void * arg )
{
    int r;
    do
        r = ioctl( dev, request, arg );
    while (-1 == r && EINTR == errno);
    return r;
}

bool CCamCtrl::capabilities( std::vector<std::string> & cap, std::vector<bool> & en, std::vector<std::string> & info )
{
    v4l2_capability c;
    if(ioctl( m_dev, VIDIOC_QUERYCAP, &c) < 0)
    {
        std::ostringstream s;
        s <<  "Not a V4L2 device";
        info.push_back( s.str() );
        return false;
    }
    std::ostringstream s;
    s << "driver " << c.driver;
    info.push_back( s.str() );
    s.clear();
    
    s << "card " << c.card;
    info.push_back( s.str() );
    s.clear();
    
    s << "bus_info " << c.bus_info;
    info.push_back( s.str() );
    s.clear();
    
    cap.push_back( "capture" );
    en.push_back( c.capabilities & V4L2_CAP_VIDEO_CAPTURE );
    
    cap.push_back( "output" );
    en.push_back( c.capabilities & V4L2_CAP_VIDEO_OUTPUT );
    
    cap.push_back( "overlay" );
    en.push_back( c.capabilities & V4L2_CAP_VIDEO_OVERLAY );
    
    cap.push_back( "vbi_capture" );
    en.push_back( c.capabilities & V4L2_CAP_VBI_CAPTURE );
    
    cap.push_back( "vbi_output" );
    en.push_back( c.capabilities & V4L2_CAP_VBI_OUTPUT );
    
    cap.push_back( "rds_capture" );
    en.push_back( c.capabilities & V4L2_CAP_RDS_CAPTURE );
    
    cap.push_back( "cap_tuner" );
    en.push_back( c.capabilities & V4L2_CAP_TUNER );
    
    cap.push_back( "cap_audio" );
    en.push_back( c.capabilities & V4L2_CAP_AUDIO );
    
    cap.push_back( "cap_radio" );
    en.push_back( c.capabilities & V4L2_CAP_RADIO );
    
    cap.push_back( "cap_readwrite" );
    en.push_back( c.capabilities & V4L2_CAP_READWRITE );
    
    cap.push_back( "cap_asyncio" );
    en.push_back( c.capabilities & V4L2_CAP_ASYNCIO );
    
    cap.push_back( "cap_streaming" );
    en.push_back( c.capabilities & V4L2_CAP_STREAMING );
    
    cap.push_back( "cap_timeperframe" );
    en.push_back( c.capabilities & V4L2_CAP_TIMEPERFRAME );
    
    return true;
}

bool CCamCtrl::formats( std::vector<std::string> & fmt, std::vector<unsigned long> & fourcc )
{
    v4l2_fmtdesc f;
    int v4l2_pal;
    
    v4l2_pal = 0;
    memset(&f, 0, sizeof(fmt));
    f.index = v4l2_pal;
    f.type  = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    
    while(ioctl( m_dev, VIDIOC_ENUM_FMT, &f) != -1)
    {
        std::ostringstream s;
        s << f.description;
        fmt.push_back( s.str() );
        
        fourcc.push_back( f.pixelformat );
        
        memset(&f, 0, sizeof(f));
        f.index = ++v4l2_pal;
        f.type  = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    }
    
    return true;
}

std::vector<int> CCamCtrl::resolutions()
{
    return std::vector<int>();
}

bool CCamCtrl::initDevice( bool streaming, unsigned long format, 
                           int width, int height, int fps )
{
    struct v4l2_capability cap;
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;

    // Select video input, video standard and tune here.
    CLEAR( cropcap );
    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if ( 0 == xioctl( m_dev, VIDIOC_CROPCAP, &cropcap) )
    {
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect; // reset to default

        if (-1 == xioctl( m_dev, VIDIOC_S_CROP, &crop ) )
        {
            switch ( errno )
            {
                case EINVAL:
                    // Cropping not supported.
                    break;
                default:
                    // Errors ignored.
                    break;
            }
        }
    }
    else
    {
        // Errors ignored.
    }

    CLEAR (fmt);

    fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width       = width;
    fmt.fmt.pix.height      = height;
    fmt.fmt.pix.pixelformat = format;
    fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;

    if ( -1 == xioctl( m_dev, VIDIOC_S_FMT, &fmt ) )
    {
        m_msgs.push( "set video format failed" );
        return false;
    }

    // Note VIDIOC_S_FMT may change width and height.
    m_width  = fmt.fmt.pix.width;
    m_height = fmt.fmt.pix.height;

    // Buggy driver paranoia.
    /*unsigned int min;
    min = fmt.fmt.pix.width * 2;
    if ( fmt.fmt.pix.bytesperline < min )
        fmt.fmt.pix.bytesperline = min;
    min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
    if ( fmt.fmt.pix.sizeimage < min )
        fmt.fmt.pix.sizeimage = min;*/

    // Init fps.
    bool res = setFps( fps );
    usleep( 1000 * 1000 / fps * 2 );

    if ( streaming )
        res = initMMap( fmt.fmt.pix.sizeimage );
    else
    {
        m_msgs.push( "read-write not supported yet\n\r" );
        res = false;
    }
    return res;
}

bool CCamCtrl::startCapture()
{
    for ( unsigned i = 0; i <m_buffer.size(); ++i )
    {
        v4l2_buffer & buf = pd->buf;
        CLEAR(buf);
        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = i;

        if (-1 == xioctl( m_dev, VIDIOC_QBUF, &buf ) )
        {
            m_msgs.push( "VIDIOC_QBUF" );
            return false;
        }
    }
    unsigned long type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == xioctl ( m_dev, VIDIOC_STREAMON, &type ) )
    {
        m_msgs.push( "VIDIOC_STREAMON" );
        return false;
    }
    m_capture = true;
    return true;
}

void CCamCtrl::imageSize( int & width, int & height, int & bufferSz )
{
    width  = m_width;
    height = m_height;
    bufferSz = ( m_bufferSz.size() > 0 ) ? m_bufferSz[0] : 0;
}

void CCamCtrl::stopCapture()
{
    // Capture stop.
    enum v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if ( -1 == xioctl( m_dev, VIDIOC_STREAMOFF, &type ) )
        m_msgs.push( "VIDIOC_STREAMOFF" );
    m_capture = false;
}

bool CCamCtrl::started() const
{
    return m_capture;
}

bool CCamCtrl::setFps( int fps )
{
    struct v4l2_streamparm setfps;

    CLEAR( setfps );

    setfps.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    setfps.parm.capture.timeperframe.numerator   = 1;
    setfps.parm.capture.timeperframe.denominator = fps;
    if( xioctl( m_dev, VIDIOC_S_PARM, &setfps ) == -1 )
    {
        m_msgs.push( "setFps failed" );
        return false;
    }
    m_fps = fps;
    return true;
}

bool CCamCtrl::initMMap( unsigned int buffer_size )
{
    struct v4l2_requestbuffers req;
    unsigned int page_size;

    CLEAR( req );

    req.count               = 2;
    req.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory              = V4L2_MEMORY_MMAP;

    if (-1 == xioctl( m_dev, VIDIOC_REQBUFS, &req ) )
    {
        if (EINVAL == errno)
        {
            m_msgs.push( "Does not support memory map i/o" );
            return false;
        }
        else
        {
            m_msgs.push( "VIDIOC_REQBUFS" );
            return false;
        }
    }

    if ( req.count < 2 )
    {
        m_msgs.push( "Insufficient buffer memory" );
        return false;
    }

    freeBuffer();
    for ( unsigned i=0; i<req.count; i++ )
    {
        v4l2_buffer & buf = pd->buf;
        CLEAR (buf);
        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = i;

        if ( -1 == xioctl( m_dev, VIDIOC_QUERYBUF, &buf ) )
        {
            m_msgs.push( "VIDIOC_QUERYBUF" );
            return false;
        }

        void * buffer = 0;
        buffer = mmap( NULL /* start anywhere */,
                       buffer_size,
                       PROT_READ | PROT_WRITE /* required */,
                       MAP_SHARED /* recommended */,
                       m_dev, buf.m.offset );
        if ( MAP_FAILED == buffer )
        {
            m_msgs.push( "MMap failed" );
            std::ostringstream s;
            s << "buffer size: "   << buffer_size;
            m_msgs.push( s.str() );
            s.clear();
            s << "buffer offset: " << buf.m.offset;
            m_msgs.push( s.str() );
            s.clear();
            s << "buffer index: "  << i;
            m_msgs.push( s.str() );
            s.clear();
            return false;
        }
        m_buffer.push_back( buffer );
        m_bufferSz.push_back( buffer_size );
    }
    return true;
}

void CCamCtrl::freeBuffer()
{
    for ( unsigned i=0; i<m_buffer.size(); i++ )
    {
        if ( m_buffer[ i ] )
            munmap( m_buffer[ i ], m_bufferSz[ i ] );
    }
    m_buffer.clear();
    m_bufferSz.clear();
}

bool CCamCtrl::acquire()
{
    v4l2_buffer & buf = pd->buf;
    CLEAR( buf );

    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    if ( -1 == xioctl( m_dev, VIDIOC_DQBUF, &buf ) )
    {
        switch ( errno )
        {
        case EAGAIN:
            m_msgs.push( "readFrame: EAGAIN" );
            return false;

        case EIO:
            /* Could ignore EIO, see spec. */
            /* fall through */
            m_msgs.push( "readFrame: EIO" );
            return false;
        default:
            m_msgs.push( "VIDIOC_DQBUF" );
            return false;
        }
    }
    m_index = buf.index;
    if( buf.index >= m_buffer.size() )
        return false;
    return true;
}

bool CCamCtrl::release()
{
    v4l2_buffer & buf = pd->buf;
    if ( -1 == xioctl( m_dev, VIDIOC_QBUF, &buf ) )
    {
        m_msgs.push( "VIDIOC_QBUF" );
        return false;
    }
    return true;
}

void CCamCtrl::data( int from, int sz, std::vector<unsigned char> & out )
{
    unsigned char * data = (unsigned char *)( m_buffer[ m_index ] );
    out.clear();
    out.reserve( sz );
    int to = from + sz;
    to = ( to <= m_bufferSz[ m_index ] ) ? to : m_bufferSz[ m_index ];
    for ( int i=from; i<to; i++ )
        out.push_back( data[i] );
}

std::string CCamCtrl::lastError()
{
    std::string res;
    if ( m_msgs.size() > 0 )
    {
        res = m_msgs.front();
        m_msgs.pop();
    }
    else
        res = "";
    return res;
}


/*
static bool initMmap()
{
    struct v4l2_requestbuffers req;
    CLEAR( req );
    req.count  = 4;
    req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (-1 == xioctl( m_dev, VIDIOC_REQBUFS, &req ) )
    {
        if (EINVAL == errno)
        {
            fprintf (stderr, "%s does not support "
                              "memory mapping\n", dev_name);
                        exit (EXIT_FAILURE);
                } else {
                        errno_exit ("VIDIOC_REQBUFS");
                }
        }

        if (req.count < 2) {
                fprintf (stderr, "Insufficient buffer memory on %s\n",
                         dev_name);
                exit (EXIT_FAILURE);
        }

        buffers = calloc (req.count, sizeof (*buffers));

        if (!buffers) {
                fprintf (stderr, "Out of memory\n");
                exit (EXIT_FAILURE);
        }

        for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
                struct v4l2_buffer buf;

                CLEAR (buf);

                buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                buf.memory      = V4L2_MEMORY_MMAP;
                buf.index       = n_buffers;

                if (-1 == xioctl (fd, VIDIOC_QUERYBUF, &buf))
                        errno_exit ("VIDIOC_QUERYBUF");

                buffers[n_buffers].length = buf.length;
                buffers[n_buffers].start =
                        mmap (NULL,  // start anywhere
                              buf.length,
                              PROT_READ | PROT_WRITE, // required
                              MAP_SHARED, // recommended
                              fd, buf.m.offset);

                if (MAP_FAILED == buffers[n_buffers].start)
                        errno_exit ("mmap");
        }
}

static void
init_userp			(unsigned int		buffer_size)
{
    struct v4l2_requestbuffers req;
        unsigned int page_size;

        page_size = getpagesize ();
        buffer_size = (buffer_size + page_size - 1) & ~(page_size - 1);

        CLEAR (req);

        req.count               = 4;
        req.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        req.memory              = V4L2_MEMORY_USERPTR;

        if (-1 == xioctl (fd, VIDIOC_REQBUFS, &req)) {
                if (EINVAL == errno) {
                        fprintf (stderr, "%s does not support "
                                 "user pointer i/o\n", dev_name);
                        exit (EXIT_FAILURE);
                } else {
                        errno_exit ("VIDIOC_REQBUFS");
                }
        }

        buffers = calloc (4, sizeof (*buffers));

        if (!buffers) {
                fprintf (stderr, "Out of memory\n");
                exit (EXIT_FAILURE);
        }

        for (n_buffers = 0; n_buffers < 4; ++n_buffers) {
                buffers[n_buffers].length = buffer_size;
                buffers[n_buffers].start = memalign ( // boundary
                                                      page_size,
                                                      buffer_size );

                if (!buffers[n_buffers].start) {
                fprintf (stderr, "Out of memory\n");
                    exit (EXIT_FAILURE);
        }
        }
}*/






