#' Basic Properties
#'
#' @source <https://igraph.org/c/doc/igraph-Structural.html#basic-properties>
#' @inheritParams common_params
#' @rdname adjacent
#' @export
are_adjacent = function(graph, from, to) {
  .Call(`_igraphlite_are_adjacent_`, graph, from, to)
}


#' Neighborhood of vertices
#'
#' @source <https://igraph.org/c/doc/igraph-Structural.html#neighborhood-of-a-vertex>
#' @param order integer
#' @param mindist The minimum distance to include a vertex in the counting.
#' @inheritParams common_params
#' @rdname neighborhood
#' @export
neighborhood_size = function(graph, vids = integer(0), order = 1L, mode = 1L, mindist = 0L) {
  .Call(`_igraphlite_neighborhood_size_`, graph, vids, order, mode, mindist)
}

#' @rdname neighborhood
#' @export
neighborhood = function(graph, vids = integer(0), order = 1L, mode = 1L, mindist = 0L) {
  .Call(`_igraphlite_neighborhood_`, graph, vids, order, mode, mindist)
}


#' Graph Components
#'
#' @source <https://igraph.org/c/doc/igraph-Structural.html#graph-components>
#' @seealso [induced_subgraph()]
#' @inheritParams common_params
#' @rdname component
#' @export
subcomponent = function(graph, vid, mode = 1L) {
  .Call(`_igraphlite_subcomponent_`, graph, vid, mode)
}

#' @rdname component
#' @export
subcomponents = function(graph, vids, mode = 1L) {
  .Call(`_igraphlite_subcomponents_`, graph, vids, mode)
}
