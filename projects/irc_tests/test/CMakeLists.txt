
find_package( Qt4 )
set( QT_USE_QTCORE     True )
set( QT_USE_QTGUI      True )
include( ${QT_USE_FILE} )

include_directories( "./src" 
                     ${ROOT}/ircctrl/src 
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

add_executable( test ${src} )
target_link_libraries( test ircctrl ${QT_LIBRARIES} )



