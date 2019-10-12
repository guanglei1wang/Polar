#include(ExternalProject)

include_directories(${PROJECT_INCLUDE_DIR})

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
#SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# the RPATH to be used when installing, but only if it's not a system directory
#SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib:'$ORIGIN/lib'")

file(GLOB HEADERS ${PROJECT_INCLUDE_DIR} *.h)
file(GLOB SOURCES ./Cbc/*/ *.cpp ${PROJECT_INCLUDE_DIR}/Cbc/*/ *.h)


#if(Cov)
#  set_target_properties(Polar
#  PROPERTIES
#    COMPILE_FLAGS "-ftest-coverage -fprofile-arcs"
#    LINK_FLAGS    "-lgcov --coverage -fprofile-arcs"
#  )
#endif()



add_library(Polar STATIC ${SOURCES} ${HEADERS})
#target_link_libraries(Polar ${OSI_LIBRARIES}  ${CLP_LIBRARIES} ${CGL_LIBRARIES})
set_target_properties(Polar PROPERTIES LINKER_LANGUAGE CXX)
