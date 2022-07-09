cmake_minimum_required(VERSION 3.16)
project(rigraphlite
  VERSION 0.9.9
  LANGUAGES CXX)

message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
include(GNUInstallDirs)
set(CMAKE_VERBOSE_MAKEFILE ON)

message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
find_package(igraph ${PROJECT_VERSION} QUIET)
message(STATUS "igraph_FOUND: ${igraph_FOUND}")
if(igraph_FOUND)
  get_target_property(INCLUDEDIR igraph::igraph INTERFACE_INCLUDE_DIRECTORIES)
  list(GET INCLUDEDIR 1 INCLUDEDIR)
  get_filename_component(CMAKE_INSTALL_PREFIX "${INCLUDEDIR}" DIRECTORY)
  message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
  install(CODE "message(STATUS ${igraph_DIR})") # to make target 'install'
else()
  set(CMAKE_BUILD_TYPE Release)
  set(CMAKE_RULE_MESSAGES OFF CACHE BOOL "")
  set(BUILD_TESTING OFF CACHE BOOL "")
  set(BUILD_SHARED_LIBS ON)
  include(FetchContent)
  set(FETCHCONTENT_QUIET OFF)
  message(STATUS "FETCHCONTENT_SOURCE_DIR_IGRAPH: ${FETCHCONTENT_SOURCE_DIR_IGRAPH}")
  FetchContent_Declare(
    igraph
    GIT_REPOSITORY https://github.com/igraph/igraph.git
    GIT_TAG ${PROJECT_VERSION}
    GIT_SHALLOW ON
  )
  FetchContent_MakeAvailable(igraph)
  message(STATUS "igraph_SOURCE_DIR: ${igraph_SOURCE_DIR}")
endif()

if(${CMAKE_INSTALL_PREFIX} MATCHES linuxbrew)
  set(CMAKE_INSTALL_LIBDIR lib)
endif()
set(LIBDIR ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
set(CPPFLAGS "-I${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
set(LDFLAGS "-L${LIBDIR} -Wl,-rpath,${LIBDIR}")
set(LDLIBS "-ligraph")
message(STATUS "CPPFLAGS: ${CPPFLAGS}")
message(STATUS "LDFLAGS: ${LDFLAGS}")
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Makevars.in
  ${CMAKE_CURRENT_SOURCE_DIR}/Makevars @ONLY
)
