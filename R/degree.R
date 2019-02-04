#' The degree of some vertices in a graph
#'
#' This function calculates the in-, out- or total degree of the specified vertices.
#' @param graph IGraph object.
#' @param vs vertices of which the degree will be calculated.
#' @param mode type of the degree.
#' @param loops whether self-loop should be counted.
#' @export
degree = function(graph, vs = NA, mode = c("all", "out", "in", "total"), loops = TRUE) {
  mode = match.arg(mode)
  mode = switch(mode, out = 1L, `in` = 2L, all = 3L, total = 3L)
  if (isTRUE(is.na(vs))) {
    impl_degree_all(graph, mode = mode, loops = loops)
  } else {
    impl_degree(graph, vs - 1, mode = mode, loops = loops)
  }
}
