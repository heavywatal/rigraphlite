#' Convert igraph objects to and from other formats.
#'
#' Round-trip conversion is not guaranteed currently.
#' Conversion to data.frame preserves edge attributes and vertex names,
#' but the other vertex attributes are lost, and internal vertex IDs may change.
#' @seealso [graph_from_symbolic_edgelist()], [graph_from_edgelist()],
#' [graph_from_data_frame()], [graph_create()] for underlying functions.
#' @param x A vector, matrix, data.frame, or graph object to be converted.
#' @param ... Additional arguments passed to the conversion function.
#' @returns `as_igraph()` returns an [igraph_ptr] object.
#' @rdname conversion
#' @export
#' @examples
#' edges = seq_len(6L)
#' g1 = as_igraph(edges)
#' edgelist = as.matrix(g1) |> print()
#'
#' g2 = as_igraph(edgelist)
#' g3 = as_igraph(as.data.frame(g2)) |> print()
as_igraph = function(x, ...) UseMethod("as_igraph")

#' @rdname conversion
#' @export
as_igraph.default = function(x, ...) {
  graph_create(x, ...)
}

#' @rdname conversion
#' @export
as_igraph.matrix = function(x, ...) {
  if (is.numeric(x)) {
    graph_from_edgelist(x, ...)
  } else {
    graph_from_symbolic_edgelist(x, ...)
  }
}

#' @rdname conversion
#' @export
as_igraph.data.frame = function(x, ...) {
  graph_from_data_frame(x, ...)
}

#' @returns `as.data.frame()` returns an edge list in data.frame format,
#' which may include additional columns for edge attributes.
#' @rdname conversion
#' @export
as.data.frame.igraph_ptr = function(x, ...) {
  .Call(`_igraphlite_as_data_frame_`, x)
}

#' @returns `as.matrix()` returns an edge list in matrix format.
#' @rdname conversion
#' @export
as.matrix.igraph_ptr = function(x, ...) {
  .Call(`_igraphlite_as_edgelist_`, x)
}
