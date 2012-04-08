
if ( CROSS )
    set( CMAKE_TOOLCHAIN_FILE ../cross_openwrt.txt )
    include( ../cross_openwrt.txt )
endif ( CROSS )

if ( WIN32 )
    include_directories( "./src_windows" )
    aux_source_directory( "./src_windows" src )
else ( WIN32 )
    include_directories( "./src" )
    aux_source_directory( "./src" src )
endif ( WIN32 )

add_library( v4l STATIC ${src} )


