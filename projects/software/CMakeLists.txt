
project( remote_ctrl )
cmake_minimum_required(VERSION 2.8)
if ( WIN32 )
    include( "./settings.win32.cmake" )
elseif ( UNIX )
    include( "./settings.unix.cmake" )
endif ( WIN32 )
set( CMAKE_INSTALL_PREFIX ./app )

find_library( icee   NAMES icee_static.lib 
                           libIceE.a PATHS ${ICE_LIB_PATH} $ENV{PATH} )
find_library( iceec  NAMES iceec_static.lib 
                           libIceEC.a PATHS ${ICE_LIB_PATH} $ENV{PATH} )
find_library( iceed  NAMES icee_staticd.lib 
                           libIceE.a PATHS ${ICE_LIB_PATH} $ENV{PATH} )
find_library( iceecd NAMES iceec_staticd.lib 
                           libIceEC.a PATHS ${ICE_LIB_PATH} $ENV{PATH} )
message( STATUS $ENV{PATH} )
if ( WIN32 )
    find_library( rpcrt4   NAMES rpcrt4.lib   PATHS  $ENV{PATH} "./3dparty" )
    find_library( ws2_32   NAMES ws2_32.lib   PATHS  $ENV{PATH} "./3dparty" )
elseif ( UNIX )
    #find_library( pthread NAMES libpthread.a PATHS ${ICE_LIB_PATH} $ENV{PATH} )
    #find_library( rt      NAMES librt.a PATHS ${ICE_LIB_PATH} $ENV{PATH} )
    if ( CROSS )
        find_library( iceeEmb   NAMES libIceE.a    PATHS ${ICE_LIB_PATH_EMB} $ENV{PATH} )
        find_library( iceecEmb  NAMES libIceEC.a   PATHS ${ICE_LIB_PATH_EMB} $ENV{PATH} )
        find_library( iceedEmb  NAMES libIceE.a    PATHS ${ICE_LIB_PATH_EMB} $ENV{PATH} )
        find_library( iceecdEmb NAMES libIceEC.a   PATHS ${ICE_LIB_PATH_EMB} $ENV{PATH} )
    endif ( CROSS )
endif ( WIN32 )

add_subdirectory( "./host" )
add_subdirectory( "./client" )
add_subdirectory( "./hdw" )
add_subdirectory( "./proxy" )

add_subdirectory( "./lib-ijg" )
add_subdirectory( "./lib-usbio" )
add_subdirectory( "./lib-v4l" )
add_subdirectory( "./lib-qslog" )

