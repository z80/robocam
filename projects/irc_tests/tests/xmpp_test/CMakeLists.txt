
find_package( Qt4 )
set( QT_USE_QTCORE     True )
set( QT_USE_QTGUI      True )
include( ${QT_USE_FILE} )

find_package( Boost )

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
#find_library( libresolv NAMES libresolv.a PATHS $ENV{PATH} )
#find_library( libssl    NAMES libssl.a    PATHS $ENV{PATH} )
#find_library( libcrypto NAMES libcrypto.a PATHS $ENV{PATH} )
#find_library( libz      NAMES libz.a      PATHS $ENV{PATH} )
target_link_libraries( xmpp_test ircctrl ${QT_LIBRARIES} )
#${libresolv} ${libresolv} ${libssl} ${libcrypto} ${libz} )



