cmake_minimum_required(VERSION 3.1)
project(igraphlite
  VERSION 0.0.0.9000
  LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
include(GNUInstallDirs)

if(DEFINED ENV{IGRAPH_INSTALL_PREFIX})
  set(IGRAPH_INSTALL_PREFIX "$ENV{IGRAPH_INSTALL_PREFIX}")
else()
  set(IGRAPH_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
endif()
message(STATUS "IGRAPH_INSTALL_PREFIX: ${IGRAPH_INSTALL_PREFIX}")
set(LIBDIR "${IGRAPH_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set(CPPFLAGS "-I${IGRAPH_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
set(LDFLAGS "-L${LIBDIR} -Wl,-rpath,${LIBDIR}")
set(LDLIBS "-ligraph")

find_library(igraph NAMES igraph HINTS "${LIBDIR}")
if(igraph)
  message(STATUS "Using preinstalled igraph: ${igraph}")
else()
  find_package(Git)
  get_filename_component(IGRAPH_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/../igraph" ABSOLUTE)
  if(EXISTS "${IGRAPH_SOURCE}")
    # source repo
    execute_process(COMMAND
      ${GIT_EXECUTABLE} submodule update --init --recursive
      WORKING_DIRECTORY "${IGRAPH_SOURCE}"
    )
  else()
    # bundled package
    set(IGRAPH_GIT "https://github.com/heavywatal/igraph.git")
    set(IGRAPH_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/igraph")
    execute_process(COMMAND
      ${GIT_EXECUTABLE} clone --depth=1 --single-branch ${IGRAPH_GIT} ${IGRAPH_SOURCE}
    )
  endif()
endif()

if(DEFINED IGRAPH_SOURCE)
  message(STATUS "IGRAPH_SOURCE: ${IGRAPH_SOURCE}")
  if("${IGRAPH_SOURCE}/.git" IS_NEWER_THAN "${IGRAPH_SOURCE}/configure")
    execute_process(COMMAND
      ./bootstrap.sh
      WORKING_DIRECTORY "${IGRAPH_SOURCE}"
    )
  endif()
  if("${IGRAPH_SOURCE}/configure" IS_NEWER_THAN "${IGRAPH_SOURCE}/Makefile")
    execute_process(COMMAND
      ./configure --prefix=${IGRAPH_INSTALL_PREFIX} --disable-static --with-external-blas --with-external-lapack
      WORKING_DIRECTORY "${IGRAPH_SOURCE}"
      OUTPUT_QUIET
    )
  endif()
  execute_process(COMMAND
    make -j2 install
    WORKING_DIRECTORY "${IGRAPH_SOURCE}"
    ERROR_QUIET
  )
endif()

message(STATUS "CPPFLAGS: ${CPPFLAGS}")
message(STATUS "LDFLAGS: ${LDFLAGS}")
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Makevars.in
  ${CMAKE_CURRENT_SOURCE_DIR}/Makevars @ONLY
)
