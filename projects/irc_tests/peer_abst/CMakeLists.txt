
find_package( Qt4 )
set( QT_USE_QTCORE     True )
include( ${QT_USE_FILE} )

set( Boost_USE_STATIC_LIBS True )
set( Boost_USE_MULTITHREADED True )
find_package( Boost COMPONENTS thread filesystem REQUIRED )
find_package( Threads )

include_directories( "./src" 
                     ${ROOT}/3dparty/lua-5.1.5/src 
                     ${ROOT}/3dparty/lua-5.1.5/etc 
                     ${Boost_INCLUDE_DIRS} 
                     ${CMAKE_CURRENT_BINARY_DIR} )

file( GLOB src     "./src/*.cpp" )
file( GLOB headers "./src/*.h" )
message( STATUS "SRC = ${src}" )
message( STATUS "HEADERS = ${headers}" )
message( STATUS ${Boost_LIBRARIES} )

add_library( peer_abst STATIC ${src} )
target_link_libraries( peer_abst liblua-5.1.5 ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${QT_LIBRARIES} )




