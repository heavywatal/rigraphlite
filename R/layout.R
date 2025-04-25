#' Choose a layout algorithm automatically
#'
#' Layout functions add `x` and `y` vertex attributes to the graph object.
#' The object is modified in place, and its shallow copy is returned.
#' @source <https://r.igraph.org/reference/layout_nicely.html>
#' @inheritParams common_params
#' @param ... Additional arguments passed to the layout function.
#' @returns An [`igraph_ptr`] object with vertex attributes `x` and `y`.
#' @family layouts
#' @rdname layout
#' @export
#' @examples
#' layout_nicely(graph_tree(5L)) |> Vattr()
layout_nicely = function(graph, ...) {
  if (all(c("x", "y") %in% names(Vattr(graph)))) {
    return(graph)
  }
  if (vcount(graph) < 1000L) {
    layout_fruchterman_reingold(graph, ...)
  } else {
    layout_drl(graph, ...)
  }
}

#' 2D layout generators
#'
#' Layout functions add `x` and `y` vertex attributes to the graph object.
#' The object is modified in place, and its shallow copy is returned.
#' @source <https://igraph.org/c/doc/igraph-Layout.html#two-d-layout-generators>
#' @inheritParams common_params
#' @returns An [`igraph_ptr`] object with vertex attributes `x` and `y`.
#' @family layouts
#' @rdname layout-2d
#' @export
#' @examples
#' igraph_rng_seed(24601L)
#' g = graph_tree(5L)
#'
#' layout_random(g) |> Vattr()
#'
#' layout_drl(g) |> Vattr()
#'
#' layout_fruchterman_reingold(g) |> Vattr()
#'
#' layout_mds(g, dist = distances(g)) |> Vattr()
layout_random = function(graph) {
  .Call(`_igraphlite_layout_random_`, graph)
  graph
}

#' @rdname layout-2d
#' @export
layout_drl = function(graph) {
  .Call(`_igraphlite_layout_drl_`, graph)
  graph
}

#' @param grid An integer value, whether to use the (fast but less accurate) grid based algorithm;
#'  \{0: GRID, 1: NOGRID, 2: AUTOGRID\}.
#' @rdname layout-2d
#' @export
layout_fruchterman_reingold = function(graph, grid = 2L) {
  .Call(`_igraphlite_layout_fruchterman_reingold_`, graph, grid = grid)
  graph
}

#' @param dist A distance matrix.
#' @rdname layout-2d
#' @export
layout_mds = function(graph, dist) {
  .Call(`_igraphlite_layout_mds_`, graph, dist)
  graph
}

#' Layouts for trees and acyclic graphs
#'
#' Layout functions add `x` and `y` vertex attributes to the graph object.
#' The object is modified in place, and its shallow copy is returned.
#' @source <https://igraph.org/c/doc/igraph-Layout.html#layouts-for-trees-and-acyclic-graphs>
#' @inheritParams common_params
#' @param roots An integer vector of vertex IDs, the roots of the tree.
#' @returns An [`igraph_ptr`] object with vertex attributes `x` and `y`.
#' @family layouts
#' @rdname layout-tree
#' @export
#' @examples
#' g = graph_tree(5L)
#'
#' layout_reingold_tilford(g) |> Vattr()
#'
#' layout_reingold_tilford_circular(g) |> Vattr()
layout_reingold_tilford = function(graph, mode = 1L, roots = integer(0)) {
  .Call(`_igraphlite_layout_reingold_tilford_`, graph, mode, roots)
  graph
}

#' @rdname layout-tree
#' @export
layout_reingold_tilford_circular = function(graph, mode = 1L, roots = integer(0)) {
  .Call(`_igraphlite_layout_reingold_tilford_circular_`, graph, mode, roots)
  graph
}
