
find_package( Qt4 )
set( QT_USE_QTCORE     True )
include( ${QT_USE_FILE} )

set( Boost_USE_STATIC_LIBS True )
set( Boost_USE_MULTITHREADED True )
find_package( Boost COMPONENTS thread filesystem REQUIRED )
find_package( Threads )

include_directories( "./src" 
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

add_executable( qxmpp_test STATIC ${src} )
set( libs ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${QT_LIBRARIES} )
if ( WIN32 )
    find_library( qxmppd NAMES libqxmpp_d.lib PATHS ${ROOT}/3dparty/qxmpp-0.7.3/src )
    find_library( qxmpp NAMES  libqxmpp.lib PATHS ${ROOT}/3dparty/qxmpp-0.7.3/src )
    set( libs ${libs} debug ${qxmpp_d} optimized ${qxmpp} )
else ( WIN32 )
    find_library( qxmpp NAMES  libqxmpp.a PATHS ${ROOT}/3dparty/qxmpp-0.7.3/src )
    set( libs ${libs} ${qxmpp} )
endif ( WIN32 )
target_link_libraries( qxmpp_test ${libs} )




