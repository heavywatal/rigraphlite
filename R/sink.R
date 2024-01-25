#' Shortcuts to get sink/source vertices.
#'
#' @inheritParams common_params
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
