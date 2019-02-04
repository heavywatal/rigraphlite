graph_from_edgelist = function(el, directed = TRUE) {
  edges = as.numeric(t(el)) - 1
  igraph_create(edges, directed = directed)
}
