#' Create graph from R objects
#'
#' @seealso [graph_create()], [as.data.frame.igraph_ptr()]
#' @param x A vector, matrix, or data.frame.
#' @param ... Additional arguments passed to the graph creation function.
#' @rdname as_igraph
#' @export
as_igraph = function(x, ...) UseMethod("as_igraph")

#' @rdname as_igraph
#' @export
as_igraph.default = function(x, ...) {
  graph_create(x, ...)
}

#' @rdname as_igraph
#' @export
as_igraph.matrix = function(x, ...) {
  if (is.numeric(x)) {
    graph_from_edgelist(x, ...)
  } else {
    graph_from_symbolic_edgelist(x, ...)
  }
}

#' @rdname as_igraph
#' @export
as_igraph.data.frame = function(x, ...) {
  graph_from_data_frame(x, ...)
}

#' @param df data.frame that includes an edgelist and edge attributes.
#' @param edgelist Two-column matrix.
#' @param directed Boolean
#' @rdname as_igraph
#' @export
graph_from_data_frame = function(df, directed = TRUE) {
  .Call(`_igraphlite_graph_from_data_frame_`, df, directed) |> set_ptr_class()
}

#' @rdname as_igraph
#' @export
graph_from_symbolic_edgelist = function(edgelist, directed = TRUE) {
  .Call(`_igraphlite_graph_from_symbolic_edgelist_`, edgelist, directed) |> set_ptr_class()
}

#' @rdname as_igraph
#' @export
graph_from_edgelist = function(edgelist, directed = TRUE) {
  .Call(`_igraphlite_graph_from_edgelist_`, edgelist, directed) |> set_ptr_class()
}
