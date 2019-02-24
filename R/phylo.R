#' Conversion between phylo and igraph
#'
#' @source <https://cran.r-project.org/package=ape>
#' @param x An object to convert.
#' @rdname phylo
#' @export
as_igraph.phylo = function(x) {
  g = graph_from_edgelist(x[["edge"]])
  node.label = x[["node.label"]] %||% rep(NA, x[["Nnode"]])
  g$Vattr[["name"]] = c(x[["tip.label"]], node.label)
  g$Eattr[["edge.length"]] = x[["edge.length"]]
  g
}

#' @rdname phylo
#' @export
as_phylo = function(x) {
  labels = Vname(x)
  is_sink = x$is_sink
  structure(list(
    edge = phylo_edge(x),
    tip.label = labels[is_sink],
    node.label = labels[!is_sink],
    edge.length = phylo_edge_length(x),
    Nnode = sum(!is_sink)
  ), class = "phylo", order = "cladewise")
}

# Tips must have younger IDs
phylo_edge = function(graph) {
  edgelist = graph$as_edgelist()
  target = c(graph$sink, setdiff(graph$V, graph$sink))
  edge = match(edgelist, target)
  class(edge) = "integer"
  dim(edge) = dim(edgelist)
  edge
}

Vname = function(graph) {
  graph$Vattr[["name"]] %||% graph$V
}

phylo_edge_length = function(graph) {
  graph$Eattr[["edge.length"]] %||% rep(1, graph$ecount)
}
