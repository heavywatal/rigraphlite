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
