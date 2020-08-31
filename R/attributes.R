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
    setVattr_(graph, value)
  } else {
    x = .Call(`_igraphlite_getVattr_`, graph)
    x[[name]] = value
    setVattr_(graph, x)
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
    setEattr_(graph, value)
  } else {
    x = .Call(`_igraphlite_getEattr_`, graph)
    x[[name]] = value
    setEattr_(graph, x)
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
