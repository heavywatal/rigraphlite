cmake_minimum_required(VERSION 3.24)
project($ENV{R_PACKAGE_NAME}
  VERSION 1.0.1
  LANGUAGES C CXX)

include(CMakePrintHelpers)
include(FetchContent)
include(GNUInstallDirs)
cmake_print_variables(CMAKE_CURRENT_SOURCE_DIR)
cmake_print_variables(CMAKE_C_COMPILER CMAKE_C_FLAGS)
cmake_print_variables(CMAKE_CXX_COMPILER CMAKE_CXX_FLAGS)
cmake_print_variables(CMAKE_SHARED_LINKER_FLAGS_INIT)

message(STATUS "ENV{igraph_ROOT}=$ENV{igraph_ROOT}")
message(STATUS "ENV{CMAKE_PREFIX_PATH}=$ENV{CMAKE_PREFIX_PATH}")

find_package(igraph ${PROJECT_VERSION} QUIET)
cmake_print_variables(igraph_FOUND igraph_DIR IGRAPH_INTEGER_SIZE)
if(igraph_FOUND AND (IGRAPH_INTEGER_SIZE STREQUAL "32"))
  get_target_property(INCLUDEDIR igraph::igraph INTERFACE_INCLUDE_DIRECTORIES)
  list(GET INCLUDEDIR 1 INCLUDEDIR)
  get_target_property(LIBDIR igraph::igraph IMPORTED_LOCATION_RELEASE)
  cmake_path(REMOVE_FILENAME LIBDIR)
else()
  FetchContent_Declare(igraph
    URL https://github.com/igraph/igraph/releases/download/${PROJECT_VERSION}/igraph-${PROJECT_VERSION}.tar.gz
    URL_HASH SHA256=969f2d7d22f67e788d8638c9a8c96615f50d7819c08978b3ef4a787bb6daa96c
  )
  set(CMAKE_BUILD_TYPE Release)
  set(CMAKE_RULE_MESSAGES OFF CACHE BOOL "")
  set(BUILD_TESTING OFF CACHE BOOL "")
  set(BUILD_SHARED_LIBS ON)
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
  cmake_print_variables(GLPK_LIBRARY ARPACK_LIBRARY GMP_LIBRARY LIBXML2_LIBRARY)
  set(INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
  set(LIBDIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
  if(NOT APPLE)
    set(RPATH "$ENV{R_LIBRARY_DIR}/${PROJECT_NAME}/${CMAKE_INSTALL_LIBDIR}")
  endif()
endif()

set(CPPFLAGS "-I${INCLUDEDIR}")
set(LDFLAGS "-L${LIBDIR} -Wl,-rpath,${LIBDIR}")
if(RPATH)
  set(LDFLAGS "${LDFLAGS} -Wl,-rpath,${RPATH}")
endif()
set(LDLIBS "-ligraph")
cmake_print_variables(CPPFLAGS)
cmake_print_variables(LDFLAGS)
cmake_print_variables(LDLIBS)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Makevars.in
  ${CMAKE_CURRENT_SOURCE_DIR}/Makevars @ONLY
)

cmake_print_variables(CMAKE_CURRENT_BINARY_DIR)
if("${CMAKE_CURRENT_BINARY_DIR}" MATCHES "/build$")
  add_library(compile_commands OBJECT cpp11.cpp init.cpp igraph.cpp)
  target_include_directories(compile_commands PRIVATE
    "$ENV{R_INCLUDE_DIR}"
    "${INCLUDEDIR}"
  )
  string(REPLACE ":" ";" R_LIBS_USER "$ENV{R_LIBS_USER}")
  string(REPLACE ":" ";" R_LIBS_SITE "$ENV{R_LIBS_SITE}")
  set(R_HOME "$ENV{R_HOME}/library")
  foreach(r_lib IN LISTS R_LIBS_USER R_LIBS_SITE R_HOME)
    if(IS_DIRECTORY "${r_lib}/cpp11/include")
      target_include_directories(compile_commands PRIVATE "${r_lib}/cpp11/include")
    endif()
  endforeach()
endif()
