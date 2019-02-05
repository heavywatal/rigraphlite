#' Create new graph
#'
#' @param el two-column matrix
#' @param directed logical
#' @rdname constructors
#' @export
graph_from_edgelist = function(el, directed = TRUE) {
  edges = as.numeric(t(el)) - 1
  igraph_create(edges, directed = directed)
}

#' @rdname constructors
#' @export
graph_from_symbolic_edgelist = function(el, directed = TRUE) {
  edges = as.vector(t(el))
  labels = unique(edges)
  ids = seq_along(labels) - 1
  g = igraph_create(ids[edges], directed = directed)
  g$V$name = labels
  g
}
