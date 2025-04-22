#' Shortest Path Related Functions
#'
#' `get_shortest_paths()` returns a single shortest path per vertex pair,
#' while the variant with `_all_` returns all found paths.
#' The variant with `_simple_` removes paths with cycles.
#' The results should be the same for simple graphs like trees, but the order of
#' the paths may differ.
#' @source <https://igraph.org/c/doc/igraph-Structural.html#shortest-path-related-functions>
#' @inheritParams common_params
#' @returns A list of integer IDs of vertices in the paths.
#' @examples
#' g = graph_tree(5L)
#' vsource = Vsource(g)
#' vsink = Vsink(g)
#' get_shortest_paths(g, vsource, vsink, mode = 1L)
#' get_all_shortest_paths(g, vsource, vsink, mode = 1L)
#' get_all_simple_paths(g, vsource, vsink, mode = 1L)
#' @name paths
#' @rdname paths
#' @export
get_shortest_paths = function(graph, from, to = integer(0L), weights = numeric(0L), mode = 3L) {
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_get_shortest_paths_`, graph, from, to, as.numeric(weights), mode)
}

#' @rdname paths
#' @export
get_all_shortest_paths = function(graph, from, to = integer(0L), weights = numeric(0L), mode = 3L) {
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_get_all_shortest_paths_`, graph, from, to, as.numeric(weights), mode)
}

#' @param cutoff integer
#' @rdname paths
#' @export
get_all_simple_paths = function(graph, from, to = integer(0L), cutoff = -1L, mode = 3L) {
  res = .Call(`_igraphlite_get_all_simple_paths_`, graph, from, to, cutoff, mode)
  pos = which(res == 0L)
  split_at(res[-pos], pos - seq_along(pos))
}
