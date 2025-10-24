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
#'
#' edges(g, c(1L, 3L))
#'
#' get_eids(g, c(1L, 2L, 2L, 4L))
#'
#' get_all_eids_between(g, 1L, 2L)
#'
#' neighbors(g, 1L)
#'
#' incident(g, 1L)
#'
#' degree(g, mode = 1L)
#'
#' degree(g, mode = 2L)
#'
#' degree(g, mode = 3L)
#' @returns `edge()` and `edges()` return the head and tail vertices of edges.
#' @rdname basic-adjacent
#' @export
edge = function(graph, eid) {
  .Call(`_igraphlite_edge_`, graph, eid)
}

#' @param bycol A logical value to specify the result format.
#' If `FALSE` (default), the result is an edge list compatible with `add_edges()`.
#' If `TRUE`, the result is suitable for making a 2-column matrix as returned by
#' `as.matrix.igraph_ptr()`.
#' @rdname basic-adjacent
#' @export
edges = function(graph, eids = integer(0), bycol = FALSE) {
  .Call(`_igraphlite_edges_`, graph, eids, bycol)
}

#' @param error A logical value, whether to raise an error or assign `0` for
#' non-existing edges.
#' @returns `get_eids()` returns the edge IDs of given vertex pairs.
#' @rdname basic-adjacent
#' @export
get_eids = function(graph, edges, directed = is_directed(graph), error = TRUE) {
  .Call(`_igraphlite_get_eids_`, graph, edges, directed, error)
}

#' @returns `get_all_eids_between()` returns all edge IDs between two vertices.
#' @rdname basic-adjacent
#' @export
get_all_eids_between = function(graph, from, to, directed = is_directed(graph)) {
  .Call(`_igraphlite_get_all_eids_between_`, graph, from, to, directed)
}

#' @returns `neighbors()` returns the adjacent vertices to a vertex.
#' @rdname basic-adjacent
#' @export
neighbors = function(graph, vid, mode = 3L, loops = 1L, multiple = TRUE) {
  .Call(`_igraphlite_neighbors_`, graph, vid, mode, loops, multiple)
}

#' @returns `incident()` returns the incident edges of a vertex.
#' @rdname basic-adjacent
#' @export
incident = function(graph, vid, mode = 3L, loops = 1L) {
  .Call(`_igraphlite_incident_`, graph, vid, mode, loops)
}

#' @returns `degree()` returns the degrees of vertices in a graph.
#' @param loops whether self-loop should be counted.
#' @rdname basic-adjacent
#' @seealso [is_sink()], [is_source()], [Vsink()], [Vsource()] for shortcuts to
#' get zero-degree vertices.
#' @export
degree = function(graph, vids = integer(0), mode = 3L, loops = 1L) {
  .Call(`_igraphlite_degree_`, graph, vids, mode, loops)
}

#' Miscellaneous macros
#'
#' igraphlite uses 32-bit igraph,
#' which limits the maximum number of vertices to `2 ** 31 - 2`.
#' @source <https://igraph.org/c/doc/igraph-Basic.html#misc-helper-functions>
#' @name basic-macros
#' @rdname basic-macros
#' @examples
#' IGRAPH_VCOUNT_MAX
#'
#' IGRAPH_ECOUNT_MAX
#'
#' IGRAPH_UNLIMITED
#'
#' expand_path_to_pairs(seq_len(4L))
#'
#' g1 = graph_create(c(1L, 2L, 1L, 3L), directed = FALSE)
#' g2 = graph_create(c(3L, 2L, 3L, 1L), directed = FALSE)
#' g3 = graph_create(c(3L, 1L, 3L, 2L), directed = FALSE)
#' isomorphic(g1, g2)
#'
#' is_same_graph(g1, g2)
#'
#' is_same_graph(g2, g3)
"IGRAPH_VCOUNT_MAX"

#' @format NULL
#' @rdname basic-macros
"IGRAPH_ECOUNT_MAX"

#' @format NULL
#' @rdname basic-macros
"IGRAPH_UNLIMITED"

#' @inheritParams common_params
#' @rdname basic-macros
#' @export
expand_path_to_pairs = function(vids) {
  .Call(`_igraphlite_expand_path_to_pairs_`, vids)
}

#' @param graph1,graph2 Two [`igraph_ptr`] objects to compare.
#' @returns `is_same_graph()` returns a logical value.
#' It verifies that the two graphs have the same directedness,
#' the same number of vertices, and that they contain precisely the same edges
#' (regardless of their ordering) when written in terms of vertex indices.
#' Graph attributes are not taken into account.
#' @seealso [isomorphic()] and [subisomorphic()].
#' @rdname basic-macros
#' @export
is_same_graph = function(graph1, graph2) {
  .Call(`_igraphlite_is_same_graph_`, graph1, graph2)
}
