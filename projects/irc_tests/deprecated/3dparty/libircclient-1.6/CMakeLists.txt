
if ( WIN32 )
    file( GLOB src     "./src/*.cpp" )
    file( GLOB headers "./src/*.h" )
    message( STATUS "SRC = ${src}" )
    message( STATUS "HEADERS = ${headers}" )

    add_library( libircclient-1.6 STATIC ${src} )
#     target_link_libraries( irc_test ircctrl ${QT_LIBRARIES} )
endif ( WIN32 )

