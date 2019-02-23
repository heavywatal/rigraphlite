#' Structural Properties of Graphs
#'
#' @seealso <https://igraph.org/c/doc/igraph-Structural.html>
#' @eval common_params(graph, vids, from, to, weights, mode, directed)
#' @param algorithm character
#' @rdname structural
#' @export
shortest_paths = function(graph, from = numeric(0L), to = from, weights = numeric(0L), mode = 3L,
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
  graph$shortest_paths(from, to, weights, mode, algorithm)
}

#' @rdname structural
#' @export
get_shortest_paths = function(graph, from, to = numeric(0L), weights = numeric(0L), mode = 3L) {
  if (isTRUE(weights)) {
    stopifnot(utils::hasName(graph$Eattr, "weight"))
    weights = graph$Eattr$weight
  }
  graph$get_shortest_paths(from, to, weights, mode)
}

#' @rdname structural
#' @export
average_path_length = function(graph, directed = FALSE) {
  graph$average_path_length(directed)
}

#' @rdname structural
#' @export
path_length_hist = function(graph, directed = FALSE) {
  graph$path_length_hist(directed)
}

#' @param order integer
#' @param mindist The minimum distance to include a vertex in the counting.
#' @rdname structural
#' @export
neighborhood_size = function(graph, vids = numeric(0), order = 1L, mode = 1L, mindist = 0L) {
  graph$neighborhood_size(vids, order, mode, mindist)
}

#' @rdname structural
#' @export
neighborhood = function(graph, vids = numeric(0), order = 1L, mode = 1L, mindist = 0L) {
  graph$neighborhood(vids, order, mode, mindist)
}

#' @rdname structural
#' @export
subcomponent = function(graph, from, mode = 1L) {
  graph$subcomponent(from, mode)
}

#' @param impl how to construct a new graph:
#'             {0: AUTO, 1: COPY_AND_DELETE, 2: CREATE_FROM_SCRATCH}
#' @rdname structural
#' @export
induced_subgraph = function(graph, vids, impl = 0L) {
  subg = IGraph$new(graph, vids, impl)
  eids = (graph$from %in% vids) & (graph$to %in% vids)
  subg$Vattr = graph$Vattr[vids,]
  subg$Eattr = graph$Eattr[eids,]
  subg
}
