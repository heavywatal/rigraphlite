# igraphlite

[![CRAN Status Badge](https://www.r-pkg.org/badges/version/igraphlite)](https://cran.r-project.org/package=igraphlite)
[![R Build status](https://github.com/heavywatal/rigraphlite/workflows/R-CMD-check/badge.svg)](https://github.com/heavywatal/rigraphlite/actions)
[![codecov](https://codecov.io/gh/heavywatal/rigraphlite/graph/badge.svg?token=xWOphBcnTN)](https://codecov.io/gh/heavywatal/rigraphlite)

igraphlite is a cpp11-powered R package interface to [igraph](https://igraph.org/) network analysis library. It is not a fork of the existing [R igraph package](https://igraph.org/r/), but a reboot from scratch striving for good performance, simple codebase, and the consistency with the [C implementation](https://igraph.org/c/doc/).


## Requirements

- Unix-like environment (macOS, Linux, WSL, MinGW on MSYS2, etc.)
- C++17 compiler (clang++ >= Apple clang 11.0, g++ >= 9.1)
- [CMake](https://cmake.org/) (>= 3.20.0)
- NOT required:
    - R igraph package
    - C igraph library:
      igraphlite first tries to `find_package()` in `${igraph_ROOT}` and `${CMAKE_PREFIX_PATH}`; if not found, it builds and installs an appropriate version automatically.

## Installation

```r
# install.packages("devtools")
devtools::install_github("heavywatal/rigraphlite")
```
