#' Distance-related Functions
#'
#' `average_path_length()` and `path_length_hist()` can be computed with the
#' result of `distances()`, but should be faster as they are written in C.
#' @source <https://igraph.org/c/doc/igraph-Structural.html#shortest-path-related-functions>
#' @inheritParams common_params
#' @param algorithm A character string.
#' @examples
#' g = graph_tree(5L)
#' distances(g, mode = 1L)
#' average_path_length(g)
#' path_length_hist(g)
#' @returns `distances()` returns a matrix of distances between the vertices.
#' @name distances
#' @rdname distances
#' @export
distances = function(graph, from = integer(0L), to = from, weights = numeric(0L), mode = 3L,
                     algorithm = c("dijkstra", "bellman-ford", "johnson")) {
  algorithm = match.arg(algorithm)
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_distances_`, graph, from, to, as.numeric(weights), mode, algorithm)
}

#' @param unconn A logical value.
#' @returns `average_path_length()` returns a numeric value.
#' @rdname distances
#' @export
average_path_length = function(graph, weights = numeric(0L), directed = is_directed(graph), unconn = TRUE) {
  .Call(`_igraphlite_average_path_length_`, graph, weights, directed, unconn)
}

#' @returns `path_length_hist()` returns an integer vector.
#' @rdname distances
#' @export
path_length_hist = function(graph, directed = is_directed(graph)) {
  .Call(`_igraphlite_path_length_hist_`, graph, directed)
}
