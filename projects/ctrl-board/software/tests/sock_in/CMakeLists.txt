
set( PROJ_NAME sock_in )

find_package( Qt4 )
set( QT_USE_QTCORE     True )
set( QT_USE_QTNETWORK  True )
set( QT_USE_QTXML      True )
include( ${QT_USE_FILE} )

include_directories( "./src" 
                     "${ROOT}/3dparty/qxmpp/src/base"
                     "${ROOT}/3dparty/qxmpp/src/client"
                     "${ROOT}/3dparty/qxmpp/src/server"
		     "${ROOT}/xmpp_io/src" 
                     ${CMAKE_CURRENT_BINARY_DIR} )

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
target_link_libraries( ${PROJ_NAME} ${libs} qxmpp xmpp_io )
install( TARGETS ${PROJ_NAME} DESTINATION "./" )



