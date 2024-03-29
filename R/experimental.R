#' Experimental functions
#'
#' @inheritParams common_params

#' @rdname experimental
#' @export
find_common_ancestors = function(graph, vids) {
  vlist = neighborhood(graph, vids, order = 2147483647L, mode = 2L)
  Reduce(intersect, vlist)
}

#' @param to_mrca Boolean.
#' @rdname experimental
#' @export
upstream_vertices = function(graph, vids, to_mrca = TRUE) {
  vlist = neighborhood(graph, vids, order = 2147483647L, mode = 2L)
  vids = unique(unlist(vlist, use.names = FALSE))
  if (to_mrca) {
    vids = setdiff(vids, Reduce(intersect, vlist)[-1L])
  }
  vids
}

# nocov start

mean_distances = function(graph, from = integer(0L), to = from) {
  if (length(from) == 0L && length(to) == 0L) {
    mean_distances_avg(graph, from, to)
  } else if (setequal(V(graph), from) && setequal(V(graph), to)) {
    mean_distances_avg(graph, from, to)
  } else if (length(from) * length(to) > 1e9) {
    mean_distances_vec(graph, from, to)
  } else {
    mean_distances_mat(graph, from, to)
  }
}

mean_distances_mat = function(graph, from = integer(0L), to = from, weights = numeric(0L), mode = 3L,
                              algorithm = c("auto", "unweighted", "dijkstra", "bellman-ford", "johnson")) {
  m = distances(graph, from = from, to = to, weights = weights, mode = mode, algorithm = algorithm)
  if (length(from)) {
    nzero = sum(from %in% to)
  } else {
    nzero = nrow(m)
  }
  sum(m) / (nrow(m) * ncol(m) - nzero)
}

mean_distances_vec = function(graph, from = integer(0L), to = from, weights = numeric(0L), mode = 3L,
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
  graph$mean_distances(from, to, weights, mode, algorithm)
}

mean_distances_hist = function(graph, from = NULL, to = from) {
  if (length(from)) {
    vids = upstream_vertices(graph, unique(c(from, to)))
    graph = induced_subgraph(graph, vids)
  }
  # TODO: Exclude internal nodes
  h = graph$path_length_hist(FALSE)
  sum(h * seq_along(h)) / sum(h)
}

mean_distances_avg = function(graph, from = NULL, to = from) {
  if (length(from)) {
    vids = upstream_vertices(graph, unique(c(from, to)))
    graph = induced_subgraph(graph, vids)
  }
  # TODO: Exclude internal nodes
  graph$average_path_length(FALSE)
}

# nocov end
