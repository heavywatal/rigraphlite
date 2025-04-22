#' Shortcuts to get sink/source vertices.
#'
#' These are simple wrappers around `degree()` to get zero-degree vertices.
#' @inheritParams common_params
#' @returns `is_sink()` and `is_source()` return a logical vector indicating
#' whether the vertices in the graph are terminating or starting points,
#' respectively.
#' @rdname sink
#' @export
#' @examples
#' g = graph_tree(5L)
#' is_sink(g)
#' is_source(g)
#' Vsink(g)
#' Vsource(g)
is_sink = function(graph) {
  degree(graph, mode = 1L) == 0L
}

#' @rdname sink
#' @export
is_source = function(graph) {
  degree(graph, mode = 2L) == 0L
}

#' @returns `Vsink()` and `Vsource()` return the terminating and starting
#' vertices of a graph, respectively.
#' @rdname sink
#' @export
Vsink = function(graph) {
  V(graph)[is_sink(graph)]
}

#' @rdname sink
#' @export
Vsource = function(graph) {
  V(graph)[is_source(graph)]
}
