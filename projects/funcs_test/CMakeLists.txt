
cmake_minimum_required( VERSION 2.6 )
project( "funcs_test" )

aux_source_directory( "./src" src )
include_directories( "./src" )

add_executable( funcs_test ${src} )

