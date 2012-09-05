
cmake_minimum_required( VERSION 2.6 )
project( "ircio" )
set( ROOT ${CMAKE_CURRENT_SOURCE_DIR} )
add_subdirectory( "./3dparty" )
add_subdirectory( "./ircctrl" )
add_subdirectory( "./test" )
