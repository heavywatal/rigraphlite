#' @useDynLib igraphlite, .registration = TRUE
#' @importFrom rlang .data
#' @keywords internal
"_PACKAGE"

#' igraph_ptr class: thin wrapper of `igraph_t`.
#'
#' @seealso [graph_from_edgelist()], [graph_from_data_frame()], [graph_tree()]
#'   for object instantiation.
#' @source <https://github.com/igraph/igraph/blob/master/include/igraph_datatype.h>
#' @docType class
#' @keywords data
#' @format external pointer to C++ IGraph class object.
#' @name igraph_ptr
#' @rdname igraph-class
NULL

#' Check if an object is igraph_ptr class
#'
#' @param x object to be tested.
#'
#' @rdname is_igraph
#' @export
is_igraph = function(x) {
  inherits(x, "igraph_ptr")
}

#' Check and return igraph version.h
#'
#' @source <https://igraph.org/c/doc/igraph-Nongraph.html>
#' @rdname version
#' @export
igraph_version = function() {
  .Call(`_igraphlite_igraph_version_`)
}

#' Random numbers
#'
#' @source <https://igraph.org/c/doc/igraph-Random.html>
#' @param seed An integer.
#' @rdname random
#' @export
igraph_rng_seed = function(seed) {
  .Call(`_igraphlite_rng_seed`, seed)
}
