#' Conversion between phylo and igraph
#'
#' @source <https://cran.r-project.org/package=ape>
#' @param x An object to convert.

#' @rdname phylo
#' @export
as_igraph.phylo = function(x) {
  g = graph_from_edgelist(x[["edge"]])
  node.label = x[["node.label"]] %||% rep(NA, x[["Nnode"]])
  Vattr(g, "name") = c(x[["tip.label"]], node.label)
  Eattr(g, "edge.length") = x[["edge.length"]]
  g
}

#' @rdname phylo
#' @export
as_phylo = function(x) {
  labels = Vnames(x)
  idx_sink = is_sink(x)
  structure(list(
    edge = phylo_edge(x),
    tip.label = labels[idx_sink],
    node.label = labels[!idx_sink],
    edge.length = phylo_edge_length(x),
    Nnode = sum(!idx_sink)
  ), class = "phylo", order = "cladewise")
}

# Tips must have younger IDs
phylo_edge = function(graph) {
  edgelist = as.matrix(graph)
  old_ids = c(Vsink(graph), setdiff(V(graph), Vsink(graph)))
  edge = match(edgelist, old_ids)
  class(edge) = "integer"
  dim(edge) = dim(edgelist)
  edge
}

phylo_edge_length = function(graph) {
  Eattr(graph, "edge.length") %||% rep(1, ecount(graph))
}
