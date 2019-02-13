cmake_minimum_required(VERSION 3.1)
project(igraphlite
  VERSION 0.0.0.9000
  LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
include(GNUInstallDirs)
set(CMAKE_INSTALL_LIBDIR libs)
set(LIBDIR ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})

find_library(igraph NAMES igraph HINTS ${LIBDIR} $ENV{HOME}/local/lib)
message(STATUS "igraph: ${igraph}")

if(NOT igraph)
  execute_process(COMMAND
    ./bootstrap.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../igraph
  )
  execute_process(COMMAND
    ./configure --prefix=${CMAKE_INSTALL_PREFIX}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../igraph
  )
  execute_process(COMMAND
    make -j4 install
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../igraph
  )
endif()

set(CPPFLAGS "-I${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
set(LDFLAGS "-L${LIBDIR} -Wl,-rpath,${LIBDIR}")
set(LDLIBS "-ligraph")
message(STATUS "CPPFLAGS: ${CPPFLAGS}")
message(STATUS "LDFLAGS: ${LDFLAGS}")
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Makevars.in
  ${CMAKE_CURRENT_SOURCE_DIR}/Makevars @ONLY
)
