#' Efficiency measures
#'
#' The global efficiency of a network is defined as the average of inverse distances.
#' The local efficiency of a network around a vertex is the global efficiency of the
#' subgraph after removing the vertex.
#' @inheritParams common_params
#' @returns A numeric vector.
#' @source <https://igraph.org/c/doc/igraph-Structural.html#efficiency-measures>
#' @rdname efficiency
#' @export
#' @examples
#' g = graph_tree(7L, mode = 2L)
#' global_efficiency(g)
#'
#' local_efficiency(g)
#'
#' average_local_efficiency(g)
global_efficiency = function(graph, weights = numeric(0L), directed = is_directed(graph)) {
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_global_efficiency_`, graph, as.numeric(weights), directed)
}

#' @rdname efficiency
#' @export
local_efficiency = function(graph, weights = numeric(0L), vids = integer(0L), directed = is_directed(graph), mode = 3L) {
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_local_efficiency_`, graph, as.numeric(weights), vids, directed, mode)
}

#' @rdname efficiency
#' @export
average_local_efficiency = function(graph, weights = numeric(0L), directed = is_directed(graph), mode = 3L) {
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_average_local_efficiency_`, graph, as.numeric(weights), directed, mode)
}
