set(CBC_ROOT_DIR "$ENV{CBC_ROOT_DIR}" CACHE PATH "CBC root directory.")
message("Looking for CBC in ${CBC_ROOT_DIR} folder")

find_path(CBC_INCLUDE_DIR  
    NAMES ClpSimplex.hpp 
    HINTS ${CBC_ROOT_DIR}/include/clp/coin/
    )

find_library(CBC_LIBRARY1
    NAMES libCbc.dylib
    HINTS ${CBC_ROOT_DIR}/lib/
    )

find_library(CBC_LIBRARY1
    NAMES libOsiCbc.dylib
    HINTS ${CBC_ROOT_DIR}/lib/
    )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CBC DEFAULT_MSG CBC_LIBRARY CBC_INCLUDE_DIR)

if(CBC_FOUND)
    message("—- Found CBC under ${CBC_INCLUDE_DIR}")
    set(CBC_INCLUDE_DIRS ${CBC_INCLUDE_DIR})
    set(CBC_LIBRARIES ${CBC_LIBRARY})
    link_directories(${CBC_ROOT_DIR}/lib/)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(CBC_LIBRARIES "${CBC_LIBRARIES};m;pthread")
    endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
endif(CBC_FOUND)

mark_as_advanced(CBC_LIBRARY CBC_INCLUDE_DIR)
