#' Adding and deleting vertices and edges
#'
#' @name basic-add-delete
#' @source <https://igraph.org/c/html/latest/igraph-Basic.html#adding-and-deleting-vertices-and-edges>
#' @inheritParams common_params

#' @returns A modified graph.
#' @rdname basic-add-delete
#' @export
add_edges = function(graph, eids) {
  .Call(`_igraphlite_add_edges_`, graph, eids)
}

#' @param n number of vertices to add.
#' @rdname basic-add-delete
#' @export
add_vertices = function(graph, n) {
  .Call(`_igraphlite_add_vertices_`, graph, n)
}

#' @rdname basic-add-delete
#' @export
delete_edges = function(graph, eids) {
  .Call(`_igraphlite_delete_edges_`, graph, eids)
}

#' @rdname basic-add-delete
#' @export
delete_vertices = function(graph, vids) {
  .Call(`_igraphlite_delete_vertices_`, graph, vids)
}
