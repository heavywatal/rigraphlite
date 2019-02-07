#' The degree of some vertices in a graph
#'
#' This function calculates the in-, out- or total degree of the specified vertices.
#' @param graph IGraph object.
#' @param vids vertices of which the degree will be calculated.
#' @param mode edge type to count; {1: out, 2: in, 3: all}
#' @param loops whether self-loop should be counted.
#' @export
degree = function(graph, vids = numeric(0), mode = 3L, loops = TRUE) {
  graph$degree(vids, mode, loops)
}

neighbors = function(graph, v, mode = 3L) {
  graph$neighbors(v, mode)
}
