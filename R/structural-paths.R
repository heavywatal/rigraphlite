#' Shortest Path Related Functions
#'
#' `get_shortest_paths()` returns a single shortest path per vertex pair,
#' while the variant with `_all_` returns all found paths.
#' The variant with `_simple_` removes paths with cycles.
#' The results should be the same for simple graphs like trees, but the order of
#' the paths may differ.
#' @source <https://igraph.org/c/doc/igraph-Structural.html#shortest-path-related-functions>
#' @param ... Unused, but temporarily included to avoid silent bugs and
#'   to prompt users to cope with breaking changes in version 1.0.
#' @inheritParams common_params
#' @returns A list of integer IDs of vertices in the paths.
#' @examples
#' g = graph_tree(5L)
#' vsource = Vsource(g)
#' vsink = Vsink(g)
#' get_shortest_paths(g, from = vsource, to = vsink, mode = 1L)
#' get_all_shortest_paths(g, from = vsource, to = vsink, mode = 1L)
#' get_all_simple_paths(g, from = vsource, to = vsink, mode = 1L)
#' @name paths
#' @rdname paths
#' @export
get_shortest_paths = function(graph, ..., weights = numeric(0L), from = integer(0L), to = integer(0L), mode = 3L) {
  if (!missing(...)) {
    stop("Use named arguments to cope with breaking changes in 1.0.", call. = FALSE)
  }
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_get_shortest_paths_`, graph, as.numeric(weights), from, to, mode)
}

#' @rdname paths
#' @export
get_all_shortest_paths = function(graph, ..., weights = numeric(0L), from = integer(0L), to = integer(0L), mode = 3L) {
  if (!missing(...)) {
    stop("Use named arguments to cope with breaking changes in 1.0.", call. = FALSE)
  }
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_get_all_shortest_paths_`, graph, as.numeric(weights), from, to, mode)
}

#' @param minlen Minimum length of paths that is considered. Unlimited if negative.
#' @param maxlen Maximum length of paths that is considered. Unlimited if negative.
#' @param max_results At most this many paths will be recorded. Unlimited if negative.
#' @rdname paths
#' @export
get_all_simple_paths = function(
    graph, from, to = integer(0L), mode = 3L,
    minlen = -1L, maxlen = -1L, max_results = -1L) {
  .Call(`_igraphlite_get_all_simple_paths_`, graph, from, to, mode, minlen, maxlen, max_results)
}
