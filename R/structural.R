#' Basic Properties
#'
#' @source <https://igraph.org/c/doc/igraph-Structural.html>
#' @inheritParams common_params
#' @rdname connected
#' @export
are_adjacent = function(graph, from, to) {
  are_adjacent_(graph, from, to)
}

#' Shortest Path Related Functions
#'
#' @source <https://igraph.org/c/doc/igraph-Structural.html>
#' @param algorithm character
#' @inheritParams common_params
#' @rdname shortest_paths
#' @export
distances = function(graph, from = integer(0L), to = from, weights = numeric(0L), mode = 3L,
                     algorithm = c("auto", "unweighted", "dijkstra", "bellman-ford", "johnson")) {
  algorithm = match.arg(algorithm)
  if (isTRUE(weights)) {
    stopifnot(utils::hasName(Eattr(graph), "weight"))
    weights = Eattr(graph, "weight")
  }
  if (algorithm == "auto") {
    if (length(weights)) {
      algorithm = "dijkstra"
    } else {
      algorithm = "unweighted"
    }
  }
  distances_(graph, from, to, weights, mode, algorithm)
}

#' @rdname shortest_paths
#' @export
get_shortest_paths = function(graph, from, to = integer(0L), weights = numeric(0L), mode = 3L) {
  if (isTRUE(weights)) {
    stopifnot(utils::hasName(Eattr(graph), "weight"))
    weights = Eattr(graph, "weight")
  }
  get_shortest_paths_(graph, from, to, weights, mode)
}

#' @rdname shortest_paths
#' @export
get_all_shortest_paths = function(graph, from, to = integer(0L), weights = numeric(0L), mode = 3L) {
  if (isTRUE(weights)) {
    stopifnot(utils::hasName(Eattr(graph), "weight"))
    weights = Eattr(graph, "weight")
  }
  get_all_shortest_paths_(graph, from, to, weights, mode)
}

#' @param cutoff integer
#' @rdname shortest_paths
#' @export
get_all_simple_paths = function(graph, from, to = integer(0L), cutoff = -1L, mode = 3L) {
  res = get_all_simple_paths_(graph, from, to, cutoff, mode)
  pos = which(res == 0L)
  split_at(res[-pos], pos - seq_along(pos))
}

#' @rdname shortest_paths
#' @export
average_path_length = function(graph, directed = FALSE) {
  average_path_length_(graph, directed)
}

#' @rdname shortest_paths
#' @export
path_length_hist = function(graph, directed = FALSE) {
  path_length_hist_(graph, directed)
}


#' Neighborhood of vertices
#'
#' @source <https://igraph.org/c/doc/igraph-Structural.html>
#' @param order integer
#' @param mindist The minimum distance to include a vertex in the counting.
#' @inheritParams common_params
#' @rdname neighborhood
#' @export
neighborhood_size = function(graph, vids = integer(0), order = 1L, mode = 1L, mindist = 0L) {
  neighborhood_size_(graph, vids, order, mode, mindist)
}

#' @rdname neighborhood
#' @export
neighborhood = function(graph, vids = integer(0), order = 1L, mode = 1L, mindist = 0L) {
  neighborhood_(graph, vids, order, mode, mindist)
}


#' Graph Components
#'
#' @source <https://igraph.org/c/doc/igraph-Structural.html>
#' @inheritParams common_params
#' @rdname component
#' @export
subcomponent = function(graph, vid, mode = 1L) {
  subcomponent_(graph, vid, mode)
}

#' @rdname component
#' @export
subcomponents = function(graph, vids, mode = 1L) {
  subcomponents_(graph, vids, mode)
}

#' @param impl how to construct a new graph:
#'             \{0: AUTO, 1: COPY_AND_DELETE, 2: CREATE_FROM_SCRATCH\}
#' @rdname component
#' @export
induced_subgraph = function(graph, vids, impl = 0L) {
  vids = sort(vids)
  subg = induced_subgraph_(graph, vids, impl)
  Vattr(subg) = Vattr(graph)[vids, ]
  subg
}
