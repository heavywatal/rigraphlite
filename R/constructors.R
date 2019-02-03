graph_from_edgelist = function(el, directed = TRUE) {
  edges = as.numeric(t(el)) - 1
  make_graph(edges, directed = directed)
}
