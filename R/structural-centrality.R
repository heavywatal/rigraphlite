#' Centrality measures
#'
#' The betweenness centrality of a vertex or an edge is the number of geodesics
#' going through it.
#' @source <https://igraph.org/c/doc/igraph-Structural.html#centrality-measures>
#' @param ... Unused, but temporarily included to avoid silent bugs and
#'   to prompt users to cope with breaking changes in version 1.0.
#' @param cutoff Maximum length of paths to be considered. Unlimited if negative.
#' @inheritParams common_params
#' @examples
#' g = graph_tree(5L)
#' betweenness(g)
#' edge_betweenness(g)
#' edge_betweenness(g, from = Vsource(g), to = Vsink(g))
#' edge_betweenness(g, normalized = TRUE)
#' edge_betweenness(g, cutoff = 1)
#' @name centrality
#' @returns `betweenness()` returns a numeric vector of betweenness
#' for each vertex in the graph.
#' @rdname centrality
#' @export
betweenness = function(
  graph, ..., weights = numeric(0), from = integer(0), to = integer(0), vids = integer(0),
  directed = is_directed(graph), normalized = FALSE, cutoff = -1
) {
  if (!missing(...)) {
    stop("Use named arguments to cope with breaking changes in 1.0.", call. = FALSE)
  }
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  if (missing(from) && missing(to)) {
    .Call(`_igraphlite_betweenness_`, graph, as.numeric(weights), vids, directed, normalized, cutoff)
  } else {
    if (!missing(cutoff)) {
      warning("`cutoff` is ignored when `from` or `to` is specified.", call. = FALSE)
    }
    .Call(`_igraphlite_betweenness_subset_`, graph, as.numeric(weights), from, to, vids, directed, normalized)
  }
}

#' @returns `edge_betweenness()` returns a numeric vector of edge betweenness
#' for each edge in the graph.
#' @rdname centrality
#' @export
edge_betweenness = function(
  graph, ..., weights = numeric(0), from = integer(0), to = integer(0), eids = integer(0),
  directed = is_directed(graph), normalized = FALSE, cutoff = -1
) {
  if (!missing(...)) {
    stop("Use named arguments to cope with breaking changes in 1.0.", call. = FALSE)
  }
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  if (missing(from) && missing(to)) {
    .Call(`_igraphlite_edge_betweenness_`, graph, as.numeric(weights), eids, directed, normalized, cutoff)
  } else {
    if (!missing(cutoff)) {
      warning("`cutoff` is ignored when `from` or `to` is specified.", call. = FALSE)
    }
    .Call(`_igraphlite_edge_betweenness_subset_`, graph, as.numeric(weights), from, to, eids, directed, normalized)
  }
}

#' @returns `edge_betweenness_subset()` is a variant of `edge_betweenness()`
#' that computes the betweenness using a subset of paths between `from` and `to`.
#' @rdname centrality
#' @export
edge_betweenness_subset = function(
  graph, ..., weights = numeric(0), from = integer(0), to = integer(0), eids = integer(0),
  directed = is_directed(graph), normalized = FALSE
) {
  if (!missing(...)) {
    stop("Use named arguments to cope with breaking changes in 1.0.", call. = FALSE)
  }
  warning("`edge_betweenness_subset()` is deprecated; use `edge_betweenness()` instead.", call. = FALSE)
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_edge_betweenness_subset_`, graph, as.numeric(weights), from, to, eids, directed, normalized)
}
