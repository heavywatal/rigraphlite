#' The Erdős-Rényi and related models
#'
#' Classical random graph models with a fixed number of vertices.
#' @inheritParams common_params
#' @param n The number of vertices.
#' @param m The number of edges.
#' @param p The probability of edge creation or rewiring.
#' @param edge_type_sw The types of edges to allow in the graph:
#' \{0: simple, 1: loops, 6: multiple, 7: loops and multiple\}.
#' @returns An [`igraph_ptr`] object.
#' @source <https://igraph.org/c/html/latest/igraph-Games.html#erdos-renyi-games>
#' @rdname games-erdos-renyi
#' @export
#' @examples
#' gnm = erdos_renyi_game_gnm(5L, 5L)
#' gnp = erdos_renyi_game_gnp(5L, 0.5)
erdos_renyi_game_gnm = function(n, m, directed = FALSE, edge_type_sw = 0L) {
  .Call(`_igraphlite_erdos_renyi_game_gnm_`, n, m, directed, edge_type_sw) |> set_ptr_class()
}

#' @rdname games-erdos-renyi
#' @export
erdos_renyi_game_gnp = function(n, p, directed = FALSE, edge_type_sw = 0L) {
  .Call(`_igraphlite_erdos_renyi_game_gnp_`, n, p, directed, edge_type_sw) |> set_ptr_class()
}

#' Degree-constrained models
#'
#' Random graph models with hard or soft degree constraints.
#' @inheritParams common_params
#' @inheritParams erdos_renyi_game_gnm
#' @param out_degrees,in_degrees Integer vectors giving the degree sequences.
#' Undirected graphs are generated if an empty `in_degrees` is given.
#' @param degseq_method The method to generate a graph from the degree sequence:
#' \{0: smallest, 1: largest, 2: index\}.
#' @param k The degree of each vertex in an undirected graph,
#' or the out-degree and in-degree of each vertex in a directed graph.
#' @returns An [`igraph_ptr`] object.
#' @source <https://igraph.org/c/html/latest/igraph-Games.html#degree-constrained-games>
#' @rdname games-degree-constrained
#' @export
#' @examples
#' out_deg = seq_len(4L)
#' undirected = degree_sequence_game(out_deg)
#' degree(undirected)
#'
#' in_deg = rev(out_deg)
#' directed = degree_sequence_game(out_deg, in_deg)
#' degree(directed, mode = 1L)
#' degree(directed, mode = 2L)
#'
#' k_regular = k_regular_game(7L, 2L)
#' degree(k_regular)
#' degree(rewire(k_regular, 9L))
degree_sequence_game = function(out_degrees, in_degrees = integer(0), degseq_method = 0L) {
  .Call(`_igraphlite_degree_sequence_game_`, out_degrees, in_degrees, degseq_method) |> set_ptr_class()
}

#' @rdname games-degree-constrained
#' @export
k_regular_game = function(n, k, directed = FALSE, multiple = FALSE) {
  .Call(`_igraphlite_k_regular_game_`, n, k, directed, multiple) |> set_ptr_class()
}

#' @description
#' `rewire()` creates a copy of the input graph,
#' and performs `n_trials` of edge rewirings while preserving the degree sequence.
#' @param n_trials The number of rewiring trials to perform.
#' @seealso [rewire_edges()] for an edge rewiring model without degree constraints.
#' @rdname games-degree-constrained
#' @export
rewire = function(graph, n_trials, edge_type_sw = 0L) {
  res = graph_copy(graph)
  .Call(`_igraphlite_rewire_`, graph, n_trials, edge_type_sw)
  res
}

#' Edge rewiring models
#'
#' @inheritParams common_params
#' @inheritParams erdos_renyi_game_gnm
#' @param dim The dimension of the lattice.
#' @param size The size of the lattice along each dimension.
#' @param nei The size of the neighborhood for each vertex.
#' @returns An [`igraph_ptr`] object.
#' @source <https://igraph.org/c/html/latest/igraph-Games.html#edge-rewiring-games>
#' @rdname games-edge-rewiring
#' @export
#' @examples
#' regular = watts_strogatz_game(1L, 20L, 2L, 0)
#' random = watts_strogatz_game(1L, 20L, 2L, 1)
#' small_world = watts_strogatz_game(1L, 20L, 2L, 0.1)
#' small_world2 = rewire_edges(regular, 0.1)
watts_strogatz_game = function(dim, size, nei, p, edge_type_sw = 0L) {
  .Call(`_igraphlite_watts_strogatz_game_`, dim, size, nei, p, edge_type_sw) |> set_ptr_class()
}

#' @description
#' `rewire_edges()` creates a copy of the input graph,
#' and rewires edges randomly with probability `p` for each edge.
#' @seealso [rewire()] for the degree-preserving edge rewiring model.
#' @rdname games-edge-rewiring
#' @export
rewire_edges = function(graph, p, edge_type_sw = 0L) {
  res = graph_copy(graph)
  .Call(`_igraphlite_rewire_edges_`, res, p, edge_type_sw)
  res
}
