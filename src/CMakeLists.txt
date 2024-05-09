cmake_minimum_required(VERSION 3.18)
project(rigraphlite
  VERSION 0.10.12
  LANGUAGES C CXX)

include(CMakePrintHelpers)
include(FetchContent)
include(GNUInstallDirs)
set(CMAKE_VERBOSE_MAKEFILE ON)
cmake_print_variables(CMAKE_CURRENT_SOURCE_DIR)

function(import_env variable)
  if(DEFINED ENV{${variable}})
    set(${variable} $ENV{${variable}} PARENT_SCOPE)
  endif()
endfunction()

cmake_print_variables(CMAKE_PREFIX_PATH)
find_package(igraph ${PROJECT_VERSION} QUIET)
cmake_print_variables(igraph_FOUND igraph_DIR)
if(igraph_FOUND)
  get_target_property(INCLUDEDIR igraph::igraph INTERFACE_INCLUDE_DIRECTORIES)
  list(GET INCLUDEDIR 1 INCLUDEDIR)
  get_filename_component(CMAKE_INSTALL_PREFIX "${INCLUDEDIR}" DIRECTORY)
  cmake_print_variables(CMAKE_INSTALL_PREFIX)
  if(${CMAKE_INSTALL_PREFIX} MATCHES linuxbrew)
    set(CMAKE_INSTALL_LIBDIR "lib")
  endif()
  install(CODE "message(STATUS ${igraph_DIR})") # to make target 'install'
else()
  set(FETCHCONTENT_QUIET OFF)
  import_env("FETCHCONTENT_SOURCE_DIR_IGRAPH")
  cmake_print_variables(FETCHCONTENT_SOURCE_DIR_IGRAPH)
  FetchContent_Declare(
    igraph
    GIT_REPOSITORY https://github.com/igraph/igraph.git
    GIT_TAG ${PROJECT_VERSION}
    GIT_SHALLOW ON
    # FIND_PACKAGE_ARGS  # 3.24
  )
  set(CMAKE_BUILD_TYPE Release)
  set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
  set(CMAKE_BUILD_WITH_INSTALL_NAME_DIR ON)
  set(CMAKE_INSTALL_LIBDIR "libs")
  set(CMAKE_RULE_MESSAGES OFF CACHE BOOL "")
  set(BUILD_TESTING OFF CACHE BOOL "")
  set(BUILD_SHARED_LIBS ON)
  set(IGRAPH_OPENMP_SUPPORT OFF)
  set(IGRAPH_USE_INTERNAL_GLPK OFF)
  set(IGRAPH_USE_INTERNAL_GMP OFF)
  set(IGRAPH_USE_INTERNAL_LAPACK OFF)
  set(IGRAPH_INTEGER_SIZE 32)
  FetchContent_MakeAvailable(igraph)
  cmake_print_variables(igraph_SOURCE_DIR igraph_BINARY_DIR)
endif()

set(LIBDIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set(CPPFLAGS "-I${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
set(LDFLAGS "-L${LIBDIR} -Wl,-rpath,${LIBDIR}")
set(LDLIBS "-ligraph")
cmake_print_variables(CPPFLAGS)
cmake_print_variables(LDFLAGS)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Makevars.in
  ${CMAKE_CURRENT_SOURCE_DIR}/Makevars @ONLY
)
