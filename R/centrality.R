#' Centrality measures
#'
#' @source <https://igraph.org/c/doc/igraph-Structural.html#centrality-measures>
#' @inheritParams common_params
#' @rdname centrality
#' @export
edge_betweenness = function(graph, directed = is_directed(graph), weights = numeric(0)) {
  .Call(`_igraphlite_edge_betweenness_`, graph, directed, weights)
}

#' @rdname centrality
#' @export
edge_betweenness_subset = function(
    graph, directed = is_directed(graph), eids = integer(0),
    weights = numeric(0), from = integer(0), to = integer(0)) {
  .Call(`_igraphlite_edge_betweenness_subset_`, graph, directed, eids, weights, from, to)
}
