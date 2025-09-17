# igraphlite

[![CRAN Status Badge](https://www.r-pkg.org/badges/version/igraphlite)](https://cran.r-project.org/package=igraphlite)
[![R Build status](https://github.com/heavywatal/rigraphlite/workflows/R-CMD-check/badge.svg)](https://github.com/heavywatal/rigraphlite/actions)
[![codecov](https://codecov.io/gh/heavywatal/rigraphlite/graph/badge.svg?token=xWOphBcnTN)](https://codecov.io/gh/heavywatal/rigraphlite)

igraphlite is a cpp11-powered R package interface to [igraph](https://igraph.org/) network analysis library. It is not a fork of the existing [R igraph package](https://igraph.org/r/), but a reboot from scratch striving for good performance, simple codebase, and the consistency with the [C implementation](https://igraph.org/c/doc/).


## Requirements

- Unix-like environment (macOS, Linux, WSL, MinGW on MSYS2, etc.)
- C++17 compiler (clang++ >= Apple clang 11.0, g++ >= 9.1)
- [CMake](https://cmake.org/)
- NOT required:
    - R igraph package
    - C igraph library:
      igraphlite can use an existing igraph library for faster installation
      if it is built with `IGRAPH_INTEGER_SIZE=32` and found by CMake `find_package()`.
      For example, `brew install heavywatal/tap/igraph32` provides such a library.
      Environment variables `${igraph_ROOT}` and `${CMAKE_PREFIX_PATH}` can be used to help CMake find it.
      if not found, an appropriate version is built and installed automatically.

## Installation

```r
# install.packages("pak")
pak::pak("heavywatal/rigraphlite")
```
