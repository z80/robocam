
aux_source_directory( "./src" src )
message( STATUS "src: \"${src}\"" )

include_directories( "./src" 
                     ${GLOB_BIN_DIR} )
set( src ${src} ${s} )

add_library( ctrlboard STATIC ${src} )




