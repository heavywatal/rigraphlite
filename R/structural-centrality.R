#' Centrality measures
#'
#' The betweenness centrality of an edge is the number of geodesics going through it.
#' @source <https://igraph.org/c/doc/igraph-Structural.html#centrality-measures>
#' @param ... Unused, but temporarily included to avoid silent bugs and
#'   to prompt users to cope with breaking changes in version 1.0.
#' @param cutoff Maximum length of paths to be considered. Unlimited if negative.
#' @inheritParams common_params
#' @returns `edge_betweenness()` returns a numeric vector of edge betweenness
#' for each edge in the graph.
#' @examples
#' g = graph_tree(5L)
#' edge_betweenness(g)
#' edge_betweenness_subset(g, from = Vsource(g), to = Vsink(g))
#' @name centrality
#' @rdname centrality
#' @export
edge_betweenness = function(
    graph, ..., weights = numeric(0), from = integer(0), to = integer(0), eids = integer(0),
    directed = is_directed(graph), normalized = FALSE, cutoff = -1) {
  if (!missing(...)) {
    stop("Use named arguments to cope with breaking changes in 1.0.", call. = FALSE)
  }
  if (missing(from) && missing(to)) {
    .Call(`_igraphlite_edge_betweenness_`, graph, weights, eids, directed, normalized, cutoff)
  } else {
    if (!missing(cutoff)) {
      warning("`cutoff` is ignored when `from` or `to` is specified.", call. = FALSE)
    }
    .Call(`_igraphlite_edge_betweenness_subset_`, graph, weights, from, to, eids, directed, normalized)
  }
}

#' @returns `edge_betweenness_subset()` is a variant of `edge_betweenness()`
#' that computes the betweenness using a subset of paths between `from` and `to`.
#' @rdname centrality
#' @export
edge_betweenness_subset = function(
    graph, ..., weights = numeric(0), from = integer(0), to = integer(0), eids = integer(0),
    directed = is_directed(graph), normalized = FALSE) {
  warning("`edge_betweenness_subset()` is deprecated; use `edge_betweenness()` instead.", call. = FALSE)
  if (!missing(...)) {
    stop("Use named arguments to cope with breaking changes in 1.0.", call. = FALSE)
  }
  .Call(`_igraphlite_edge_betweenness_subset_`, graph, weights, from, to, eids, directed, normalized)
}
