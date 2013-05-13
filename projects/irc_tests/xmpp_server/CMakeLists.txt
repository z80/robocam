
find_package( Qt4 )
set( QT_USE_QTCORE     True )
include( ${QT_USE_FILE} )

include_directories( "./src" 
                     "${ROOT}/peer_abst/src" 
                     "${ROOT}/peer_qxmpp/src"
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

add_executable( xmpp_server ${src} )
set( libs peer_qxmpp 
          ${QT_LIBRARIES} ) 
target_link_libraries( xmpp_server ${libs} )
install( TARGETS xmpp_server DESTINATION "./" )
install( DIRECTORY "./src_lua/" DESTINATION "./" )



