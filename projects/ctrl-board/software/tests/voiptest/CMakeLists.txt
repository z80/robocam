

set( PROJ_NAME voiptest )

if ( USE_OPENCV )
    find_package( OpenCV REQUIRED )
endif ( USE_OPENCV )

find_package( Qt4 )
set( QT_USE_QTCORE       True )
set( QT_USE_QTGUI        True )
set( QT_USE_QTNETWORK    True )
set( QT_USE_QTXML        True )
set( QT_USE_QTMULTIMEDIA True )
set( QT_USE_PHONON       True )
include( ${QT_USE_FILE} )

set( Boost_USE_STATIC_LIBS True )
set( Boost_USE_MULTITHREADED True )
find_package( Boost COMPONENTS thread filesystem REQUIRED )
find_package( Threads )

include_directories( "./src" 
                     ${ROOT}/3dparty/qxmpp/src/base 
                     ${ROOT}/3dparty/qxmpp/src/client 
                     ${ROOT}/3dparty/qxmpp/src/server 
                     ${Boost_INCLUDE_DIRS} 
                     ${CMAKE_CURRENT_BINARY_DIR} )
if ( USE_OPENCV )
    include_directories( ${OPENCV_INCLUDE_DIRS} )
endif ( USE_OPENCV )

file( GLOB src     "./src/*.cpp" )
file( GLOB headers "./src/*.h" )
file( GLOB ui      "./src/*.ui" )
file( GLOB qrc     "./src/*.qrc" )
#message( STATUS "SRC = ${src}" )
#message( STATUS "HEADERS = ${headers}" )

Qt4_WRAP_CPP( mocSrc ${headers} )
set( src ${src} ${mocSrc} )

QT4_WRAP_UI( uiSrc ${ui} )
set( src ${src} ${uiSrc} )

QT4_ADD_RESOURCES( qrcSrc ${qrc} )
set( src ${src} ${qrcSrc} )

add_executable( ${PROJ_NAME} ${src} )
set( libs qxmpp )
#message( STATUS "LIBS0 = ${libs}" )
set( libs ${libs} ${QT_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES}  )
if ( USE_OPENCV )
    set( libs ${libs} ${OpenCV_LIBS} )
endif ( USE_OPENCV )
#message( STATUS "LIBS1 = ${libs}" )
set( defs QXMPP_STATIC )

if ( WIN32 )
    include( "./win32_opencv.cmake" )
endif ( WIN32 )

target_link_libraries( ${PROJ_NAME} ${libs} )
set_property( TARGET ${PROJ_NAME} PROPERTY COMPILE_DEFINITIONS ${defs} )
install( TARGETS ${PROJ_NAME} DESTINATION "./" )



