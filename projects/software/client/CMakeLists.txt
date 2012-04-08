
find_package( Qt4 )
set( QT_USE_QTMAIN True )
set( QT_USE_QTCORE True )
set( QT_USE_QTGUI  True )
if ( WIN32 )
    set( QT_USE_QTMAIN True )
endif ( WIN32 )
include( ${QT_USE_FILE} )

#message( STATUS ">>>>>> before custom command" )
#message( STATUS ${ICE_GEN_FILE} )
#message( STATUS ${ICE_GEN_PATH} )
#message( STATUS ${ICE_SLICE_PATH} )
#message( STATUS ${ICE_SLICE_INC} )
#add_custom_command(
#    OUTPUT   ${ICE_GEN_FILE}
#    COMMAND  ${ICE_SLICE_PATH}/slice2cppe -I${ICE_SLICE_INC} interface.ice
#    WORKING_DIRECTORY ${ICE_GEN_PATH}
#    COMMENT "Generating Ice files!!!" )
#message( STATUS ">>>>>> after custom command" )

include_directories( "./src" 
                     "./src/analogpad"
                     ${ICEE_PATH} 
                     ${CMAKE_CURRENT_BINARY_DIR} )
if ( WIN32 )
    include_directories( "../ice/win" )
elseif ( UNIX )
    include_directories( "../ice/unix" )
endif ( WIN32 )

if ( WIN32 )
    include_directories( ${BOOST_PATH} )
endif ( WIN32 )

aux_source_directory( "./src" src )
aux_source_directory( "./src/analogpad" apsrc )
list( APPEND src ${apsrc} )

#list( APPEND src ${ICE_GEN_FILE} )
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

#QT4_WRAP_CPP( moc_src "./src/client_gui.h" )
#QT4_WRAP_CPP( moc_src "./src/camera_ctrl.h" )

QT4_WRAP_CPP( moc_src "./src/main_wnd.h" )
QT4_WRAP_CPP( moc_src "./src/connect.h" )
QT4_WRAP_CPP( moc_src "./src/client_list.h" )
QT4_WRAP_CPP( moc_src "./src/chat.h" )
QT4_WRAP_CPP( moc_src "./src/camera.h" )
QT4_WRAP_CPP( moc_src "./src/moto.h" )
QT4_WRAP_CPP( moc_src "./src/sudo.h" )
QT4_WRAP_CPP( moc_src "./src/analogpad/analogpad.h" )
list( APPEND src ${moc_src} )

#list( APPEND ui "./src/client_gui.ui" )
#list( APPEND ui "./src/passwd_dlg.ui" )

list( APPEND ui "./src/main_wnd.ui" )
list( APPEND ui "./src/connect.ui" )
list( APPEND ui "./src/client_list.ui" )
list( APPEND ui "./src/chat.ui" )
list( APPEND ui "./src/camera.ui" )
list( APPEND ui "./src/moto.ui" )
list( APPEND ui "./src/sudo.ui" )
QT4_WRAP_UI( ui_src ${ui} )
list( APPEND src ${ui_src} )

QT4_ADD_RESOURCES( qrc_src "./src/images.qrc" )
list( APPEND src ${qrc_src} )

if ( WIN32 )
    set( BLD_TYPE WIN32 )
elseif ( UNIX )
    set( BLD_TYPE "" )
endif (WIN32)

add_executable( client ${BLD_TYPE} ${src} )
set_property( TARGET client PROPERTY COMPILE_DEFINITIONS ICEE_STATIC_LIBS )
list( APPEND libs debug ${iceed} optimized ${icee} ${QT_LIBRARIES} )
# ${iceec} 
if ( WIN32 )
    list( APPEND libs ${rpcrt4} ${ws2_32} ) 
    # ${advapi32} 
endif ( WIN32 )
target_link_libraries( client ${libs} )

install( TARGETS client DESTINATION "." )

