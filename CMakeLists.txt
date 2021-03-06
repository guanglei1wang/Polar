# Author: Guanglei Wang 
# Time:  Thu Oct 10 15:19:31 CST 2019
cmake_minimum_required(VERSION 3.2)

project(polar)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

set(MACOSX_RPATH 1)

# Find CLP (optional)
option(Clp "Link to CLP libraries" ON)
option(Cgl "Link to CGL libraries" ON)
option(Osi "Link to OSI libraries" ON)
option(Cbc "Link to CBC libraries" ON)


# Find CLP?
if (Clp MATCHES ON)
    message(STATUS "I am trying to enable CLP.......")
    add_definitions(-DUSE_CLP)
    add_definitions(-DCOIN_HAS_CLP)
    find_package(CLP REQUIRED)
    include_directories(${CLP_INCLUDE_DIRS}/)
    set(LIBS ${LIBS} ${CLP_LIBRARIES})
    message(STATUS "The associated LIBS are: " ${LIBS})
    message(STATUS "I am trying to enable COINUTILS.......")
    find_package(COINUTILS REQUIRED)
    include_directories(${COINUTILS_INCLUDE_DIRS}/)
    set(LIBS ${LIBS} ${COINUTILS_LIBRARIES})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lClp -lCoinUtils")
endif()

# Find CGL? 
if (Cgl MATCHES ON)
    message(STATUS "I am trying to enable CGL.......")
    add_definitions(-DUSE_CGL)
    find_package(CGL REQUIRED)
    include_directories(${CGL_INCLUDE_DIRS}/)
    set(LIBS ${LIBS} ${CGL_LIBRARIES})
message(STATUS "The associated LIBS are: " ${LIBS})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lCgl")
endif()

# Find Osi?
if (Osi MATCHES ON)
    message(STATUS "I am trying to enable OSI.......")
    add_definitions(-DUSE_OSI)
    find_package(OSI REQUIRED)
    include_directories(${OSI_INCLUDE_DIRS}/)
    set(LIBS ${LIBS} ${OSI_LIBRARIES})
message(STATUS "The associated LIBS are: " ${LIBS})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lOsi -lOsiClp")
endif()

# Find CBC?
if (CBC MATCHES ON)
    message(STATUS "I am trying to enable CBC library.......")
    add_definitions(-DUSE_CBC)
    find_package(CBC REQUIRED)
    include_directories(${CBC_INCLUDE_DIRS}/)
    set(LIBS ${LIBS} ${CBC_LIBRARIES})
    message(STATUS "The associated LIBS are: " ${LIBS})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lCbc")
endif()

message(STATUS "The associated LIBS are: " ${LIBS})
set(LIBS ${LIBS} ${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/lib/Release ${PROJECT_SOURCE_DIR}/lib/Debug)
#set(LIBS ${LIBS} ${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/lib/Release ${PROJECT_SOURCE_DIR}/lib/Debug)
#set(LIBS ${LIBS} ${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/lib/Debug)
# Compiler options
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

# Build options
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/Release)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/)
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)


# Debug mode
option(Debug "Turn on debug mode" OFF)

# Coverage
option(Cov "Turn on coverage" OFF)


set(CMAKE_BUILD_TYPE "Release")
if (Debug)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/Debug)
endif()

if(Cov)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fprofile-arcs -lgcov")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'\$ORIGIN/lib'")

#subdirectories 
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(solvers)

#Get user defined configuration including passing project source directory into c++ code
configure_file(Config.h.in ${PROJECT_SOURCE_DIR}/include/polar/Config.h)
