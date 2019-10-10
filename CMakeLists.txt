# Author: Guanglei Wang 
# Time:  Thu Oct 10 15:19:31 CST 2019
cmake_minimum_required(VERSION 3.2)

project(Polar)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

set(MACOSX_RPATH 1)


# Find CLP (optional)
option(Clp "Link to CLP libraries" OFF)


# Find CLP?
if (Clp)
    message(STATUS "Enable CLP")
    add_definitions(-DUSE_CLP)
    find_package(CLP REQUIRED)
    include_directories(${CLP_INCLUDE_DIRS}/)
    set(LIBS ${LIBS} ${CLP_LIBRARIES})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lCoinUtils -lClp")
endif()


# Debug mode
option(Debug "Turn on debug mode" OFF)

# Coverage
option(Cov "Turn on coverage" OFF)


# set paths 
set(LIBS ${LIBS} ${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/lib/Release ${PROJECT_SOURCE_DIR}/lib/Debug)
