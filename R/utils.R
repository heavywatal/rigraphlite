#' Common parameters used throughout the package
#'
#' This function does nothing. It is designed to be used with @@inheritParams.
#' @param graph An [`igraph_ptr`] object.
#' @param vids An integer vector of vertex IDs.
#' @param vid  An integer value of vertex ID.
#' @param from An integer vector of vertex IDs.
#' @param to   An integer vector of vertex IDs.
#' @param eids An integer vector of edge IDs.
#' @param eid  An integer value of edge ID.
#' @param edges An integer vector of vertex IDs; the first two elements are the first edge, etc.
#' @param mode An integer value of edge type to count; \{1: OUT, 2: IN, 3: ALL\}.
#' @param weights A numeric vector of edge weights; `TRUE` to use `Eattr(graph, "weight")`.
#' @param directed A logical value, whether to consider directed paths.
#' Ignored for undirected graphs.
#' @param loops An integer value, how to treat loop edges;
#' \{0: NO_LOOPS, 1: LOOPS, 2: LOOPS_ONCE\}
#' @param multiple A logical value, whether to keep multiple (parallel) edges.
#' @keywords internal
common_params = function(graph, vids, vid, from, to, eids, eid, edges, mode, weights, directed, loops, multiple) {
  invisible(NULL)
}

split_at = function(x, pos) {
  unname(split(x, findInterval(seq_along(x), pos + 1L)))
}

`%||%` = function(x, y) if (is.null(x)) y else x
