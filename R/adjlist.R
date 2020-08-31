#' Adjacency lists
#'
#' These functions are all-vertices version of `neighbors()` and `incident()`.
#' @seealso [neighbors()] and [incident()] for single-vertex version.
#' @source <https://igraph.org/c/doc/igraph-Data-structures.html#igraph-Adjlists>
#' @details
#' `as_adjlist()`: Convert a graph to a list of adjacent vertices.
#' @inheritParams common_params
#' @rdname adjlist
#' @export
as_adjlist = function(graph, mode = 3L, loops = 1L, multiple = 1L) {
  .Call(`_igraphlite_as_adjlist_`, graph, mode, loops, multiple)
}

#' @details
#' `as_inclist()`: Convert a graph to a list of incident edges.
#' @rdname adjlist
#' @export
as_inclist = function(graph, mode = 3L, loops = 1L) {
  .Call(`_igraphlite_as_inclist_`, graph, mode, loops)
}
