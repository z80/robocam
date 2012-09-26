
set( Boost_USE_STATIC_LIBS True )
set( Boost_USE_MULTITHREADED True )
find_package( Boost COMPONENTS thread filesystem date_time REQUIRED )
find_package( Threads )

include_directories( "./src" 
                     ${ROOT}/3dparty/gloox-1.0/src 
                     ${Boost_INCLUDE_DIRS} 
                     ${CMAKE_CURRENT_BINARY_DIR} )

file( GLOB src     "./src/*.cpp" )
file( GLOB headers "./src/*.h" )
message( STATUS "SRC = ${src}" )
message( STATUS "HEADERS = ${headers}" )
message( STATUS ${Boost_LIBRARIES} )

add_library( peer_gloox STATIC ${src} )
set( libs ${Boost_LIBRARIES} )
if ( WIN32 )
    find_library( libglooxd NAMES gloox.lib PATHS ${ROOT}/3dparty/gloox-1.0/Debug )
    find_library( libglooxr NAMES gloox.lib PATHS ${ROOT}/3dparty/gloox-1.0/Release )
    set( libs ${libs} debug ${libglooxd} optimized ${libglooxr} )
else ( WIN32 )
    find_library( libgloox NAMES libgloox.so PATHS ${ROOT}/3dparty/gloox-1.0/src/.libs )
    set( libs ${libs} ${libgloox} )
endif ( WIN32 )
target_link_libraries( peer_gloox ${libs} )




