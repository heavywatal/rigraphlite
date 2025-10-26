#' Cliques
#'
#' A graph is considered complete if all pairs of different vertices are adjacent.
#' Cliques are fully connected subgraphs of a graph.
#' @source <https://igraph.org/c/doc/igraph-Cliques.html#cliques>
#' @inheritParams common_params
#' @returns `is_complete()` and `is_clique()` return a logical value.
#' @name cliques
#' @rdname cliques
#' @export
is_complete = function(graph) {
  .Call(`_igraphlite_is_complete_`, graph)
}

#' @param candidate The vertex set to test for being a clique.
#' @rdname cliques
#' @export
is_clique = function(graph, candidate = integer(0L), directed = is_directed(graph)) {
  .Call(`_igraphlite_is_clique_`, graph, candidate, directed)
}

#' @param min_size,max_size An integer specifying the minimum/maximum size of the
#' sets to be returned. If negative or zero, no lower bound will be used.
#' @param max_results At most this many sets will be recorded.
#' If negative, no limit is applied.
#' @rdname cliques
#' @export
cliques = function(graph, min_size = 0L, max_size = -1L, max_results = -1L) {
  .Call(`_igraphlite_cliques_`, graph, min_size, max_size, max_results)
}

#' @rdname cliques
#' @export
clique_size_hist = function(graph, min_size = 0L, max_size = -1L) {
  .Call(`_igraphlite_clique_size_hist_`, graph, min_size, max_size) |> as.integer()
}

#' @rdname cliques
#' @export
largest_cliques = function(graph) {
  .Call(`_igraphlite_largest_cliques_`, graph)
}

#' @rdname cliques
#' @export
maximal_cliques = function(graph, min_size = 0L, max_size = -1L, max_results = -1L) {
  .Call(`_igraphlite_maximal_cliques_`, graph, min_size, max_size, max_results)
}

#' @rdname cliques
#' @export
maximal_cliques_count = function(graph, min_size = 0L, max_size = -1L) {
  .Call(`_igraphlite_maximal_cliques_count_`, graph, min_size, max_size)
}

#' @rdname cliques
#' @export
maximal_cliques_hist = function(graph, min_size = 0L, max_size = -1L) {
  .Call(`_igraphlite_maximal_cliques_hist_`, graph, min_size, max_size) |> as.integer()
}

#' @rdname cliques
#' @export
clique_number = function(graph) {
  .Call(`_igraphlite_clique_number_`, graph)
}


#' Independent vertex sets
#'
#' A vertex set is considered independent if there are no edges between them.
#' @source <https://igraph.org/c/doc/igraph-Cliques.html#independent-vertex-sets>
#' @inheritParams common_params
#' @inheritParams cliques
#' @name independent
#' @rdname independent
#' @export
is_independent_vertex_set = function(graph, candidate = integer(0L)) {
  .Call(`_igraphlite_is_independent_vertex_set_`, graph, candidate)
}

#' @rdname independent
#' @export
independent_vertex_sets = function(graph, min_size = 0L, max_size = -1L, max_results = -1L) {
  .Call(`_igraphlite_independent_vertex_sets_`, graph, min_size, max_size, max_results)
}

#' @rdname independent
#' @export
largest_independent_vertex_sets = function(graph) {
  .Call(`_igraphlite_largest_independent_vertex_sets_`, graph)
}

#' @rdname independent
#' @export
maximal_independent_vertex_sets = function(graph, min_size = 0L, max_size = -1L, max_results = -1L) {
  .Call(`_igraphlite_maximal_independent_vertex_sets_`, graph, min_size, max_size, max_results)
}

#' @rdname independent
#' @export
independence_number = function(graph) {
  .Call(`_igraphlite_independence_number_`, graph)
}
