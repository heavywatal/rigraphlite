#' Convesion between vertex IDs and names
#'
#' @inheritParams common_params
#' @param vnames Vertex names stored in `Vattr[["name"]]`
#' @rdname vattr-name
#' @export
as_vids = function(graph, vnames) {
  match(vnames, graph$Vattr[["name"]])
}

#' @rdname vattr-name
#' @export
as_vnames = function(graph, vids = graph$V) {
  graph$Vattr[["name"]][vids]
}
