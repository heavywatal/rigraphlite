# nocov start

mean_distances = function(graph, from = numeric(0L), to = from) {
  if (length(from) == 0L && length(to) == 0L) {
    mean_distances_avg(graph, from, to)
  } else if (setequal(graph$V, from) && setequal(graph$V, to)) {
    mean_distances_avg(graph, from, to)
  } else if (length(from) * length(to) > 1e9) {
    mean_distances_vec(graph, from, to)
  } else {
    mean_distances_mat(graph, from, to)
  }
}

mean_distances_mat = function(graph, from = numeric(0L), to = from, weights = numeric(0L), mode = 3L,
                              algorithm = c("auto", "unweighted", "dijkstra", "bellman-ford", "johnson")) {
  m = shortest_paths(graph, from = from, to = to, weights = weights, mode = mode, algorithm = algorithm)
  if (length(from)) {
    nzero = sum(from %in% to)
  } else {
    nzero = nrow(m)
  }
  sum(m) / (nrow(m) * ncol(m) - nzero)
}

mean_distances_vec = function(graph, from = numeric(0L), to = from, weights = numeric(0L), mode = 3L,
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

upstream_vertices = function(graph, vids) {
  vlist = neighborhood(graph, vids, order = 2147483647L, mode = 2L)
  unique(unlist(vlist, use.names = FALSE))
}

# nocov end
