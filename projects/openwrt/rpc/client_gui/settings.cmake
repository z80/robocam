

set( CMAKE_INSTALL_PREFIX ${INSTALL_PATH} )

if ( UNIX )
    include( "./settings_unix.cmake" )
    set( ICE_PATH_BIN   ../../build/icee/cpp/bin )
    set( ICE_INC_PATH   ../../build/icee/cppe/include )
    set( ICE_LIB        ../../build/icee/cppe/lib )
    set( ICE_SLICE_INC  ../../build/icee/slice )
    set( ICE_SLICE_PATH ../../build/icee/cpp/bin )
elseif ( WIN32 )
    include( "./settings_win32.cmake" )
    set( ICE_PATH_BIN ${ICE_PATH}/bin )
    set( ICE_INC_PATH ${ICE_PATH}/include )
    set( ICE_LIB      ${ICE_PATH}/lib )
    set( ICE_SLICE_PATH ${ICE_PATH}/bin )
    set( ICE_SLICE_INC  ${ICE_PATH}/slice )
endif ( UNIX )

set( ICE_GEN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../common/interface.cpp )
set( ICE_GEN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../common )


find_library( libIceE  NAMES libIceE
                             libIceE.a PATHS ${ICE_LIB} $ENV{PATH} )
find_library( libIceEC NAMES libIceEC
                             libIceEC.a PATHS ${ICE_LIB} $ENV{PATH} )


