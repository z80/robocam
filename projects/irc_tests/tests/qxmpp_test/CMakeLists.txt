
find_package( Qt4 )
set( QT_USE_QTCORE     True )
set( QT_USE_QTGUI      True )
set( QT_USE_QTNETWORK  True )
set( QT_USE_QTXML      True )
include( ${QT_USE_FILE} )

set( Boost_USE_STATIC_LIBS True )
set( Boost_USE_MULTITHREADED True )
find_package( Boost COMPONENTS thread filesystem date_time REQUIRED )
find_package( Threads )

include_directories( "./src" 
                     "${ROOT}/peer_abst/src" 
                     ${ROOT}/3dparty/lua-5.1.5/src 
                     ${ROOT}/3dparty/lua-5.1.5/etc 
                     ${ROOT}/3dparty/qxmpp-0.7.3/src/base 
                     ${ROOT}/3dparty/qxmpp-0.7.3/src/client 
                     ${ROOT}/3dparty/qxmpp-0.7.3/src/server 
                     ${Boost_INCLUDE_DIRS} 
                     ${CMAKE_CURRENT_BINARY_DIR} )

file( GLOB src     "./src/*.cpp" )
file( GLOB headers "./src/*.h" )
file( GLOB ui      "./src/*.ui" )
file( GLOB qrc     "./src/*.qrc" )
message( STATUS "SRC = ${src}" )
message( STATUS "HEADERS = ${headers}" )

Qt4_WRAP_CPP( mocSrc ${headers} )
set( src ${src} ${mocSrc} )

QT4_WRAP_UI( uiSrc ${ui} )
set( src ${src} ${uiSrc} )

QT4_ADD_RESOURCES( qrcSrc ${qrc} )
set( src ${src} ${qrcSrc} )

add_executable( qxmpp_test ${src} )
set( libs peer_abst liblua-5.1.5 qxmpp )
message( STATUS "LIBS0 = ${libs}" )
#set( defs QXMPP_STATIC )
set( libs ${libs} ${QT_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} )
message( STATUS "LIBS1 = ${libs}" )
target_link_libraries( qxmpp_test ${libs} )
set_property( TARGET qxmpp_test PROPERTY COMPILE_DEFINITIONS ${defs} )




