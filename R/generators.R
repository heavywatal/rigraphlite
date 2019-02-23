#' Shortcut to deterministic graph generators
#'
#' @seealso [graph_create()], [graph_from_edgelist()], [graph_from_data_frame()]
#' @param x A vector, matrix, or data.frame.
#' @rdname as_igraph
#' @export
as_igraph = function(x) UseMethod("as_igraph")

#' @rdname as_igraph
#' @export
as_igraph.default = function(x) {
  graph_create(x)
}

#' @rdname as_igraph
#' @export
as_igraph.matrix = function(x) {
  if (is.double(x)) {
    graph_from_edgelist(x)
  } else {
    graph_from_symbolic_edgelist(x)
  }
}

#' @rdname as_igraph
#' @export
as_igraph.data.frame = function(x) {
  graph_from_data_frame(x)
}
