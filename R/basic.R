#' Basic Query Operations
#'
#' @name basic-query
#' @seealso [as_adjlist()] and [as_inclist()] for the all-vertices version of
#' `neighbors()` and `incident()`.
#' @source <https://igraph.org/c/doc/igraph-Basic.html>
#' @inheritParams common_params

#' @returns `vcount()` returns the number of vertices in a graph.
#' @rdname basic
#' @export
vcount = function(graph) {
  .Call(`_igraphlite_vcount_`, graph)
}

#' @returns `ecount()` returns the number of edges in a graph.
#' @rdname basic
#' @export
ecount = function(graph) {
  .Call(`_igraphlite_ecount_`, graph)
}

#' @returns `is_directed()` returns whether the graph is directed.
#' @rdname basic
#' @export
is_directed = function(graph) {
  .Call(`_igraphlite_is_directed_`, graph)
}

#' @returns `edge()` returns the head and tail vertices of an edge.
#' @rdname basic
#' @export
edge = function(graph, eid) {
  .Call(`_igraphlite_edge_`, graph, eid)
}

#' @returns `neighbors()` returns the adjacent vertices to a vertex.
#' @rdname basic
#' @export
neighbors = function(graph, vid, mode = 3L) {
  .Call(`_igraphlite_neighbors_`, graph, vid, mode)
}

#' @returns `incident()` returns the incident edges of a vertex.
#' @rdname basic
#' @export
incident = function(graph, vid, mode = 3L) {
  .Call(`_igraphlite_incident_`, graph, vid, mode)
}

#' @returns `degree()` returns the degrees of vertices in a graph.
#' @param loops whether self-loop should be counted.
#' @rdname basic
#' @export
degree = function(graph, vids = integer(0), mode = 3L, loops = TRUE) {
  .Call(`_igraphlite_degree_`, graph, vids, mode, loops)
}
