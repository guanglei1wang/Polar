include_directories(${PROJECT_INCLUDE_DIR})

include_directories(
  ${PROJECT_INCLUDE_DIR}/Cbc/
  ${PROJECT_INCLUDE_DIR}/Cbc/API/
  ${PROJECT_INCLUDE_DIR}/Cbc/Core/ 
  ${PROJECT_INCLUDE_DIR}/Cbc/Branch/
  ${PROJECT_INCLUDE_DIR}/Cbc/Cuts/
  ${PROJECT_INCLUDE_DIR}/Cbc/Generic/
  ${PROJECT_INCLUDE_DIR}/Cbc/Heuristics/
  ${PROJECT_INCLUDE_DIR}/Cbc/NodeStrat/
  )

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
#SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# the RPATH to be used when installing, but only if it's not a system directory
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/solvers/*.h)

file(GLOB CbcPlus_SOURCES ${PROJECT_SOURCE_DIR}/solvers/CbcPlus/*.cpp)

add_executable(CbcPlus ${CbcPlus_SOURCES} ${HEADERS})
target_link_libraries(CbcPlus polar)
