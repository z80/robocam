
include_directories( "./src" 
                     "${ROOT}/mcuctrl/src" )

file( GLOB src     "./src/*.cpp" )
file( GLOB headers "./src/*.h" )
message( STATUS "SRC = ${src}" )
message( STATUS "HEADERS = ${headers}" )

add_executable( mcuctrl_test ${src} )
set( libs mcuctrl )
message( STATUS "LIBS0 = ${libs}" )
set( defs QXMPP_STATIC )
set( libs ${libs} )
message( STATUS "LIBS1 = ${libs}" )
target_link_libraries( mcuctrl_test ${libs} )
set_property( TARGET mcuctrl_test PROPERTY COMPILE_DEFINITIONS ${defs} )




