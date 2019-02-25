cmake_minimum_required(VERSION 3.1)
project(igraphlite
  VERSION 0.0.0.9000
  LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
include(GNUInstallDirs)

if(DEFINED ENV{IGRAPH_INSTALL_PREFIX})
  set(CMAKE_INSTALL_PREFIX "$ENV{IGRAPH_INSTALL_PREFIX}")
endif()
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
set(LIBDIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set(CPPFLAGS "-I${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
set(LDFLAGS "-L${LIBDIR} -Wl,-rpath,${LIBDIR}")
set(LDLIBS "-ligraph")

find_library(igraph NAMES igraph HINTS "${LIBDIR}")
if(igraph)
  message(STATUS "Using preinstalled igraph: ${igraph}")
else()
  find_package(Git)
  get_filename_component(PACKAGE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)
  if(EXISTS "${PACKAGE_ROOT_DIR}/.git")
    # source repo
    set(IGRAPH_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/igraph")
  else()
    # bundled package
    set(IGRAPH_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/igraph")
  endif()
  if(EXISTS "${IGRAPH_SOURCE}")
    execute_process(COMMAND
      ${GIT_EXECUTABLE} pull --ff-only
      WORKING_DIRECTORY "${IGRAPH_SOURCE}"
    )
  else()
    set(IGRAPH_REMOTE "https://github.com/heavywatal/igraph.git")
    execute_process(COMMAND
      ${GIT_EXECUTABLE} clone --depth=1 --single-branch ${IGRAPH_REMOTE} ${IGRAPH_SOURCE}
    )
  endif()
endif()

if(DEFINED IGRAPH_SOURCE)
  message(STATUS "IGRAPH_SOURCE: ${IGRAPH_SOURCE}")
  if("${IGRAPH_SOURCE}/.git/index" IS_NEWER_THAN "${IGRAPH_SOURCE}/configure")
    execute_process(COMMAND
      ./bootstrap.sh
      WORKING_DIRECTORY "${IGRAPH_SOURCE}"
    )
  endif()
  if("${IGRAPH_SOURCE}/configure" IS_NEWER_THAN "${IGRAPH_SOURCE}/Makefile")
    execute_process(COMMAND
      ./configure --prefix=${CMAKE_INSTALL_PREFIX} --disable-static --with-external-blas --with-external-lapack
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
