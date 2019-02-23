#' Common parameters used throughout the package
#'
#' This function does nothing. It is designed to be used with @@inheritParams.
#' @param graph IGraph object.
#' @param vids Vertices of interest.
#' @param v    Vertices of interest.
#' @param from Vertices of interest.
#' @param to   Vertices of interest.
#' @param mode Edge type to count; {1: OUT, 2: IN, 3: ALL}.
#' @param weights Numeric edge weights; `TRUE` to use `graph$Eattr$weight`.
#' @param directed Boolean, whether to consider directed paths. Ignored for undirected graphs.
#' @keywords internal
common_params = function(graph, vids, v, from, to, mode, weights, directed) {
  invisible(NULL)
}
