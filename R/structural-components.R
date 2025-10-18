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
#'
#' connected_components(g)
#'
#' is_connected(g)
#'
#' count_reachable(g)
#'
#' transitive_closure(g)
#'
#' articulation_points(g)
#'
#' bridges(g)
#'
#' is_biconnected(g)
#'
#' subcomponents(g, c(1L, 2L))
#' @name components
#' @rdname components
#' @export
subcomponent = function(graph, vid, mode = 1L) {
  .Call(`_igraphlite_subcomponent_`, graph, vid, mode)
}

#' @param connectedness An integer indicating the type of connectedness:
#' \{1: WEAK (ignore edge directions), 2: STRONG\}
#' @returns `connected_components()` returns component IDs for each vertex.
#' @rdname components
#' @export
connected_components = function(graph, connectedness = 1L) {
  .Call(`_igraphlite_connected_components_`, graph, connectedness)
}

#' @returns `is_connected()` and `is_biconnected()` return logical values.
#' @rdname components
#' @export
is_connected = function(graph, connectedness = 1L) {
  .Call(`_igraphlite_is_connected_`, graph, connectedness)
}

#' @returns `count_reachable()` returns an integer vector of the number of
#' reachable vertices from each vertex including itself.
#' @rdname components
#' @export
count_reachable = function(graph, mode = 1L) {
  .Call(`_igraphlite_count_reachable_`, graph, mode)
}

#' @returns `transitive_closure()` returns the transitive closure graph.
#' @rdname components
#' @export
transitive_closure = function(graph) {
  .Call(`_igraphlite_transitive_closure_`, graph) |> set_ptr_class()
}

#' @returns `articulation_points()` and `bridges()` return vertex IDs and edge IDs,
#' respectively.
#' @rdname components
#' @export
articulation_points = function(graph) {
  .Call(`_igraphlite_articulation_points_`, graph)
}

#' @rdname components
#' @export
bridges = function(graph) {
  .Call(`_igraphlite_bridges_`, graph)
}

#' @rdname components
#' @export
is_biconnected = function(graph) {
  .Call(`_igraphlite_is_biconnected_`, graph)
}

#' @returns `subcomponents()` returns a list of integer vectors by applying
#' `subcomponent()` for each vertex in `vids`.
#' @rdname components
#' @export
subcomponents = function(graph, vids, mode = 1L) {
  .Call(`_igraphlite_subcomponents_`, graph, vids, mode)
}
