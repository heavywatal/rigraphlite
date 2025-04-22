#' Graph Components
#'
#' @source <https://igraph.org/c/doc/igraph-Structural.html#graph-components>
#' @seealso [induced_subgraph()]
#' @inheritParams common_params
#' @returns `subcomponent()` returns the IDs of the vertices reachable from the
#' given vertex.
#' @examples
#' g = graph_tree(5L)
#' subcomponent(g, 2L)
#' subcomponents(g, c(1L, 2L))
#' @name components
#' @rdname components
#' @export
subcomponent = function(graph, vid, mode = 1L) {
  .Call(`_igraphlite_subcomponent_`, graph, vid, mode)
}

#' @returns `subcomponents()` returns a list of integer vectors by applying
#' `subcomponent()` for each vertex in `vids`.
#' @rdname components
#' @export
subcomponents = function(graph, vids, mode = 1L) {
  .Call(`_igraphlite_subcomponents_`, graph, vids, mode)
}
