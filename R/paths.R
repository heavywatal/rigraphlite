#' Shortest Path Related Functions
#'
#' @source <https://igraph.org/c/doc/igraph-Structural.html#shortest-path-related-functions>
#' @param algorithm character
#' @inheritParams common_params
#' @rdname paths
#' @export
distances = function(graph, from = integer(0L), to = from, weights = numeric(0L), mode = 3L,
                     algorithm = c("dijkstra", "bellman-ford", "johnson")) {
  algorithm = match.arg(algorithm)
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_distances_`, graph, from, to, as.numeric(weights), mode, algorithm)
}

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

#' @param unconn logical
#' @rdname paths
#' @export
average_path_length = function(graph, weights = numeric(0L), directed = FALSE, unconn = TRUE) {
  .Call(`_igraphlite_average_path_length_`, graph, weights, directed, unconn)
}

#' @rdname paths
#' @export
path_length_hist = function(graph, directed = FALSE) {
  .Call(`_igraphlite_path_length_hist_`, graph, directed)
}
