#' Get and set vertex and edge attributes
#'
#' @inheritParams common_params
#' @param name Name of the attribute to query or set.
#'   If missing, all the attributes are returned or replaced.
#' @param value A vector or data.frame.
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
#' @inheritParams common_params
#' @param vnames Vertex names stored in `Vattr[["name"]]`.
#' @rdname vnames
#' @export
Vnames = function(graph) {
  .Call(`_igraphlite_Vnames_`, graph)
}

#' @rdname vnames
#' @export
as_vids = function(graph, vnames) {
  match(vnames, Vnames(graph))
}

#' @rdname vnames
#' @export
as_vnames = function(graph, vids = V(graph)) {
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
