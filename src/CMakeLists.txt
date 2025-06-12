cmake_minimum_required(VERSION 3.18)
project(rigraphlite
  VERSION 0.10.16
  LANGUAGES C CXX)

include(CMakePrintHelpers)
include(FetchContent)
include(GNUInstallDirs)
cmake_print_variables(CMAKE_CURRENT_SOURCE_DIR)

function(import_env variable)
  if(DEFINED ENV{${variable}})
    set(${variable} $ENV{${variable}} PARENT_SCOPE)
  endif()
endfunction()

cmake_print_variables(igraph_ROOT CMAKE_PREFIX_PATH)
find_package(igraph ${PROJECT_VERSION} QUIET)
cmake_print_variables(igraph_FOUND IGRAPH_INTEGER_SIZE igraph_DIR)
if(igraph_FOUND AND (IGRAPH_INTEGER_SIZE STREQUAL "32"))
  get_target_property(INCLUDEDIR igraph::igraph INTERFACE_INCLUDE_DIRECTORIES)
  list(GET INCLUDEDIR 1 INCLUDEDIR)
  get_target_property(LIBDIR igraph::igraph IMPORTED_LOCATION_RELEASE)
  get_filename_component(LIBDIR "${LIBDIR}" DIRECTORY)
  get_target_property(LIB_TYPE igraph::igraph TYPE)
  if(LIB_TYPE STREQUAL "SHARED_LIBRARY")
    set(BUILD_SHARED_LIBS ON) # for conditinal LDFLAGS
  endif()
else()
  set(FETCHCONTENT_QUIET OFF)
  import_env("FETCHCONTENT_SOURCE_DIR_IGRAPH")
  cmake_print_variables(FETCHCONTENT_SOURCE_DIR_IGRAPH)
  FetchContent_Declare(
    igraph
    GIT_REPOSITORY https://github.com/igraph/igraph.git
    GIT_TAG ${PROJECT_VERSION}
    GIT_SHALLOW ON
  )
  set(CMAKE_BUILD_TYPE Release)
  set(CMAKE_INSTALL_LIBDIR "libs")
  set(CMAKE_RULE_MESSAGES OFF CACHE BOOL "")
  set(BUILD_TESTING OFF CACHE BOOL "")
  set(BUILD_SHARED_LIBS OFF)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
  set(IGRAPH_OPENMP_SUPPORT OFF)
  set(IGRAPH_ENABLE_LTO "AUTO")
  set(IGRAPH_ENABLE_TLS ON)
  set(IGRAPH_GLPK_SUPPORT ON)
  set(IGRAPH_GRAPHML_SUPPORT ON)
  set(IGRAPH_USE_INTERNAL_BLAS OFF)
  set(IGRAPH_USE_INTERNAL_GLPK OFF)
  set(IGRAPH_USE_INTERNAL_GMP OFF)
  set(IGRAPH_USE_INTERNAL_LAPACK OFF)
  set(IGRAPH_INTEGER_SIZE 32)
  set(USE_CCACHE OFF)
  FetchContent_MakeAvailable(igraph)
  cmake_print_variables(igraph_SOURCE_DIR igraph_BINARY_DIR)
  set(INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
  set(LIBDIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
endif()

set(CPPFLAGS "-I${INCLUDEDIR}")
set(LDFLAGS "-L${LIBDIR}")
set(LDLIBS "-ligraph")
if(BUILD_SHARED_LIBS)
  set(LDFLAGS "${LDFLAGS} -Wl,-rpath,${LIBDIR}")
else()
  if(NOT APPLE)
    set(LDLIBS "${LDLIBS} $(LAPACK_LIBS) $(BLAS_LIBS) $(FLIBS)")
  endif()
endif()
cmake_print_variables(CPPFLAGS)
cmake_print_variables(LDFLAGS)
cmake_print_variables(LDLIBS)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Makevars.in
  ${CMAKE_CURRENT_SOURCE_DIR}/Makevars @ONLY
)
