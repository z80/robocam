
find_package( Qt4 )
set( QT_USE_QTGUI   True )
set( QT_USE_QTNETWORK True )
if ( WIN32 )
    set( QT_USE_QTMAIN True )
endif ( WIN32 )
include( ${QT_USE_FILE} )

include_directories( "./src"
                     "../lib-qslog/src"
                     ${CMAKE_CURRENT_BINARY_DIR} )

aux_source_directory( "./src" src )

QT4_WRAP_CPP( moc_src "./src/proxy.h" )
list( APPEND src ${moc_src} )
QT4_WRAP_CPP( moc_src "./src/tray.h" )
list( APPEND src ${moc_src} )

QT4_ADD_RESOURCES( moc_src "./src/images.qrc" )
list( APPEND src ${moc_src} )

if ( WIN32 )
    set( BLD_TYPE WIN32 )
elseif ( UNIX )
    set( BLD_TYPE "" )
endif (WIN32)

add_executable( proxy ${BLD_TYPE} ${src} )
list( APPEND libs ${QT_LIBRARIES} libqslog )
target_link_libraries( proxy ${libs} )

install( TARGETS proxy DESTINATION "." )


