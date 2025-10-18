#' Distance-related Functions
#'
#' `average_path_length()` and `path_length_hist()` can be computed with the
#' result of `distances()`, but should be faster as they are written in C.
#' @source <https://igraph.org/c/doc/igraph-Structural.html#shortest-path-related-functions>
#' @param ... Unused, but temporarily included to avoid silent bugs and
#'   to prompt users to cope with breaking changes in version 1.0.
#' @param cutoff Maximum length of paths to be considered. Unlimited if negative.
#' @inheritParams common_params
#' @examples
#' g = graph_tree(5L)
#' distances(g, mode = 1L)
#' average_path_length(g)
#' path_length_hist(g)
#' diameter(g)
#' girth(g)
#' radius(g)
#' eccentricity(g)
#' @returns `distances()` returns a matrix of distances between the vertices.
#' @name distances
#' @rdname distances
#' @export
distances = function(graph, ..., weights = numeric(0L), from = integer(0L), to = from, mode = 3L, cutoff = -1) {
  if (!missing(...)) {
    stop("Use named arguments to cope with breaking changes in 1.0.", call. = FALSE)
  }
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_distances_`, graph, as.numeric(weights), from, to, mode, cutoff)
}

#' @param unconn A logical value.
#' @returns `average_path_length()` returns a numeric value.
#' @rdname distances
#' @export
average_path_length = function(graph, ..., weights = numeric(0L), directed = is_directed(graph), unconn = TRUE) {
  if (!missing(...)) {
    stop("Use named arguments to cope with breaking changes in 1.0.", call. = FALSE)
  }
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_average_path_length_`, graph, as.numeric(weights), directed, unconn)
}

#' @returns `path_length_hist()` returns an integer vector.
#' @rdname distances
#' @export
path_length_hist = function(graph, directed = is_directed(graph)) {
  .Call(`_igraphlite_path_length_hist_`, graph, directed)
}

#' @rdname distances
#' @export
eccentricity = function(graph, weights = numeric(0L), vids = integer(0L), mode = 3L) {
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_eccentricity_`, graph, as.numeric(weights), vids, mode)
}

#' @rdname distances
#' @export
diameter = function(graph, weights = numeric(0L), directed = is_directed(graph), unconn = TRUE) {
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_diameter_`, graph, as.numeric(weights), directed, unconn)
}

#' @rdname distances
#' @export
girth = function(graph) {
  .Call(`_igraphlite_girth_`, graph)
}

#' @rdname distances
#' @export
radius = function(graph, weights = numeric(0L), mode = 3L) {
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_radius_`, graph, as.numeric(weights), mode)
}
