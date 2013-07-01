
set( PROJ_NAME host )

find_package( Qt4 )
set( QT_USE_QTCORE     True )
set( QT_USE_QTGUI      True )
set( QT_USE_QTNETWORK  True )
set( QT_USE_QTXML      True )
include( ${QT_USE_FILE} )

find_package( Boost )

include_directories( ./src 
                     ${ROOT}/3dparty/qxmpp/src/base 
                     ${ROOT}/3dparty/qxmpp/src/client 
                     ${ROOT}/3dparty/qxmpp/src/server 
                     ${ROOT}/xmpp_io/src 
                     ${ROOT}/3dparty/lua-5.1.5/src 
                     ${ROOT}/3dparty/lua-5.1.5/etc 
                     ${Boost_INCLUDE_DIRS} 
                     ${CMAKE_CURRENT_BINARY_DIR} )
if ( UNIX )
    include_directories( ${ROOT}/luactrlboard/src
                         ${ROOT}/ctrlboard/src )
endif ( UNIX )

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
set( libs liblua-5.1.5 
          qxmpp
          xmpp_io 
          liblua-5.1.5 
          ${QT_LIBRARIES} )
if ( UNIX )
    set( defs LUA_CTRL_BOARD )
    set( libs ${libs} 
              luactrlboard )
endif ( UNIX )
target_link_libraries( ${PROJ_NAME} ${libs} )
set_property( TARGET ${PROJ_NAME} PROPERTY COMPILE_DEFINITIONS ${defs} )

install( TARGETS ${PROJ_NAME} DESTINATION "./" )
install( DIRECTORY "./src_lua/" DESTINATION "./" )



