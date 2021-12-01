# igraphlite

[![CRAN Status Badge](https://www.r-pkg.org/badges/version/igraphlite)](https://cran.r-project.org/package=igraphlite)
[![R Build status](https://github.com/heavywatal/rigraphlite/workflows/R-CMD-check/badge.svg)](https://github.com/heavywatal/rigraphlite/actions)
[![Codecov test coverage](https://codecov.io/gh/heavywatal/rigraphlite/branch/master/graph/badge.svg)](https://app.codecov.io/gh/heavywatal/rigraphlite?branch=master)

igraphlite is an Rcpp-powered R package interface to [igraph](https://igraph.org/) network analysis library. It is not a fork of the existing [R igraph package](https://igraph.org/r/), but a reboot from scratch striving for good performance, simple codebase, and the consistency with the [C implementation](https://igraph.org/c/doc/).


## Requirements

- Unix-like environment (macOS, Linux, WSL, MinGW on MSYS2, etc.)
- C++14 compiler (clang++ >= Apple LLVM 8.1, g++ >= 5.3)
- [CMake](https://cmake.org/) (>= 3.8.0)
- Optionally the following tools are required when you build C igraph from [the latest source on GitHub](https://github.com/igraph/igraph):

    - [autoconf](https://www.gnu.org/software/autoconf/)
    - [automake](https://www.gnu.org/software/automake/)
    - [libtool](https://www.gnu.org/software/libtool/)
    - bison, byacc, flex

  The easiest way is to use [Homebrew](https://brew.sh/):
  `brew install autoconf automake libtool`

- NOT required:
    - R igraph package
    - C igraph library


## Installation

```r
# install.packages("devtools")
devtools::install_github("heavywatal/rigraphlite")
```
