INCLUDE (FindPackageHandleStandardArgs)

FIND_PATH (VPX_ROOT_DIR
  NAMES vpx/vp8.h include/vpx/vp8.h
  PATHS ENV CRYPTOPPROOT
  DOC "Vpx root directory")

FIND_PATH (VPX_INCLUDE_DIRS
  NAMES vpx/vp8.h
  HINTS ${VPX_ROOT_DIR}
  PATH_SUFFIXES include
  DOC "Vpx include directory")

FIND_LIBRARY (VPX_LIBRARIES
  NAMES vpx
  HINTS ${VPX_ROOT_DIR}
  PATH_SUFFIXES lib
  DOC "Vpx library")
  
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Vpx REQUIRED_VARS VPX_ROOT_DIR VPX_INCLUDE_DIRS VPX_LIBRARIES)