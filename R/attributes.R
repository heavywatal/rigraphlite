#' Get and set vertex and edge attributes
#'
#' @inheritParams common_params
#' @param name Name of the attribute to query or set.
#'   If missing, all the attributes are returned or replaced.
#' @param value A vector or data.frame.
#' @rdname attributes
#' @export
vertex_attr = function(graph, name) {
  if (missing(name)) {
    graph$Vattr
  } else {
    graph$Vattr[[name]]
  }
}

#' @rdname attributes
#' @export
`vertex_attr<-` = function(graph, name, value) {
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
  if (missing(name)) {
    graph$Eattr
  } else {
    graph$Eattr[[name]]
  }
}

#' @rdname attributes
#' @export
`edge_attr<-` = function(graph, name, value) {
  if (missing(name)) {
    graph$Eattr = value
  } else {
    graph$Eattr[[name]] = value
  }
  graph
}

#' Convesion between vertex IDs and names
#'
#' @inheritParams common_params
#' @param vnames Vertex names stored in `Vattr[["name"]]`.
#' @rdname vnames
#' @export
Vnames = function(graph) {
  graph$Vattr[["name"]] %||% graph$V
}

#' @rdname vnames
#' @export
as_vids = function(graph, vnames) {
  match(vnames, Vnames(graph))
}

#' @rdname vnames
#' @export
as_vnames = function(graph, vids = graph$V) {
  Vnames(graph)[vids]
}
