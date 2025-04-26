#' Miscellaneous operators
#'
#' `induced_subgraph()` can be achieved in two steps with
#' `induced_subgraph_edges()` and `subgraph_from_edges()`,
#' but it is much slower than expected.
#' @source <https://igraph.org/c/doc/igraph-Operators.html#miscellaneous-operators>
#' @seealso [delete_vertices()]
#' @inheritParams common_params
#' @param impl An integer value, how to construct a new graph:
#'             \{0: AUTO, 1: COPY_AND_DELETE, 2: CREATE_FROM_SCRATCH\}
#' @returns An [`igraph_ptr`] object.
#' @rdname subgraph
#' @export
#' @examples
#' g = graph_tree(5L)
#' induced_subgraph(g, seq_len(3L))
#'
#' edges = induced_subgraph_edges(g, seq_len(3L)) |> print()
#'
#' subgraph_from_edges(g, edges)
induced_subgraph = function(graph, vids, impl = 0L) {
  .Call(`_igraphlite_induced_subgraph_`, graph, sort(vids), impl) |> set_ptr_class()
}

#' @rdname subgraph
#' @export
induced_subgraph_edges = function(graph, vids) {
  .Call(`_igraphlite_induced_subgraph_edges_`, graph, vids)
}

#' @param delete_vertices whether to delete the unused vertices.
#' @rdname subgraph
#' @export
subgraph_from_edges = function(graph, eids, delete_vertices = TRUE) {
  .Call(`_igraphlite_subgraph_from_edges_`, graph, eids, delete_vertices) |> set_ptr_class()
}
