
set( Boost_USE_STATIC_LIBS True )
set( Boost_USE_MULTITHREADED True )
find_package( Boost COMPONENTS thread filesystem REQUIRED )
find_package( Threads )

include_directories( "./src" 
                     ${ROOT}/3dparty/libircclient-1.6/include 
                     ${ROOT}/3dparty/gloox-1.0/src 
                     ${ROOT}/3dparty/lua-5.1.5/src 
                     ${ROOT}/3dparty/lua-5.1.5/etc 
                     ${Boost_INCLUDE_DIRS} 
                     ${CMAKE_CURRENT_BINARY_DIR} )

file( GLOB src     "./src/*.cpp" )
file( GLOB headers "./src/*.h" )
file( GLOB ui      "./src/*.ui" )
file( GLOB qrc     "./src/*.qrc" )
message( STATUS "SRC = ${src}" )
message( STATUS "HEADERS = ${headers}" )
message( STATUS ${Boost_LIBRARIES} )

add_library( ircctrl STATIC ${src} )
find_library( libircclient NAMES libircclient.a libircclient.lib PATHS ${ROOT}/3dparty/libircclient-1.6/src ${ROOT}/3dparty/libircclient-1.6/bin )
find_library( libgloox NAMES libgloox.a libgloox.lib PATHS ${ROOT}/3dparty/gloox-1.0/src/.libs )
target_link_libraries( ircctrl liblua-5.1.5 ${libircclient} ${libgloox} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} )




