#' Shortcuts to get sink/source vertices.
#'
#' @inheritParams common_params
#' @returns `is_sink()` and `is_source()` return a logical vector indicating
#' whether the vertices in the graph are terminating or starting points,
#' respectively.
#' @rdname sink
#' @export
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
#' a graph, respectively.
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
