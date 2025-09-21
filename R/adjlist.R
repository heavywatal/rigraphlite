#' Adjacency lists and incidence lists
#'
#' Both lists have the same length as the number of vertices in the graph.
#' @seealso [neighbors()] and [incident()] for single-vertex version.
#' @source <https://igraph.org/c/doc/igraph-Data-structures.html#igraph-Adjlists>
#' @inheritParams common_params
#' @examples
#' g = graph_tree(5L)
#' as_adjlist(g, mode = 1L)
#' as_inclist(g, mode = 1L)
#' @returns `as_adjlist()` returns a list of adjacent vertices for each vertex.
#' @rdname adjlist
#' @export
as_adjlist = function(graph, mode = 3L, loops = 1L, multiple = TRUE) {
  .Call(`_igraphlite_as_adjlist_`, graph, mode, loops, multiple)
}

#' @returns `as_inclist()` returns a list of incident edges for each vertex.
#' @rdname adjlist
#' @export
as_inclist = function(graph, mode = 3L, loops = 1L) {
  .Call(`_igraphlite_as_inclist_`, graph, mode, loops)
}
