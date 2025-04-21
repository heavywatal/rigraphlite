#' Convert edge lists to igraph objects.
#'
#' An edge list is a two-column matrix or data.frame where the first column
#' contains the source vertices and the second column contains the target
#' vertices.
#' @seealso [as.data.frame.igraph_ptr()] and [as.matrix.igraph_ptr()]
#' do the opposite conversion.
#' @param edgelist An edge list in two-column matrix or data.frame format.
#' `graph_from_edgelist()` only accepts integer values,
#' interpreting them directly as vertex IDs starting from 1.
#' Other functions support non-numeric values, treating them as vertex names.
#' A data.frame may contain additional columns for edge attributes.
#' @param directed A logical.
#' @returns An igraph object.
#' @rdname conversion-impl
#' @export
#' @examples
#' edges = seq_len(6L) + 3L
#' edgelist = matrix(edges, ncol = 2L, byrow = TRUE)
#' g = graph_from_edgelist(edgelist) |> print()
#' stopifnot(all.equal(as.matrix(g), as.matrix(graph_create(edges))))
#'
#' symbolic = matrix(letters[edges], ncol = 2L)
#' graph_from_symbolic_edgelist(symbolic)
graph_from_data_frame = function(edgelist, directed = TRUE) {
  .Call(`_igraphlite_graph_from_data_frame_`, edgelist, directed) |> set_ptr_class()
}

#' @rdname conversion-impl
#' @export
graph_from_symbolic_edgelist = function(edgelist, directed = TRUE) {
  .Call(`_igraphlite_graph_from_symbolic_edgelist_`, edgelist, directed) |> set_ptr_class()
}

#' @rdname conversion-impl
#' @export
graph_from_edgelist = function(edgelist, directed = TRUE) {
  .Call(`_igraphlite_graph_from_edgelist_`, edgelist, directed) |> set_ptr_class()
}
