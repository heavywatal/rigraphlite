#' Acyclic graphs and feedback sets
#'
#' A directed acyclic graph (DAG) is a directed graph with no directed cycles.
#' For directed graphs, only directed cycles are considered.
#' @inheritParams common_params
#' @returns A logical value.
#' @source <https://igraph.org/c/doc/igraph-Cycles.html#acyclic-graphs-feedback-sets>
#' @rdname cycles-acyclic
#' @export
#' @examples
#' dag = graph_tree(5L)
#' tree = graph_tree(5L, mode = 2L)
#' ring = graph_ring(5L)
#'
#' is_dag(dag)
#' is_dag(tree)
#' is_dag(ring)
#'
#' is_acyclic(dag)
#' is_acyclic(tree)
#' is_acyclic(ring)
is_dag = function(graph) {
  .Call(`_igraphlite_is_dag_`, graph)
}

#' @rdname cycles-acyclic
#' @export
is_acyclic = function(graph) {
  .Call(`_igraphlite_is_acyclic_`, graph)
}

#' Eulerian cycles and paths
#'
#' An Eulerian path traverses each edge of the graph precisely once.
#' A closed Eulerian path is referred to as an Eulerian cycle.
#' @inheritParams common_params
#' @returns A logical value with two elements: "has a path" and "has a cycle".
#' @source <https://igraph.org/c/doc/igraph-Cycles.html#eulerian-cycles>
#' @rdname cycles-eulerian
#' @export
#' @examples
#' is_eulerian(graph_tree(5L))
#'
#' is_eulerian(graph_square_lattice(5L))
#'
#' is_eulerian(graph_ring(5L))
is_eulerian = function(graph) {
  .Call(`_igraphlite_is_eulerian_`, graph)
}
