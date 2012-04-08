
include_directories( "./src" )

aux_source_directory( "./src" src )

add_library( ijg STATIC ${src} )


