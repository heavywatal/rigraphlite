# igraphlite

[![CRAN Status Badge](https://www.r-pkg.org/badges/version/igraphlite)](http://cran.r-project.org/package=igraphlite)
[![Build Status](https://travis-ci.com/heavywatal/rigraphlite.svg?branch=master)](https://travis-ci.com/heavywatal/rigraphlite)
[![Codecov test coverage](https://codecov.io/gh/heavywatal/rigraphlite/branch/master/graph/badge.svg)](https://codecov.io/gh/heavywatal/rigraphlite?branch=master)

igraphlite is an Rcpp-powered R package interface to [igraph](https://igraph.org/) network analysis library. It is not a fork of the existing [R igraph package](https://igraph.org/r/), but a reboot from scratch striving for good performance, simple codebase, and the consistency with the [C implementation](https://igraph.org/c/doc/).


## Requirements

- C++14 compiler (clang++ >= Apple LLVM 8.1, g++ >= 5.3)


## Installation

```r
# install.packages("remotes")
remotes::install_github("heavywatal/rigraphlite")
```
