#' Non-simple graphs: multiple and loop edges
#'
#' Multiple edges are those that connect the same pair of vertices, where the direction
#' is also taken into account in directed graphs.
#' Loop here means auto-loop/self-loop, i.e., an edge that connects a vertex to itself.
#' @source <https://igraph.org/c/doc/igraph-Structural.html#non-simple-graphs-multiple-and-loop-edges>
#' @inheritParams common_params
#' @returns Logical or integer values.
#' @examples
#' g = graph_tree(5L)
#' g = add_edges(g, c(1L, 1L)) # add a loop
#' g = add_edges(g, c(1L, 2L)) # add a multiple edge
#' g = add_edges(g, c(2L, 1L)) # not a multiple edge in directed graph
#'
#' is_simple(g)
#' has_loop(g)
#' count_loops(g)
#' has_multiple(g)
#' count_multiple(g)
#' @rdname non-simple
#' @export
is_simple = function(graph, directed = is_directed(graph)) {
  .Call(`_igraphlite_is_simple_`, graph, directed)
}

#' @rdname non-simple
#' @export
has_loop = function(graph) {
  .Call(`_igraphlite_has_loop_`, graph)
}

#' @rdname non-simple
#' @export
count_loops = function(graph) {
  .Call(`_igraphlite_count_loops_`, graph)
}

#' @rdname non-simple
#' @export
has_multiple = function(graph) {
  .Call(`_igraphlite_has_multiple_`, graph)
}

#' @rdname non-simple
#' @export
count_multiple = function(graph, eids = integer(0L)) {
  .Call(`_igraphlite_count_multiple_`, graph, eids)
}
