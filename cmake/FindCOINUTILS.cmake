set(COINUTILS_ROOT_DIR "$ENV{COINUTILS_ROOT_DIR}" CACHE PATH "COINUTILS root directory.")
message("Looking for COINUTILS in ${COINUTILS_ROOT_DIR} folder")

find_path(COINUTILS_INCLUDE_DIR  
  NAMES CoinPragma.hpp 
  HINTS ${COINUTILS_ROOT_DIR}/include/coinutils/coin/
)

find_library(COINUTILS_LIBRARY
  NAMES libCoinUtils.dylib
  HINTS ${COINUTILS_ROOT_DIR}/lib/coinutils/
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(COINUTILS DEFAULT_MSG COINUTILS_LIBRARY COINUTILS_INCLUDE_DIR)

if(COINUTILS_FOUND)
    message("—- Found COINUTILS under ${COINUTILS_INCLUDE_DIR}")
    set(COINUTILS_INCLUDE_DIRS ${COINUTILS_INCLUDE_DIR})
    set(COINUTILS_LIBRARIES ${COINUTILS_LIBRARY})
    link_directories(${COINUTILS_ROOT_DIR}/lib/)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(COINUTILS_LIBRARIES "${COINUTILS_LIBRARIES};m;pthread")
    endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
endif(COINUTILS_FOUND)

mark_as_advanced(COINUTILS_LIBRARY COINUTILS_INCLUDE_DIR)
