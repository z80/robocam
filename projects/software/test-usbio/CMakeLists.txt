

find_package( Qt4 )
set( QT_USE_QTCORE True )
set( QT_USE_QTGUI  True )
if ( WIN32 )
    set( QT_USE_QTMAIN True )
endif ( WIN32 )
include( ${QT_USE_FILE} )

include_directories( "./src"
                     "../lib-usbio/src"
                     ${CMAKE_CURRENT_BINARY_DIR} )

aux_source_directory( "./src" src )
list( APPEND src ${src_libusb} )

QT4_WRAP_UI( ui_src "./src/usb_ctrl.ui" )
list( APPEND src ${ui_src} )

QT4_WRAP_CPP( moc_src "./src/usb_ctrl.h" )
list( APPEND src ${moc_src} )

QT4_ADD_RESOURCES( qrc_src "./src/images.qrc" )
list( APPEND src ${qrc_src} )


if ( WIN32 )
    set( BLD_TYPE WIN32 )
elseif ( UNIX )
    set( BLD_TYPE "" )
endif (WIN32)

add_executable(test_usbio ${BLD_TYPE} ${src} )

target_link_libraries( test_usbio usbio ${QT_LIBRARIES} )

install( TARGETS test_usbio DESTINATION "." )


