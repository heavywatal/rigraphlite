#' Basic interface
#'
#' @details
#' `neighbors()`: Adjacent vertices to a vertex.
#' @param graph IGraph object.
#' @param v,vids vertices of which the degree will be calculated.
#' @param mode edge type to count; {1: out, 2: in, 3: all}
#' @param loops whether self-loop should be counted.
#' @rdname basic
#' @export
neighbors = function(graph, v, mode = 3L) {
  graph$neighbors(v, mode)
}

#' @details
#' `degree()`: The degree of some vertices in a graph.
#' @rdname basic
#' @export
degree = function(graph, vids = numeric(0), mode = 3L, loops = TRUE) {
  graph$degree(vids, mode, loops)
}
