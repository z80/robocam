
set( PROJ_NAME client )

find_package( Qt4 )
set( QT_USE_QTCORE    True )
set( QT_USE_QTGUI     True )
set( QT_USE_QTUITOOLS True )
set( QT_USE_NETWORK   True )
set( QT_USE_XML       True )
if ( WIN32 )
    set( QT_USE_QTMAIN True )
endif ( WIN32 )
include( ${QT_USE_FILE} )

set( Boost_USE_STATIC_LIBS True )
set( Boost_USE_MULTITHREADED True )
find_package( Boost COMPONENTS thread filesystem REQUIRED )
find_package( Threads )

include_directories( "./src" 
                     ${ROOT}/3dparty/qxmpp/src/base 
                     ${ROOT}/3dparty/qxmpp/src/client 
                     ${ROOT}/3dparty/qxmpp/src/server 
                     ${ROOT}/xmpp_io/src 
                     ${ROOT}/3dparty/lua-5.1.5/src 
                     ${ROOT}/3dparty/lua-5.1.5/etc   
                     ${ROOT}/3dparty/qtlua-1.4/src  
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

if ( WIN32 )
    set( BUILD_TYPE WIN32 )
else ( WIN32 )
    set( BUILD_TYPE "" )
endif ( WIN32 )

add_executable( ${PROJ_NAME} ${BUILD_TYPE} ${src} )
target_link_libraries( ${PROJ_NAME} qxmpp xmpp_io liblua-5.1.5 qtlua ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${QT_LIBRARIES} )
install( TARGETS ${PROJ_NAME} DESTINATION "." )
install( DIRECTORY "./src_ini/" DESTINATION "." )

