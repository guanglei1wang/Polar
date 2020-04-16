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


# the RPATH to be used when installing, but only if it's not a system directory file(GLOB HEADERS_LINK ${PROJECT_SOURCE_DIR}/examples/nonlinear/*.h)
file(GLOB SOURCE_LINK ${PROJECT_SOURCE_DIR}/examples/nonlinear/*.cpp)

add_executable(polar_test ${PROJECT_SOURCE_DIR}/examples/Polar_test.cpp)
add_executable(link  ${SOURCE_LINK} ${HEADERS_LINK})
#add_executable(default ${PROJECT_SOURCE_DIR}/examples/default.cpp)

#target_link_libraries(polar_test polar)
target_link_libraries(polar_test)
#target_link_libraries(default)
target_link_libraries(link polar)
