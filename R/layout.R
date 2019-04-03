#' Layouts for Graph Drawing
#'
#' @source <https://igraph.org/c/doc/igraph-Layout.html>
#' @inheritParams common_params
#' @param ... Passed to an internal layout function.
#' @rdname layout
#' @export
layout_nicely = function(graph, ...) {
  layout_fruchterman_reingold(graph, ...)
}

#' @rdname layout
#' @export
layout_random = function(graph) {
  graph$layout_random()
}

#' @rdname layout
#' @export
layout_drl = function(graph) {
  graph$layout_drl()
}

#' @param grid Whether to use the (fast but less accurate) grid based version;
#'   {0: GRID, 1: NOGRID, 2: AUTOGRID}.
#' @rdname layout
#' @export
layout_fruchterman_reingold = function(graph, grid = 2L) {
  graph$layout_fruchterman_reingold(grid = grid)
}

#' @rdname layout
#' @export
layout_mds = function(graph) {
  graph$layout_mds()
}

#' @rdname layout
#' @export
layout_reingold_tilford = function(graph, mode = 1L) {
  graph$layout_reingold_tilford(mode = mode)
}

#' @rdname layout
#' @export
layout_reingold_tilford_circular = function(graph, mode = 1L) {
  graph$layout_reingold_tilford_circular(mode = mode)
}
