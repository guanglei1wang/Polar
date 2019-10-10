set(CGL_ROOT_DIR "$ENV{CGL_ROOT_DIR}" CACHE PATH "CGL root directory.")
message("Looking for CGL in ${CGL_ROOT_DIR} folder")

find_path(CGL_INCLUDE_DIR  
  NAMES CglProbing.hpp
  HINTS ${CGL_ROOT_DIR}/include/cgl/coin/
)

find_library(CGL_LIBRARY
  NAMES libCoinUtils.dylib
  HINTS ${CGL_ROOT_DIR}/lib/
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CGL DEFAULT_MSG CGL_LIBRARY CGL_INCLUDE_DIR)

if(CGL_FOUND)
    message("—- Found CGL under ${CGL_INCLUDE_DIR}")
    set(CGL_INCLUDE_DIRS ${CGL_INCLUDE_DIR})
    set(CGL_LIBRARIES ${CGL_LIBRARY}  ${CGL_ROOT_DIR}/lib)
    link_directories(${CGL_ROOT_DIR}/lib/)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(CGL_LIBRARIES "${CGL_LIBRARIES};m;pthread")
    endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
endif(CGL_FOUND)

mark_as_advanced(CGL_LIBRARY CGL_INCLUDE_DIR)
