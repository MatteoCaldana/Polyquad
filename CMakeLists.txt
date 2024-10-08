##################################################
# Main build file for Polyquad
##################################################
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
INCLUDE(CheckIncludeFiles)

PROJECT(polyquad)

# Add our custom CMake module dir
SET(CMAKE_MODULE_PATH ${polyquad_SOURCE_DIR}/cmake)

SET(POLYQUAD_VERSION_MAJOR 1)
SET(POLYQUAD_VERSION_MINOR 1)
SET(POLYQUAD_VERSION "${POLYQUAD_VERSION_MAJOR}.${POLYQUAD_VERSION_MINOR}")

##################################################
# Source files
##################################################
SET(POLYQUAD_HEADERS
    src/dispatcher.hpp
    src/dispatcher_map.hpp
    src/dispatcher_instances/instances.hpp
    src/actions/eval.hpp
    src/actions/expand.hpp
    src/actions/find.hpp
    src/actions/iterate.hpp
    src/shapes/base.hpp
    src/shapes/hex.hpp
    src/shapes/quad.hpp
    src/shapes/tet.hpp
    src/shapes/tri.hpp
    src/shapes/pyr.hpp
    src/shapes/pri.hpp
    src/utils/io.hpp
    src/utils/eigen_addons.hpp
    src/utils/ortho_poly.hpp
    src/utils/serialization.hpp
    src/utils/timer.hpp
)

SET(POLYQUAD_SOURCES 
  src/dispatcher_map.cpp
  src/dispatcher_instances/tri_double.cpp
)

##################################################
# Executable
##################################################
ADD_EXECUTABLE(polyquad src/main.cpp ${POLYQUAD_SOURCES} ${POLYQUAD_HEADERS})

##################################################
# Internal includes, these must come before the
# located dependencies!
##################################################
INCLUDE_DIRECTORIES(src)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

##################################################
# External dependencies
##################################################
SET(POLYQUAD_BOOST_LIBS
    program_options
    serialization)

# Find Boost
FIND_PACKAGE(Boost REQUIRED ${POLYQUAD_BOOST_LIBS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(polyquad ${Boost_LIBRARIES})

# Find Eigen 3
FIND_PACKAGE(Eigen3 REQUIRED)
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIR}/unsupported)

##################################################
# MPI
##################################################
FIND_PACKAGE(MPI)
IF(MPI_CXX_FOUND)
    FIND_PACKAGE(Boost COMPONENTS mpi)
    IF(Boost_MPI_FOUND)
        SET(CMAKE_CXX_COMPILE_FLAGS
            ${CMAKE_CXX_COMPILE_FLAGS}
            ${MPI_COMPILE_FLAGS})
        SET(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
        INCLUDE_DIRECTORIES(${MPI_INCLUDE_PATH})
        TARGET_LINK_LIBRARIES(polyquad
                              ${Boost_MPI_LIBRARY}
                              ${MPI_CXX_LIBRARIES})
        SET(POLYQUAD_HAVE_MPI 1)
    ENDIF()
ENDIF()

# Avoid ';' in the link flags
STRING(REPLACE ";" " " CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS}")

##################################################
# C++17
##################################################
IF(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -Wno-deprecated")
ENDIF()

##################################################
# Build type
##################################################
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE RelWithDebInfo)
ENDIF()

##################################################
# Optimisation
##################################################

# Auto-optimise for CPU arch for non-debug builds
IF(NOT CMAKE_BUILD_TYPE MATCHES Debug)
  ADD_DEFINITIONS("-O3 -march=native")
ENDIF()

# For release builds remove all debugging info
IF(CMAKE_BUILD_TYPE MATCHES Release)
  ADD_DEFINITIONS("-DNDEBUG")
ENDIF()

##################################################
# Date & compiler info
##################################################
INCLUDE(Today)
TODAY(POLYQUAD_BUILD_DATE)

#INCLUDE(GetGitRevisionDescription)
#GET_GIT_HEAD_REVISION(GIT_REFSPEC POLYQUAD_GIT_SHA1)

##################################################
# Config.h
##################################################
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/config.h)
