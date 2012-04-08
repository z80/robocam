
find_package( Qt4 )
set( QT_USE_QTCORE True )
include( ${QT_USE_FILE} )

include_directories( "./src"
                     ${CMAKE_CURRENT_BINARY_DIR} )
aux_source_directory( "./src" src )

add_library( libqslog ${src} )


