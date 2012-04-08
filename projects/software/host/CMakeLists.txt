

find_package( Qt4 )
set( QT_USE_QTCORE True )
set( QT_USE_QTGUI  True )
if ( WIN32 )
    set( QT_USE_QTMAIN True )
endif ( WIN32 )
include( ${QT_USE_FILE} )

include_directories( "./src"
                     "../lib-ijg/src"
                     "../lib-qslog/src"
                     ${ICEE_PATH} 
                     ${CMAKE_CURRENT_BINARY_DIR} )
if ( WIN32 )
    include_directories( "../ice/win" )
elseif ( UNIX )
    include_directories( "../ice/unix" )
endif ( WIN32 )


aux_source_directory( "./src" src )
if ( WIN32 )
    list( APPEND src "../ice/win/types.cpp" )
    list( APPEND src "../ice/win/host.cpp" )
    list( APPEND src "../ice/win/client.cpp" )
    list( APPEND src "../ice/win/hdw.cpp" )
elseif ( UNIX )
    list( APPEND src "../ice/unix/types.cpp" )
    list( APPEND src "../ice/unix/host.cpp" )
    list( APPEND src "../ice/unix/client.cpp" )
    list( APPEND src "../ice/unix/hdw.cpp" )
endif ( WIN32 )

#QT4_WRAP_UI( ui_src "./src/usb_ctrl.ui" )
#list( APPEND src ${ui_src} )

QT4_WRAP_CPP( moc_src "./src/host_tray.h" )
list( APPEND src ${moc_src} )

QT4_WRAP_CPP( moc_src "./src/cam_thread_eml.h" )
list( APPEND src ${moc_src} )

QT4_WRAP_CPP( moc_src "./src/cam_thread_hdw.h" )
list( APPEND src ${moc_src} )

QT4_WRAP_CPP( moc_src "./src/moto_thread_hdw.h" )
list( APPEND src ${moc_src} )

QT4_ADD_RESOURCES( qrc_src "./src/images.qrc" )
list( APPEND src ${qrc_src} )


if ( WIN32 )
    set( BLD_TYPE WIN32 )
elseif ( UNIX )
    set( BLD_TYPE "" )
endif (WIN32)

add_executable( host ${BLD_TYPE} ${src} )
set_property( TARGET host PROPERTY COMPILE_DEFINITIONS ICEE_STATIC_LIBS )
list( APPEND libs debug ${iceed} optimized ${icee} ${QT_LIBRARIES} ijg )
# ${iceec} 
if ( WIN32 )
    list( APPEND libs ${rpcrt4} ${ws2_32} ) 
    # ${advapi32} 
endif ( WIN32 )
target_link_libraries( host ${libs} libqslog )

install( TARGETS host DESTINATION "." )


