
set( PROJ_NAME xmpp_server )

find_package( Qt4 )
set( QT_USE_QTCORE     True )
set( QT_USE_QTNETWORK  True )
set( QT_USE_QTXML      True )
include( ${QT_USE_FILE} )

include_directories( "./src" 
                     "${ROOT}/3dparty/qxmpp/src/base"
                     "${ROOT}/3dparty/qxmpp/src/client"
                     "${ROOT}/3dparty/qxmpp/src/server"
                     ${CMAKE_CURRENT_BINARY_DIR} 
                     ${BOOST_INCLUDEDIR} )

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
set( libs qxmpp 
          ${QT_LIBRARIES} ) 
target_link_libraries( ${PROJ_NAME} ${libs} )

set( defs QXMPP_STATIC )
set_property( TARGET ${PROJ_NAME} PROPERTY COMPILE_DEFINITIONS ${defs} )

install( TARGETS ${PROJ_NAME} DESTINATION "./" )
install( DIRECTORY "./ini/" DESTINATION "./" )



