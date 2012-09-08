cmake_minimum_required (VERSION 2.6)

set (PROJECT property_tree)

set (HEADERS)

set (SOURCES 
	../main.cpp)

set (LIBRARIES)

set (BOOST_COMPONENTS)

set (Boost_USE_STATIC_LIBS ON)

set (Boost_USE_MULTITHREADED ON)

project (${PROJECT})

include_directories (../)

find_package (Threads)

find_package (Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

foreach (LIBRARY ${LIBRARIES})
	add_subdirectory (../${LIBRARY}/build bin/${LIBRARY})
endforeach ()

if (MSVC)
	add_definitions (/W3)
elseif (CMAKE_COMPILER_IS_GNUCXX)
	add_definitions (-Wall -pedantic)
else ()
	message ("Unknown compiler")
endif ()

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT} ${HEADERS} ${SOURCES})

target_link_libraries (${PROJECT} ${LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})

enable_testing ()
