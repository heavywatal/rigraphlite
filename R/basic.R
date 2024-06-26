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
  .Call(`_igraphlite_vcount_`, graph)
}

#' @details
#' `ecount()`: The number of edges in a graph.
#' @rdname basic
#' @export
ecount = function(graph) {
  .Call(`_igraphlite_ecount_`, graph)
}

#' @rdname basic
#' @export
igraph_from = function(graph) {
  .Call(`_igraphlite_from_`, graph)
}

#' @rdname basic
#' @export
igraph_to = function(graph) {
  .Call(`_igraphlite_to_`, graph)
}

#' @details
#' `edge()`: Gives the head and tail vertices of an edge.
#' @rdname basic
#' @export
edge = function(graph, eid) {
  .Call(`_igraphlite_edge_`, graph, eid)
}

#' @details
#' `neighbors()`: Adjacent vertices to a vertex.
#' @rdname basic
#' @export
neighbors = function(graph, vid, mode = 3L) {
  .Call(`_igraphlite_neighbors_`, graph, vid, mode)
}

#' @details
#' `incident()`: Gives the incident edges of a vertex.
#' @rdname basic
#' @export
incident = function(graph, vid, mode = 3L) {
  .Call(`_igraphlite_incident_`, graph, vid, mode)
}

#' @details
#' `is_directed()`: Is this a directed graph?
#' @rdname basic
#' @export
is_directed = function(graph) {
  .Call(`_igraphlite_is_directed_`, graph)
}

#' @details
#' `degree()`: The degree of some vertices in a graph.
#' @param loops whether self-loop should be counted.
#' @rdname basic
#' @export
degree = function(graph, vids = integer(0), mode = 3L, loops = TRUE) {
  .Call(`_igraphlite_degree_`, graph, vids, mode, loops)
}

#' @param n number of vertices to add.
#' @rdname basic
#' @export
add_vertices = function(graph, n) {
  .Call(`_igraphlite_add_vertices_`, graph, n)
}

#' @rdname basic
#' @export
add_edges = function(graph, eids) {
  .Call(`_igraphlite_add_edges_`, graph, eids)
}

#' @rdname basic
#' @export
delete_vertices = function(graph, vids) {
  .Call(`_igraphlite_delete_vertices_`, graph, vids)
}

#' @rdname basic
#' @export
delete_edges = function(graph, eids) {
  .Call(`_igraphlite_delete_edges_`, graph, eids)
}
