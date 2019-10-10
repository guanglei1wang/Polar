set(OSI_ROOT_DIR "$ENV{OSI_ROOT_DIR}" CACHE PATH "OSI root directory.")
message("Looking for OSI in ${OSI_ROOT_DIR} folder")

find_path(OSI_INCLUDE_DIR  
  NAMES OsiPresolve.hpp
  HINTS ${OSI_ROOT_DIR}/include/osi/coin/
)

find_library(OSI_LIBRARY
  NAMES libOsi.dylib
  HINTS ${OSI_ROOT_DIR}/lib/
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OSI DEFAULT_MSG OSI_LIBRARY OSI_INCLUDE_DIR)

if(OSI_FOUND)
    message("—- Found OSI under ${OSI_INCLUDE_DIR}")
    set(OSI_INCLUDE_DIRS ${OSI_INCLUDE_DIR})
    set(OSI_LIBRARIES ${OSI_LIBRARY}  ${OSI_ROOT_DIR}/lib)
    link_directories(${OSI_ROOT_DIR}/lib/)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(OSI_LIBRARIES "${OSI_LIBRARIES};m;pthread")
    endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
endif(OSI_FOUND)

mark_as_advanced(OSI_LIBRARY OSI_INCLUDE_DIR)
