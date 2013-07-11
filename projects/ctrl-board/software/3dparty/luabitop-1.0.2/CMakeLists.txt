
include_directories( "./" 
                     "${ROOT}/3dparty/lua-5.1.5/src" )

file( GLOB src     "./*.c" )
message( STATUS "Project \"bit\"" )
message( STATUS "SRC = ${src}" )

list( APPEND defs "DECLSPEC" )

add_library( bit STATIC ${src} )
set_property( TARGET bit PROPERTY COMPILE_DEFINITIONS ${defs} )
set_property( TARGET bit PROPERTY OUTPUT_NAME "bit" )
set_target_properties( bit PROPERTIES PREFIX "" )
target_link_libraries( bit liblua-5.1.5 )

install( TARGETS bit DESTINATION "./" )


