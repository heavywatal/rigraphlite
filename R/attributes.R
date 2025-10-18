#' Get and set vertex and edge attributes
#'
#' @description
#' Attributes can be set and retrieved in several ways:
#' - with the `name` argument: `Vattr(g, "name") = letters[1:6]`
#' - with the `$` operator: `Vattr(g)$name = letters[1:6]`
#' - with the `[[` operator: `Vattr(g)[["name"]] = letters[1:6]`
#' - direct operation with a data.frame: `Vattr(g) = data.frame(name = letters[1:6])`
#'
#' Using the `name` argument for setting and `$` operator for getting is the most
#' efficient way according to the brief benchmarking.
#' @inheritParams common_params
#' @param name Name of the attribute to query or set.
#'   If missing, all the attributes are returned or replaced.
#' @param value A vector or data.frame.
#' @returns `Vattr()` and `Eattr()` return a data.frame with the same number of
#' rows as the number of vertices and edges in the graph, respectively.
#' @returns `V()` and `E()` return an integer vector of vertex and edge IDs, respectively.
#' @seealso [Vnames()] for specialized function for "name" attribute.
#' @examples
#' g = graph_create(letters[1:6])
#' Vattr(g)
#' Eattr(g, "weight") = seq_len(ecount(g))
#' Eattr(g)
#' V(g)
#' E(g)
#' @rdname attributes
#' @export
Vattr = function(graph, name) {
  if (missing(name)) {
    .Call(`_igraphlite_getVattr_`, graph)
  } else {
    .Call(`_igraphlite_getVattr_`, graph)[[name]]
  }
}

#' @rdname attributes
#' @export
`Vattr<-` = function(graph, name, value) {
  if (missing(name)) {
    .Call(`_igraphlite_setVattr_`, graph, value)
  } else {
    .Call(`_igraphlite_mutate_Vattr_`, graph, name, value)
  }
  graph
}

#' @rdname attributes
#' @export
Eattr = function(graph, name) {
  if (missing(name)) {
    .Call(`_igraphlite_getEattr_`, graph)
  } else {
    .Call(`_igraphlite_getEattr_`, graph)[[name]]
  }
}

#' @rdname attributes
#' @export
`Eattr<-` = function(graph, name, value) {
  if (missing(name)) {
    .Call(`_igraphlite_setEattr_`, graph, value)
  } else {
    .Call(`_igraphlite_mutate_Eattr_`, graph, name, value)
  }
  graph
}

#' @rdname attributes
#' @export
V = function(graph) {
  .Call(`_igraphlite_V_`, graph)
}

#' @rdname attributes
#' @export
E = function(graph) {
  .Call(`_igraphlite_E_`, graph)
}

#' Conversion between vertex IDs and names
#'
#' `Vnames()` is a faster alternative to [Vattr()] to get the "name" attribute,
#' falling back to `V()` when it is not set.
#' `as_vids()` and `as_vnames()` provide convenient shorthands using `Vnames()`.
#' @inheritParams common_params
#' @param vnames Vertex names stored in `Vattr(g)$name`.
#' @returns `Vnames()` and `as_vnames()` return a vector of vertex names or IDs.
#' @examples
#' g = graph_create(letters[1:6])
#' Vnames(g)
#' as_vids(g, c("d", "b"))
#' as_vnames(g, c(4L, 2L))
#'
#' # Falls back to V(), not NULL
#' Vnames(graph_empty(3L))
#' @rdname vnames
#' @export
Vnames = function(graph) {
  .Call(`_igraphlite_Vnames_`, graph)
}

#' @returns `as_vids()` returns an integer vector of vertex IDs.
#' @rdname vnames
#' @export
as_vids = function(graph, vnames) {
  match(vnames, Vnames(graph))
}

#' @rdname vnames
#' @export
as_vnames = function(graph, vids) {
  Vnames(graph)[vids]
}

#' Quick access to edge list columns
#'
#' If only one of the two columns in the edge list is needed,
#' these functions provide a more efficient way to access them.
#' @seealso [as.matrix.igraph_ptr()] and [as.data.frame.igraph_ptr()] to
#' get entire edge lists.
#' @source <https://github.com/igraph/igraph/blob/master/include/igraph_datatype.h>
#' @inheritParams common_params
#' @returns `igraph_from()` returns the head vertices of all the edges.
#' @rdname from-to
#' @export
#' @examples
#' g = graph_create(seq_len(6L))
#' igraph_from(g)
#' igraph_to(g)
igraph_from = function(graph) {
  .Call(`_igraphlite_from_`, graph)
}

#' @returns `igraph_to()` returns the tail vertices of all the edges.
#' @rdname from-to
#' @export
igraph_to = function(graph) {
  .Call(`_igraphlite_to_`, graph)
}
