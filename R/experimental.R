# nocov start

upstream_vertices = function(graph, vids) {
  vlist = neighborhood(graph, vids, order = 2147483647L, mode = 2L)
  unique(unlist(vlist, use.names = FALSE))
}

mean_branch_length_h = function(graph, from = NULL, to = from) {
  if (length(from)) {
    vids = upstream_vertices(graph, unique(c(from, to)))
    graph = induced_subgraph(graph, vids)
  }
  # TODO: Exclude internal nodes
  h = graph$path_length_hist(FALSE)
  sum(h * seq_along(h)) / sum(h)
}

mean_branch_length_m = function(graph, from = numeric(0), to = from) {
  # TODO: Avoid creating huge matrix
  m = shortest_paths(graph, from, to, mode = 3L)
  if (length(from)) {
    nzero = sum(from %in% to)
  } else {
    nzero = nrow(m)
  }
  sum(m) / (nrow(m) * ncol(m) - nzero)
}

# nocov end
