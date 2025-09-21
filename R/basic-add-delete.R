#' Adding and deleting vertices and edges
#'
#' Unlike many other R functions, these functions modify a graph in place.
#' The shallow copy of the graph is returned invisibly, which can be used with
#' the pipe operator, but does not need to be assigned to a variable.
#' @source <https://igraph.org/c/html/latest/igraph-Basic.html#adding-and-deleting-vertices-and-edges>
#' @inheritParams common_params
#' @seealso [graph_copy()] for shallow vs. deep copy of graph objects.

#' @returns A shallow copy of the modified [`igraph_ptr`] object.
#' @examples
#' g = graph_empty()
#'
#' # The graph is modified in place
#' add_vertices(g, 6L)
#' add_edges(g, c(1L, 2L))
#' g
#'
#' # Invisibly returned objects can be used with the pipe operator.
#' g |>
#'   add_edges(c(3L, 4L)) |>
#'   delete_edges(1L) |>
#'   delete_vertices(6L) |>
#'   print()
#'
#' # No need to assign the result
#' g
#' @name add-delete
#' @rdname basic-add-delete
#' @export
add_edges = function(graph, edges) {
  .Call(`_igraphlite_add_edges_`, graph, edges)
  invisible(graph)
}

#' @param n An integer, the number of vertices to add.
#' @rdname basic-add-delete
#' @export
add_vertices = function(graph, n) {
  .Call(`_igraphlite_add_vertices_`, graph, n)
  invisible(graph)
}

#' @rdname basic-add-delete
#' @export
delete_edges = function(graph, eids) {
  .Call(`_igraphlite_delete_edges_`, graph, eids)
  invisible(graph)
}

#' @rdname basic-add-delete
#' @export
delete_vertices = function(graph, vids) {
  .Call(`_igraphlite_delete_vertices_`, graph, vids)
  invisible(graph)
}
