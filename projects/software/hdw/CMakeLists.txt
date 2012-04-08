
if ( CROSS )
    set( CMAKE_TOOLCHAIN_FILE ../cross_openwrt.txt )
    include( ../cross_openwrt.txt )
endif ( CROSS )

include_directories( "./src"
                     "../lib-usbio/src"
                     ${CMAKE_CURRENT_BINARY_DIR} )
if ( WIN32 )
    include_directories( "../ice/win" )
elseif ( UNIX )
    include_directories( "../ice/unix" )
endif ( WIN32 )

if ( CROSS )
    include_directories( ${ICEE_PATH_EMB} )
else ( CROSS )
    include_directories( ${ICEE_PATH} )
endif ( CROSS )
if ( WIN32 )
    include_directories( "../lib-v4l/src_windows" )
else ( WIN32 )
    include_directories( "../lib-v4l/src" )
endif ( WIN32 )

aux_source_directory( "./src" src )
if ( WIN32 )
    list( APPEND src "../ice/win/types.cpp" )
    list( APPEND src "../ice/win/hdw.cpp" )
elseif ( UNIX )
    list( APPEND src "../ice/unix/types.cpp" )
    list( APPEND src "../ice/unix/hdw.cpp" )
endif ( WIN32 )

add_executable( hdw ${BLD_TYPE} ${src} )
set_property( TARGET hdw PROPERTY COMPILE_DEFINITIONS ICEE_STATIC_LIBS )
if ( CROSS )
    list( APPEND libs debug ${iceedEmb} optimized ${iceeEmb} )
else (CROSS)
    list( APPEND libs debug ${iceed} optimized ${icee} )
endif (CROSS)
list( APPEND libs usbio v4l )
if ( WIN32 )
    list( APPEND libs ${rpcrt4} ${ws2_32} ) 
elseif ( UNIX )
    list( APPEND libs pthread rt )
endif ( WIN32 )

target_link_libraries( hdw ${libs} )

install( TARGETS hdw DESTINATION "." )
install( FILES "./src/config.cfg" DESTINATION "." )
install( FILES "./src/hdw.sh"     DESTINATION "." )


