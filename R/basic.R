#' Basic Query Operations
#'
#' @seealso [as_adjlist()] and [as_inclist()] for all-vertices version.
#' @source <https://igraph.org/c/doc/igraph-Basic.html>
#' @inheritParams common_params

#' @details
#' `vcount()`: The number of vertices in a graph.
#' @rdname basic
#' @export
vcount = function(graph) {
  vcount_(graph)
}

#' @details
#' `ecount()`: The number of edges in a graph.
#' @rdname basic
#' @export
ecount = function(graph) {
  ecount_(graph)
}

#' @rdname basic
#' @export
igraph_from = function(graph) {
  from_(graph)
}

#' @rdname basic
#' @export
igraph_to = function(graph) {
  to_(graph)
}

#' @details
#' `edge()`: Gives the head and tail vertices of an edge.
#' @rdname basic
#' @export
edge = function(graph, eid) {
  graph$edge(eid)
}

#' @details
#' `neighbors()`: Adjacent vertices to a vertex.
#' @rdname basic
#' @export
neighbors = function(graph, vid, mode = 3L) {
  graph$neighbors(vid, mode)
}

#' @details
#' `incident()`: Gives the incident edges of a vertex.
#' @rdname basic
#' @export
incident = function(graph, vid, mode = 3L) {
  graph$incident(vid, mode)
}

#' @details
#' `is_directed()`: Is this a directed graph?
#' @rdname basic
#' @export
is_directed = function(graph) {
  graph$is_directed
}

#' @details
#' `degree()`: The degree of some vertices in a graph.
#' @param loops whether self-loop should be counted.
#' @rdname basic
#' @export
degree = function(graph, vids = integer(0), mode = 3L, loops = TRUE) {
  graph$degree(vids, mode, loops)
}
