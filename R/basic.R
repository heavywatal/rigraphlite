#' Basic query operations
#'
#' @name basic-query
#' @source <https://igraph.org/c/doc/igraph-Basic.html#basic-query-operations>
#' @inheritParams common_params
#' @examples
#' g = graph_tree(5L)
#' vcount(g)
#' ecount(g)
#' is_directed(g)

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

#' Basic query operations to get adjacency
#'
#' @name basic-adjacent
#' @seealso [as_adjlist()] and [as_inclist()] for the all-vertices version of
#' `neighbors()` and `incident()`.
#' @source <https://igraph.org/c/doc/igraph-Basic.html#basic-query-operations>
#' @inheritParams common_params
#' @examples
#' g = graph_tree(5L)
#' edge(g, 1L)
#' neighbors(g, 1L)
#' incident(g, 1L)
#' degree(g, mode = 1L)
#' degree(g, mode = 2L)
#' degree(g, mode = 3L)

#' @returns `edge()` returns the head and tail vertices of an edge.
#' @rdname basic-adjacent
#' @export
edge = function(graph, eid) {
  .Call(`_igraphlite_edge_`, graph, eid)
}

#' @returns `neighbors()` returns the adjacent vertices to a vertex.
#' @rdname basic-adjacent
#' @export
neighbors = function(graph, vid, mode = 3L) {
  .Call(`_igraphlite_neighbors_`, graph, vid, mode)
}

#' @returns `incident()` returns the incident edges of a vertex.
#' @rdname basic-adjacent
#' @export
incident = function(graph, vid, mode = 3L) {
  .Call(`_igraphlite_incident_`, graph, vid, mode)
}

#' @returns `degree()` returns the degrees of vertices in a graph.
#' @param loops whether self-loop should be counted.
#' @rdname basic-adjacent
#' @seealso [is_sink()], [is_source()], [Vsink()], [Vsource()] for shortcuts to
#' get zero-degree vertices.
#' @export
degree = function(graph, vids = integer(0), mode = 3L, loops = TRUE) {
  .Call(`_igraphlite_degree_`, graph, vids, mode, loops)
}
