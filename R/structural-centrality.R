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
#' closeness(g, mode = 3L)
#' closeness(g, mode = 3L, normalized = FALSE)
#'
#' harmonic_centrality(g, mode = 3L)
#' harmonic_centrality(g, mode = 3L, normalized = FALSE)
#'
#' betweenness(g)
#'
#' edge_betweenness(g)
#' edge_betweenness(g, from = Vsource(g), to = Vsink(g))
#' edge_betweenness(g, normalized = TRUE)
#' edge_betweenness(g, cutoff = 1)
#'
#' pagerank(g)
#'
#' constraint(g)
#'
#' maxdegree(g, mode = 3L)
#'
#' strength(g, mode = 3L)
#'
#' eigenvector_centrality(g, mode = 3L)
#'
#' convergence_degree(g)
#'
#' hub_and_authority_scores(g)
#' @name centrality
#' @returns `closeness()` returns the inverse of the mean distance to all other vertices.
#' @rdname centrality
#' @export
closeness = function(graph, vids = integer(0), mode = 1L, weights = numeric(0), normalized = TRUE) {
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_closeness_`, graph, vids, mode, as.numeric(weights), normalized)
}

#' @returns `harmonic_centrality()` returns the mean inverse distance to all other vertices.
#' @rdname centrality
#' @export
harmonic_centrality = function(graph, vids = integer(0), mode = 1L, weights = numeric(0), normalized = TRUE) {
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_harmonic_centrality_`, graph, vids, mode, as.numeric(weights), normalized)
}

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

#' @param reset A numeric vector of probabilities for each vertex to be a reset point.
#' If empty, uniform probabilities are assumed.
#' @param damping A numeric value between 0 and 1, the damping factor.
#' Walking restarts from a random vertex with probability 1 - `damping`.
#' @returns `pagerank()` returns a numeric vector of PageRank scores for each vertex.
#' @rdname centrality
#' @export
pagerank = function(
  graph,
  weights = numeric(0),
  reset = numeric(0),
  damping = 0.85,
  directed = is_directed(graph),
  vids = integer(0)
) {
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_pagerank_`, graph, as.numeric(weights), reset, damping, directed, vids)
}

#' @returns `constraint()` returns a numeric vector of Burt's constraint scores.
#' @rdname centrality
#' @export
constraint = function(graph, vids = integer(0), weights = numeric(0)) {
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_constraint_`, graph, vids, as.numeric(weights))
}

#' @returns `maxdegree()` is equivalent to `max(degree(graph))`.
#' @rdname centrality
#' @export
maxdegree = function(graph, vids = integer(0), mode = 1L, loops = 1L) {
  .Call(`_igraphlite_maxdegree_`, graph, vids, mode, loops)
}

#' @returns `strength()` of a vertex is the sum of the weights of its incident edges.
#' @rdname centrality
#' @export
strength = function(graph, vids = integer(0), mode = 1L, loops = 1L, weights = numeric(0)) {
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_strength_`, graph, vids, mode, loops, as.numeric(weights))
}

#' @returns `eigenvector_centrality()` of each vertex is proportional to
#' the sum of eigenvector centralities of its neighbors.
#' @rdname centrality
#' @export
eigenvector_centrality = function(graph, mode = 1L, weights = numeric(0)) {
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_eigenvector_centrality_`, graph, mode, as.numeric(weights))
}

#' @returns `hub_and_authority_scores()` are a generalization of the ideas
#' behind eigenvector centrality to directed graphs.
#' @rdname centrality
#' @export
hub_and_authority_scores = function(graph, weights = numeric(0)) {
  if (isTRUE(weights)) {
    weights = Eattr(graph)$weight
  }
  .Call(`_igraphlite_hub_and_authority_scores_`, graph, as.numeric(weights))
}

#' @returns `convergence_degree()` returns the normalized value of the difference
#' between the size of the input set and the output set.
#' @rdname centrality
#' @export
convergence_degree = function(graph) {
  .Call(`_igraphlite_convergence_degree_`, graph)
}
