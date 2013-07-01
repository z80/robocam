
set( OPENCV_PATH  "c:/projects/gui_git/gui/3dparty/opencv" )
set( PL_SDK       "c:/projects/gui_git/gui/3dparty/platformsdk/Windows/v7.0" )

include_directories( 
    "${OPENCV_PATH}/include" 
                   )

find_library( libcored  NAMES opencv_core220d.lib  libopencv_core220d.a  PATHS "${OPENCV_PATH}/lib" )
find_library( libcore   NAMES opencv_core220.lib   libopencv_core220.a   PATHS "${OPENCV_PATH}/lib" )
find_library( libvideod NAMES opencv_video220d.lib libopencv_video220d.a PATHS "${OPENCV_PATH}/lib" )
find_library( libvideo  NAMES opencv_video220.lib  libopencv_video220.a  PATHS "${OPENCV_PATH}/lib" )
find_library( libcalib3dd NAMES opencv_calib3d220d.lib libopencv_calib3d220d.a PATHS "${OPENCV_PATH}/lib" )
find_library( libcalib3d  NAMES opencv_calib3d220.lib  libopencv_calib3d220.a  PATHS "${OPENCV_PATH}/lib" )
find_library( libcontribd NAMES opencv_contrib220d.lib libopencv_contrib220d.a PATHS "${OPENCV_PATH}/lib" )
find_library( libcontrib  NAMES opencv_contrib220.lib  libopencv_contrib220.a  PATHS "${OPENCV_PATH}/lib" )
find_library( libfeatures2dd NAMES opencv_features2d220d.lib libopencv_features2d220d.a PATHS "${OPENCV_PATH}/lib" )
find_library( libfeatures2d  NAMES opencv_features2d220.lib  libopencv_features2d220.a  PATHS "${OPENCV_PATH}/lib" )
find_library( libflannd NAMES opencv_flann220d.lib libopencv_flann220d.a PATHS "${OPENCV_PATH}/lib" )
find_library( libflann  NAMES opencv_flann220.lib  libopencv_flann220.a  PATHS "${OPENCV_PATH}/lib" )
find_library( libgpud NAMES opencv_gpu220d.lib libopencv_gpu220d.a PATHS "${OPENCV_PATH}/lib" )
find_library( libgpu  NAMES opencv_gpu220.lib  libopencv_gpu220.a  PATHS "${OPENCV_PATH}/lib" )
find_library( libhighguid NAMES opencv_highgui220d.lib libopencv_highgui220d.a PATHS "${OPENCV_PATH}/lib" )
find_library( libhighgui  NAMES opencv_highgui220.lib  libopencv_highgui220.a  PATHS "${OPENCV_PATH}/lib" )
find_library( libimgprocd NAMES opencv_imgproc220d.lib libopencv_imgproc220d.a PATHS "${OPENCV_PATH}/lib" )
find_library( libimgproc  NAMES opencv_imgproc220.lib  libopencv_imgproc220.a  PATHS "${OPENCV_PATH}/lib" )
find_library( liblegacyd NAMES opencv_legacy220d.lib libopencv_legacy220d.a PATHS "${OPENCV_PATH}/lib" )
find_library( liblegacy  NAMES opencv_legacy220.lib  libopencv_legacy220.a  PATHS "${OPENCV_PATH}/lib" )
find_library( libmld NAMES opencv_ml220d.lib libopencv_ml220d.a PATHS "${OPENCV_PATH}/lib" )
find_library( libml  NAMES opencv_ml220.lib  libopencv_ml220.a  PATHS "${OPENCV_PATH}/lib" )
find_library( libobjdetectd NAMES opencv_objdetect220d.lib libopencv_objdetect220d.a PATHS "${OPENCV_PATH}/lib" )
find_library( libobjdetect  NAMES opencv_objdetect220.lib  libopencv_objdetect220.a  PATHS "${OPENCV_PATH}/lib" )
set( p3d "${OPENCV_PATH}/share/opencv/3rdparty/lib" )
find_library( libjasper  NAMES libjasper.lib  libjasper.a  PATHS ${p3d} )
find_library( libjasperd NAMES libjasperd.lib libjasperd.a PATHS ${p3d} )
find_library( libjpeg  NAMES libjpeg.lib  libjpeg.a  PATHS ${p3d} )
find_library( libjpegd NAMES libjpegd.lib libjpegd.a PATHS ${p3d} )
find_library( libpng  NAMES libpng.lib  libpng.a  PATHS ${p3d} )
find_library( libpngd NAMES libpngd.lib libpngd.a PATHS ${p3d} )
find_library( libtiff  NAMES libtiff.lib  libtiff.a  PATHS ${p3d} )
find_library( libtiffd NAMES libtiffd.lib libtiffd.a PATHS ${p3d} )
find_library( libzlib  NAMES zlib.lib  zlib.a  PATHS ${p3d} )
find_library( libzlibd NAMES zlibd.lib zlibd.a PATHS ${p3d} )
find_library( liblapack  NAMES opencv_lapack.lib  opencv_lapack.a  PATHS ${p3d} )
find_library( liblapackd NAMES opencv_lapackd.lib opencv_lapackd.a PATHS ${p3d} )

find_library( libvfw32 NAMES vfw32.lib vfw32.a PATHS $ENV{PATH} "${PL_SDK}/lib" )

set( libs         ${libs}        debug     ${libcored}
                                 debug     ${libvideod} 
                                 debug     ${libcalib3dd} 
                                 debug     ${libcontribd} 
                                 debug     ${libfeatures2dd} 
                                 debug     ${libflannd} 
                                 debug     ${libgpud} 
                                 debug     ${libhighguid} 
                                 debug     ${libimgprocd} 
                                 debug     ${liblegacyd} 
                                 debug     ${libmld} 
                                 debug     ${libobjdetectd} 
                                 debug     ${libjasperd} 
                                 debug     ${libjpegd} 
                                 debug     ${libpngd} 
                                 debug     ${libtiffd} 
                                 debug     ${libzlibd} 
                                 debug     ${liblapackd} 
                                 optimized ${libcore}
                                 optimized ${libvideo}
                                 optimized ${libcalib3d} 
                                 optimized ${libcontrib} 
                                 optimized ${libfeatures2d} 
                                 optimized ${libflann} 
                                 optimized ${libgpu} 
                                 optimized ${libhighgui} 
                                 optimized ${libimgproc} 
                                 optimized ${liblegacy} 
                                 optimized ${libml} 
                                 optimized ${libobjdetect} 
                                 optimized ${libjasper} 
                                 optimized ${libjpeg} 
                                 optimized ${libpng} 
                                 optimized ${libtiff} 
                                 optimized ${libzlib} 
                                 optimized ${liblapack}
                                 ${libvfw32}
                                 ${extraLibs} )



