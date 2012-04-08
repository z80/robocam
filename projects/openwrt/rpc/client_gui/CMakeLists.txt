
cmake_minimum_required( VERSION 2.6 )
include( "./settings.cmake" )
project( client )

find_package( Qt4 )
set( QT_USE_QTCORE True )
set( QT_USE_QTGUI  True )
if ( WIN32 )
    set( QT_USE_QTMAIN True )
endif ( WIN32 )
include( ${QT_USE_FILE} )

message( STATUS ">>>>>> before custom command" )
message( STATUS ${ICE_GEN_FILE} )
message( STATUS ${ICE_GEN_PATH} )
message( STATUS ${ICE_SLICE_PATH} )
message( STATUS ${ICE_SLICE_INC} )
add_custom_command(
    OUTPUT   ${ICE_GEN_FILE}
    COMMAND  ${ICE_SLICE_PATH}/slice2cppe -I${ICE_SLICE_INC} interface.ice
    WORKING_DIRECTORY ${ICE_GEN_PATH}
    COMMENT "Generating Ice files!!!" )
message( STATUS ">>>>>> after custom command" )

include_directories( "./src"
                     "../common"
                     ${BOOST_PATH}
                     ${ICE_INC_PATH}
                     ${CMAKE_CURRENT_BINARY_DIR}
                   )

aux_source_directory( "./src" src )
list( APPEND src ${ICE_GEN_FILE} )

QT4_WRAP_CPP( moc_src "./src/client_gui.h" )
QT4_WRAP_CPP( moc_src "./src/camera_ctrl.h" )
list( APPEND src ${moc_src} )

QT4_WRAP_UI( ui_src "./src/client_gui.ui" )
list( APPEND src ${ui_src} )

#QT4_ADD_RESOURCES( qrc_src "./src/images.qrc" )
#list( APPEND src ${qrc_src} )

if ( WIN32 )
    set( BLD_TYPE WIN32 )
elseif ( UNIX )
    set( BLD_TYPE "" )
endif (WIN32)

add_executable( client ${BLD_TYPE} ${src} )
target_link_libraries( client ${QT_LIBRARIES}
                              ${libIceE}
                              ${libIceEC} )

install( TARGETS client DESTINATION "." )

