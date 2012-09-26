
find_package( Qt4 )
set( QT_USE_QTCORE     True )
set( QT_USE_QTGUI      True )
include( ${QT_USE_FILE} )

set( Boost_USE_STATIC_LIBS True )
set( Boost_USE_MULTITHREADED True )
find_package( Boost COMPONENTS thread filesystem date_time REQUIRED )
find_package( Threads )

include_directories( "./src" 
                     ${ROOT}/ircctrl/src 
                     ${ROOT}/3dparty/gloox-1.0/src 
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

add_executable( xmpp_test ${src} )
set( libs ${QT_LIBRARIES} ${Boost_LIBRARIES} )
if ( WIN32 )
    find_library( libglooxd NAMES gloox.lib PATHS ${ROOT}/3dparty/gloox-1.0/Debug )
    find_library( libglooxr NAMES gloox.lib PATHS ${ROOT}/3dparty/gloox-1.0/Release )
    set( libs ${libs} debug ${libglooxd} optimized ${libglooxr} )
else ( WIN32 )
    find_library( libgloox NAMES libgloox.so PATHS ${ROOT}/3dparty/gloox-1.0/src/.libs )
    set( libs ${libs} ${libgloox} )
endif ( WIN32 )
target_link_libraries( xmpp_test ${libs} )



