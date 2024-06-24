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
  .Call(`_igraphlite_layout_random_`, graph)
}

#' @rdname layout
#' @export
layout_drl = function(graph) {
  .Call(`_igraphlite_layout_drl_`, graph)
}

#' @param grid Whether to use the (fast but less accurate) grid based version;
#'  \{0: GRID, 1: NOGRID, 2: AUTOGRID\}.
#' @rdname layout
#' @export
layout_fruchterman_reingold = function(graph, grid = 2L) {
  .Call(`_igraphlite_layout_fruchterman_reingold_`, graph, grid = grid)
}

#' @param dist A distant matrix.
#' @rdname layout
#' @export
layout_mds = function(graph, dist) {
  .Call(`_igraphlite_layout_mds_`, graph, dist)
}

#' @param roots Root vertices.
#' @rdname layout
#' @export
layout_reingold_tilford = function(graph, mode = 1L, roots = integer(0)) {
  .Call(`_igraphlite_layout_reingold_tilford_`, graph, mode, roots)
}

#' @rdname layout
#' @export
layout_reingold_tilford_circular = function(graph, mode = 1L, roots = integer(0)) {
  .Call(`_igraphlite_layout_reingold_tilford_circular_`, graph, mode, roots)
}
