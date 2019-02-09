#' Structural Properties of Graphs
#'
#' @param graph IGraph object.
#' @param v,vids,from,to vertices of interest
#' @param weights numeric edge weights; TRUE to use graph$E$weight
#' @param mode edge type to count; {1: OUT, 2: IN, 3: ALL}
#' @param algorithm character
#' @rdname structural
#' @export
shortest_paths = function(graph, from = numeric(0L), to = from, weights = numeric(0L), mode = 3L,
  algorithm = c("auto", "unweighted", "dijkstra", "bellman-ford", "johnson")) {

  algorithm = match.arg(algorithm)
  if (isTRUE(weights)) weights = graph$E$weight
  if (algorithm == "auto") {
    if (length(weights)) {
      algorithm = "dijkstra"
    } else {
      algorithm = "unweighted"
    }
  }
  if (is.null(weights)) weights = numeric(0L) # NumericVector does not accept NULL
  graph$shortest_paths(from, to, weights, mode, algorithm)
}

#' @rdname structural
#' @export
neighbors = function(graph, v, mode = 3L) {
  graph$neighbors(v, mode)
}

#' @param impl how to construct a new graph:
#'             {0: AUTO, 1: COPY_AND_DELETE, 2: CREATE_FROM_SCRATCH}
#' @rdname structural
#' @export
induced_subgraph = function(graph, vids, impl = 0L) {
  subg = IGraph$new(graph, vids, impl)
  eids = (graph$from() %in% vids) & (graph$to() %in% vids)
  subg$V = graph$V[vids,]
  subg$E = graph$E[eids,]
  subg
}
