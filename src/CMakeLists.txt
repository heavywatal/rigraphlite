cmake_minimum_required(VERSION 3.1)
project(igraphlite
  VERSION 0.0.0.9000
  LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
include(GNUInstallDirs)

find_library(igraph NAMES igraph HINTS $ENV{HOME}/local/lib)
if(igraph)
  message(STATUS "igraph: ${igraph}")
  get_filename_component(igraph_LIBDIR "${igraph}" DIRECTORY)
  get_filename_component(igraph_INCLUDEDIR "${igraph_LIBDIR}/../include" ABSOLUTE)
  message(STATUS "igraph_LIBDIR: ${igraph_LIBDIR}")
  message(STATUS "igraph_INCLUDEDIR: ${igraph_INCLUDEDIR}")
  set(CPPFLAGS "-I${igraph_INCLUDEDIR}")
  set(LDFLAGS "-L${igraph_LIBDIR} -Wl,-rpath,${igraph_LIBDIR}")
else()
  get_filename_component(IGRAPH_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/../igraph" ABSOLUTE)
  message(STATUS "IGRAPH_SOURCE: ${IGRAPH_SOURCE}")
  if(EXISTS "${IGRAPH_SOURCE}")
    message(STATUS "IGRAPH_SOURCE exists")
  else()
    message(STATUS "IGRAPH_SOURCE does not exist")
    execute_process(COMMAND pwd)
    find_package(Git)
    execute_process(COMMAND
      ${GIT_EXECUTABLE} clone --depth=1 --branch=master https://github.com/heavywatal/igraph.git ${IGRAPH_SOURCE}
    )
  endif()
  execute_process(COMMAND
    ./bootstrap.sh
    WORKING_DIRECTORY "${IGRAPH_SOURCE}"
  )
  execute_process(COMMAND
    ./configure --prefix=${CMAKE_INSTALL_PREFIX}
    WORKING_DIRECTORY "${IGRAPH_SOURCE}"
  )
  execute_process(COMMAND
    make -j2 install
    WORKING_DIRECTORY "${IGRAPH_SOURCE}"
  )
endif()

set(LIBDIR ${CMAKE_INSTALL_PREFIX}/libs)
set(CPPFLAGS "${CPPFLAGS} -I${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
set(LDFLAGS "${LDFLAGS} -L${LIBDIR} -Wl,-rpath,${LIBDIR}")
set(LDLIBS "-ligraph")
message(STATUS "CPPFLAGS: ${CPPFLAGS}")
message(STATUS "LDFLAGS: ${LDFLAGS}")
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Makevars.in
  ${CMAKE_CURRENT_SOURCE_DIR}/Makevars @ONLY
)
