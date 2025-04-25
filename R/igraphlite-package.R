#' @useDynLib igraphlite, .registration = TRUE
#' @importFrom rlang .data
#' @keywords internal
"_PACKAGE"

#' `igraph_ptr`: cpp11-powered class for igraph objects
#'
#' `igraph_ptr` is a subclass of external pointer to C++ `IGraph` objects.
#' The `IGraph` class is a thin wrapper of `igraph_t` in C igraph library.
#' @seealso [as_igraph()] and [as.data.frame.igraph_ptr()] for conversion
#' from and to R objects.
#' @source <https://github.com/igraph/igraph/blob/master/include/igraph_datatype.h>
#' @name igraph_ptr
#' @rdname igraph-class
NULL

#' @param x An object to be tested.
#' @returns A logical, `TRUE` if `x` is of class `igraph_ptr`, `FALSE` otherwise.
#' @rdname igraph-class
#' @export
#' @examples
#' v = seq_len(6L)
#' is_igraph(v)
#'
#' g = graph_create(v)
#' is_igraph(g)
#'
#' print(g)
is_igraph = function(x) {
  inherits(x, "igraph_ptr")
}

#' Get the version of the igraph C library
#'
#' Not to be confused with the R package version.
#' @returns A character string with the igraph version.
#' @source <https://igraph.org/c/doc/igraph-Nongraph.html>
#' @rdname version
#' @export
#' @examples
#' igraph_version()
igraph_version = function() {
  .Call(`_igraphlite_igraph_version_`)
}

#' Seeds a random number generator
#'
#' Initializes `igraph_rng_default()` with an integer seed.
#' @source <https://igraph.org/c/doc/igraph-Random.html>
#' @param seed An integer.
#' @returns `NULL`.
#' @rdname random
#' @export
#' @examples
#' igraph_rng_seed(24601L)
igraph_rng_seed = function(seed) {
  invisible(.Call(`_igraphlite_rng_seed`, seed))
}
