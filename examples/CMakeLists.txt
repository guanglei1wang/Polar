include_directories(${PROJECT_INCLUDE_DIR})

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
#SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# the RPATH to be used when installing, but only if it's not a system directory
#SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib:'$ORIGIN/lib'")

add_executable(polar_test ${PROJECT_SOURCE_DIR}/examples/Polar_test.cpp)
add_executable(link ${PROJECT_SOURCE_DIR}/examples/link.cpp)
#add_executable(default ${PROJECT_SOURCE_DIR}/examples/default.cpp)

#target_link_libraries(polar_test polar)
target_link_libraries(polar_test)
#target_link_libraries(default)
target_link_libraries(link)
