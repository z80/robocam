
set( Boost_USE_STATIC_LIBS True )
set( Boost_USE_MULTITHREADED True )
find_package( Boost COMPONENTS thread filesystem REQUIRED )
find_package( Threads )

include_directories( "./src" 
                     ${ROOT}/3dparty/qxmpp-0.7.3/src 
                     ${Boost_INCLUDE_DIRS} 
                     ${CMAKE_CURRENT_BINARY_DIR} )

file( GLOB src     "./src/*.cpp" )
file( GLOB headers "./src/*.h" )
message( STATUS "SRC = ${src}" )
message( STATUS "HEADERS = ${headers}" )
message( STATUS ${Boost_LIBRARIES} )

add_library( peer_qxmpp STATIC ${src} )
set( libs ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} )
if ( WIN32 )
    find_library( qxmppd NAMES libqxmpp_d.lib PATHS ${ROOT}/3dparty/qxmpp-0.7.3/src )
    find_library( qxmpp NAMES  libqxmpp.lib PATHS ${ROOT}/3dparty/qxmpp-0.7.3/src )
    set( libs ${libs} debug ${qxmpp_d} optimized ${qxmpp} )
else ( WIN32 )
    find_library( qxmpp NAMES  libqxmpp.a PATHS ${ROOT}/3dparty/qxmpp-0.7.3/src )
    set( libs ${libs} ${qxmpp} )
endif ( WIN32 )
target_link_libraries( peer_qxmpp ${libs} )




