#' Basic Properties
#'
#' @source <https://igraph.org/c/doc/igraph-Structural.html#basic-properties>
#' @seealso [edge()], [neighbors()], [incident()] for similar operations.
#' [as_adjlist()] and [degree()] can apply to all vertices at once.
#' @inheritParams common_params
#' @returns A logical, `TRUE` if `from` and `to` are adjacent, `FALSE` otherwise.
#' @rdname adjacent
#' @export
#' @examples
#' g = graph_tree(5L)
#' are_adjacent(g, 1L, 2L)
#' are_adjacent(g, 1L, 4L)
are_adjacent = function(graph, from, to) {
  .Call(`_igraphlite_are_adjacent_`, graph, from, to)
}


#' Neighborhood of vertices
#'
#' @source <https://igraph.org/c/doc/igraph-Structural.html#neighborhood-of-a-vertex>
#' @param order An integer giving the order of the neighborhood;
#' e.g., `order = 1L` considers only the immediate neighbors.
#' @param mindist The minimum distance to include a vertex in the counting;
#' e.g., `mindist = 1L` excludes the starting vertex itself, and `2L` excludes
#' the immediate neighbors.
#' @inheritParams common_params
#' @examples
#' g = graph_tree(5L)
#' neighborhood_size(g)
#' neighborhood(g)
#' @returns `neighborhood_size()` returns an integer vector of the neighborhood
#' sizes for the given vertices.
#' @rdname neighborhood
#' @export
neighborhood_size = function(graph, vids = integer(0), order = 1L, mode = 1L, mindist = 0L) {
  .Call(`_igraphlite_neighborhood_size_`, graph, vids, order, mode, mindist)
}

#' @returns `neighborhood()` returns a list of integer vectors, each containing the
#' vertex IDs of the neighbors of the given vertices.
#' @rdname neighborhood
#' @export
neighborhood = function(graph, vids = integer(0), order = 1L, mode = 1L, mindist = 0L) {
  .Call(`_igraphlite_neighborhood_`, graph, vids, order, mode, mindist)
}
