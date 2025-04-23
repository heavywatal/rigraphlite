#' Graph constructors
#'
#' @description
#' `graph_empty()` creates an empty graph with a specified number of vertices.
#' An empty graph in *igraph* is a graph with no edges, which may have vertices.
#'
#' `graph_copy()` creates a deep copy of the graph.
#' Normal assignment like `g2 = g1` creates a shallow copy, which means that
#' the internal data is shared between the two R objects, and the modification
#' on one of them will affect the other.
#' @family deterministic generators
#' @param n An integer, the number of vertices in the graph.
#' @inheritParams common_params
#' @returns An [`igraph_ptr`] object.
#' @examples
#' g = graph_empty(4L)
#' g
#'
#' g_shallow = g
#' g_deep = graph_copy(g)
#' add_edges(g, seq_len(4L))
#'
#' g_shallow
#'
#' g_deep
#' @rdname constructors
#' @export
graph_empty = function(n = 0L, directed = TRUE) {
  .Call(`_igraphlite_graph_empty_`, n, directed) |> set_ptr_class()
}

#' @rdname constructors
#' @export
graph_copy = function(graph) {
  .Call(`_igraphlite_graph_copy_`, graph) |> set_ptr_class()
}
