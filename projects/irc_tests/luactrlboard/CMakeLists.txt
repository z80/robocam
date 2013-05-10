
find_package( Qt4 )
set( QT_USE_QT_CORE True )
include( ${QT_USE_FILE} )

include_directories( "./src" 
                     "${ROOT}/3dparty/lua-5.1.5/src" 
                     "${ROOT}/ctrlboard/src" )

aux_source_directory( "./src" src )
#add_library( luamcuctrl SHARED ${src} )
#if ( WIN32 )
#   list( APPEND defs "DECLSPEC=__declspec(dllexport)" )
#endif ( WIN32 )
add_library( luactrlboard STATIC ${src} )
set_property( TARGET luactrlboard PROPERTY COMPILE_DEFINITIONS ${defs} )
set_property( TARGET luactrlboard PROPERTY OUTPUT_NAME "luactrlboard" )
set_target_properties( luactrlboard PROPERTIES PREFIX "" )
target_link_libraries( luactrlboard liblua-5.1.5 ctrlboard )

#install( TARGETS luactrlboard DESTINATION "./" )



