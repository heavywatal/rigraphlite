#' @useDynLib igraphlite, .registration = TRUE
#' @importFrom rlang .data
#' @keywords internal
"_PACKAGE"

#' igraph_ptr class: thin wrapper of `igraph_t`.
#'
#' @seealso [is_igraph()] to check if an object is of class `igraph_ptr`.
#' @seealso [as_igraph()] and [as.data.frame.igraph_ptr()] for conversion
#' from and to R objects.
#' @seealso [graph_lattice()] and [graph_tree()] for deterministic graph generation.
#' @source <https://github.com/igraph/igraph/blob/master/include/igraph_datatype.h>
#' @docType class
#' @keywords data
#' @format external pointer to C++ IGraph class object.
#' @name igraph_ptr
#' @rdname igraph-class
NULL

#' Check if an object is igraph_ptr class
#'
#' @param x An object to be tested.
#'
#' @returns `TRUE` if the object is of class `igraph_ptr`, `FALSE` otherwise.
#' @seealso [as_igraph()] to convert an object to `igraph_ptr`.
#' @rdname is_igraph
#' @export
#' @examples
#' is_igraph(graph_tree(6L))
#' is_igraph(seq_len(6L))
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
