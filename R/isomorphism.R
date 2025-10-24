#' The simple interface for graph isomorphism
#'
#' In simple terms, two graphs are isomorphic if they become indistinguishable
#' from each other once their vertex labels are removed.
#' @source <https://igraph.org/c/html/latest/igraph-Isomorphism.html#isomorphism-simple-interface>
#' @seealso [is_same_graph()].
#' @inheritParams is_same_graph
#' @returns A logical value.
#' @rdname isomorphic
#' @export
#' @examples
#' g1 = graph_create(c(1L, 2L, 1L, 3L), directed = FALSE)
#' g2 = graph_create(c(3L, 2L, 3L, 1L), directed = FALSE)
#' isomorphic(g1, g2)
#' subisomorphic(g1, g2)
#'
#' g3 = graph_create(c(1L, 2L, 1L, 3L, 3L, 4L), directed = FALSE)
#' subisomorphic(g3, g1)
#' subisomorphic(g1, g3)
isomorphic = function(graph1, graph2) {
  .Call(`_igraphlite_isomorphic_`, graph1, graph2)
}

#' @returns `subisomorphic()` returns `TRUE` if `graph2` is isomorphic
#' to a subgraph of `graph1`.
#' @rdname isomorphic
#' @export
subisomorphic = function(graph1, graph2) {
  .Call(`_igraphlite_subisomorphic_`, graph1, graph2)
}

#' Permute the vertices
#'
#' Call `permutate_vertices()` with the output of `canonical_permutation()`
#' to create the canonical form of a graph.
#' Note that the edge order may differ even after canonicalization.
#' @source <https://igraph.org/c/html/latest/igraph-Isomorphism.html#igraph_permute_vertices>
#' @seealso [topological_sorting()].
#' @inheritParams common_params
#' @param colors An optional vertex color vector in integer.
#' @returns `canonical_permutation()` returns an integer vector.
#' @name permutation
#' @rdname permutation
#' @export
#' @examples
#' g1 = graph_create(c(1L, 2L, 1L, 3L), directed = FALSE)
#' g2 = graph_create(c(3L, 2L, 3L, 1L), directed = FALSE)
#' isomorphic(g1, g2)
#' is_same_graph(g1, g2)
#' # as.matrix(g1) and as.matrix(g2) may differ
#'
#' g1can = permutate_vertices(g1, canonical_permutation(g1))
#' g2can = permutate_vertices(g2, canonical_permutation(g2))
#' is_same_graph(g1can, g2can)
#'
#' isomorphic(g1, permutate_vertices(g1, c(3L, 2L, 1L)))
canonical_permutation = function(graph, colors = integer(0L)) {
  .Call(`_igraphlite_canonical_permutation_`, graph, colors)
}

#' @param permutation An integer vector,
#' whose i-th element specifies the index of the vertex in the original graph
#' that will become vertex i in the new graph.
#' @returns `permutate_vertices()` returns an [`igraph_ptr`] object
#' isomorphic to the input `graph`.
#' @rdname permutation
#' @export
permutate_vertices = function(graph, permutation) {
  .Call(`_igraphlite_permute_vertices_`, graph, permutation) |> set_ptr_class()
}
