#' Common parameters used throughout the package
#'
#' This function does nothing. It is designed to be used with @@inheritParams.
#' @param graph igraph_ptr object.
#' @param vids Vertices of interest.
#' @param vid  Vertices of interest.
#' @param from Vertices of interest.
#' @param to   Vertices of interest.
#' @param eids Edges of interest.
#' @param eid  Edges of interest.
#' @param mode Edge type to count; \{1: OUT, 2: IN, 3: ALL\}.
#' @param weights Numeric edge weights; `TRUE` to use `Eattr(graph, "weight")`.
#' @param directed Boolean, whether to consider directed paths. Ignored for undirected graphs.
#' @param loops How to treat loop edges; \{0: NO_LOOPS, 1: LOOPS, 2: LOOPS_ONCE\}
#' @param multiple Boolean, whether to keep multiple (parallel) edges.
#' @keywords internal
common_params = function(graph, vids, vid, from, to, eids, eid, mode, weights, directed, loops, multiple) {
  invisible(NULL)
}

split_at = function(x, pos) {
  unname(split(x, findInterval(seq_along(x), pos + 1L)))
}

`%||%` = function(x, y) if (is.null(x)) y else x
