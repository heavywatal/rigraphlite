#' Centrality measures
#'
#' The betweenness centrality of an edge is the number of geodesics going through it.
#' @source <https://igraph.org/c/doc/igraph-Structural.html#centrality-measures>
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
edge_betweenness = function(graph, directed = is_directed(graph), weights = numeric(0)) {
  .Call(`_igraphlite_edge_betweenness_`, graph, directed, weights)
}

#' @returns `edge_betweenness_subset()` is a variant of `edge_betweenness()`
#' that computes the betweenness using a subset of paths between `from` and `to`.
#' @rdname centrality
#' @export
edge_betweenness_subset = function(
    graph, directed = is_directed(graph), eids = integer(0),
    weights = numeric(0), from = integer(0), to = integer(0)) {
  .Call(`_igraphlite_edge_betweenness_subset_`, graph, directed, eids, weights, from, to)
}
