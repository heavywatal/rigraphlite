#' Basic Properties
#'
#' @source <https://igraph.org/c/doc/igraph-Structural.html>
#' @inheritParams common_params
#' @rdname connected
#' @export
are_connected = function(graph, from, to) {
  graph$are_connected(from, to)
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
    stopifnot(utils::hasName(graph$Eattr, "weight"))
    weights = graph$Eattr$weight
  }
  if (algorithm == "auto") {
    if (length(weights)) {
      algorithm = "dijkstra"
    } else {
      algorithm = "unweighted"
    }
  }
  graph$distances(from, to, weights, mode, algorithm)
}

#' @param ... passed to [distances]
#' @rdname shortest_paths
#' @export
shortest_paths = function(graph, ...) {
  warning("shortest_paths() is deprecated. Use distances()")
  distances(graph, ...)
}

#' @rdname shortest_paths
#' @export
get_shortest_paths = function(graph, from, to = integer(0L), weights = numeric(0L), mode = 3L) {
  if (isTRUE(weights)) {
    stopifnot(utils::hasName(graph$Eattr, "weight"))
    weights = graph$Eattr$weight
  }
  graph$get_shortest_paths(from, to, weights, mode)
}

#' @rdname shortest_paths
#' @export
get_all_shortest_paths = function(graph, from, to = integer(0L), weights = numeric(0L), mode = 3L) {
  if (isTRUE(weights)) {
    stopifnot(utils::hasName(graph$Eattr, "weight"))
    weights = graph$Eattr$weight
  }
  graph$get_all_shortest_paths(from, to, weights, mode)
}

#' @param cutoff integer
#' @rdname shortest_paths
#' @export
get_all_simple_paths = function(graph, from, to = integer(0L), cutoff = -1L, mode = 3L) {
  res = graph$get_all_simple_paths(from, to, cutoff, mode)
  pos = which(res %in% 0L)
  split_at(res[-pos], pos - seq_along(pos))
}

#' @rdname shortest_paths
#' @export
average_path_length = function(graph, directed = FALSE) {
  graph$average_path_length(directed)
}

#' @rdname shortest_paths
#' @export
path_length_hist = function(graph, directed = FALSE) {
  graph$path_length_hist(directed)
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
  graph$neighborhood_size(vids, order, mode, mindist)
}

#' @rdname neighborhood
#' @export
neighborhood = function(graph, vids = integer(0), order = 1L, mode = 1L, mindist = 0L) {
  graph$neighborhood(vids, order, mode, mindist)
}


#' Graph Components
#'
#' @source <https://igraph.org/c/doc/igraph-Structural.html>
#' @inheritParams common_params
#' @rdname component
#' @export
subcomponent = function(graph, vid, mode = 1L) {
  graph$subcomponent(vid, mode)
}

#' @rdname component
#' @export
subcomponents = function(graph, vids, mode = 1L) {
  graph$subcomponents(vids, mode)
}

#' @param impl how to construct a new graph:
#'             {0: AUTO, 1: COPY_AND_DELETE, 2: CREATE_FROM_SCRATCH}
#' @rdname component
#' @export
induced_subgraph = function(graph, vids, impl = 0L) {
  vids = sort(vids)
  subg = IGraph$new(graph, vids, impl)
  subg$Vattr = graph$Vattr[vids, ]
  if (ncol(graph$Eattr) > 0L) {
    warning("The order of the edge attributes may not be correct.")
    eids = (graph$from %in% vids) & (graph$to %in% vids)
    subg$Eattr = graph$Eattr[eids, ]
  }
  subg
}
