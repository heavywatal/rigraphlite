#' Adjacency lists
#'
#' These functions are all-vertices version of `neighbors()` and `incident()`.
#' @seealso [neighbors()] and [incident()] for single-vertex version.
#' @source <https://igraph.org/c/doc/ch07.html#igraph-Adjlists>
#' @details
#' `as_adjlist()`: Convert a graph to a list of adjacent vertices.
#' @inheritParams common_params
#' @rdname adjlist
#' @export
as_adjlist = function(graph, mode = 3L) {
  graph$as_adjlist(mode)
}

#' @details
#' `as_inclist()`: Convert a graph to a list of incident edges.
#' @rdname adjlist
#' @export
as_inclist = function(graph, mode = 3L) {
  graph$as_inclist(mode)
}
