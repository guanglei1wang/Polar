#include(ExternalProject)

#MACRO(HEADER_DIRECTORIES return_list)
#     FILE(GLOB_RECURSE new_list *.h)
#     SET(dir_list "")
#     FOREACH(file_path ${new_list})
#         GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
#         SET(dir_list ${dir_list} ${dir_path})
#     ENDFOREACH()
#     LIST(REMOVE_DUPLICATES dir_list)
#     SET(${return_list} ${dir_list})
#ENDMACRO()


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


# the RPATH to be used when installing, but only if it's not a system directory

file(GLOB HEADERS ${PROJECT_INCLUDE_DIR}/Cbc/*/ *.h)
file(GLOB_RECURSE SOURCES ./Cbc/*/*.cpp ${PROJECT_INCLUDE_DIR}/Cbc/*/*.h)

add_library(polar STATIC ${SOURCES} ${HEADERS})
target_link_libraries(polar ${CLP_LIBRARIES} ${OSI_LIBRARIES} ${CGL_LIBRARIES}  ${CBC_LIBRARIES})
set_target_properties(polar PROPERTIES LINKER_LANGUAGE CXX)


SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
SET(CMAKE_INSTALL_RPATH "${PROJ_LIB_DIR}")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
