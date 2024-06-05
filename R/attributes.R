#' Get and set vertex and edge attributes
#'
#' @inheritParams common_params
#' @param name Name of the attribute to query or set.
#'   If missing, all the attributes are returned or replaced.
#' @param value A vector or data.frame.
#' @rdname attributes
#' @export
vertex_attr = function(graph, name) {
  .Deprecated("Vattr")
  Vattr(graph, name)
}

#' @rdname attributes
#' @export
Vattr = function(graph, name) {
  if (missing(name)) {
    graph$Vattr
  } else {
    graph$Vattr[[name]]
  }
}

#' @rdname attributes
#' @export
`vertex_attr<-` = function(graph, name, value) {
  .Deprecated("Vattr<-")
  Vattr(graph, name) = value
}

#' @rdname attributes
#' @export
`Vattr<-` = function(graph, name, value) {
  if (missing(name)) {
    graph$Vattr = value
  } else {
    graph$Vattr[[name]] = value
  }
  graph
}

#' @rdname attributes
#' @export
edge_attr = function(graph, name) {
  .Deprecated("Eattr")
  Eattr(graph, name)
}

#' @rdname attributes
#' @export
Eattr = function(graph, name) {
  if (missing(name)) {
    graph$Eattr
  } else {
    graph$Eattr[[name]]
  }
}

#' @rdname attributes
#' @export
`edge_attr<-` = function(graph, name, value) {
  .Deprecated("Eattr<-")
  Eattr(graph, name) = value
}

#' @rdname attributes
#' @export
`Eattr<-` = function(graph, name, value) {
  if (missing(name)) {
    graph$Eattr = value
  } else {
    graph$Eattr[[name]] = value
  }
  graph
}

#' @rdname attributes
#' @export
V = function(graph) {
  seq_len(vcount(graph))
}

#' @rdname attributes
#' @export
E = function(graph) {
  seq_len(ecount(graph))
}

#' Conversion between vertex IDs and names
#'
#' @inheritParams common_params
#' @param vnames Vertex names stored in `Vattr[["name"]]`.
#' @rdname vnames
#' @export
Vnames = function(graph) {
  Vattr(graph, "name") %||% V(graph)
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
