#' Basic interface
#'
#' @seealso `as_adjlist` and `as_inclist` for all-vertices version.
#' @details
#' `neighbors()`: Adjacent vertices to a vertex.
#' @param graph IGraph object.
#' @param v,vids vertices of which the degree will be calculated.
#' @param mode edge type to count; {1: out, 2: in, 3: all}
#' @param loops whether self-loop should be counted.
#' @rdname basic
#' @export
neighbors = function(graph, v, mode = 3L) {
  graph$neighbors(v, mode)
}

#' @details
#' `incident()`: Gives the incident edges of a vertex.
#' @rdname basic
#' @export
incident = function(graph, v, mode = 3L) {
  graph$incident(v, mode)
}

#' @details
#' `degree()`: The degree of some vertices in a graph.
#' @rdname basic
#' @export
degree = function(graph, vids = numeric(0), mode = 3L, loops = TRUE) {
  graph$degree(vids, mode, loops)
}


#' Adjacency lists
#'
#' These functions are all-vertices version of `neighbors()` and `incident()`.
#' @seealso `neighbors`, `incident`
#' @details
#' `as_adjlist()`: Convert a graph to a list of adjacent vertices.
#' @param graph IGraph object.
#' @param mode edge type to count; {1: out, 2: in, 3: all}
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
