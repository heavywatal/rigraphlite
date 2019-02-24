#' Conversion between phylo and igraph
#'
#' @source <https://cran.r-project.org/package=ape>
#' @param x An object to convert.
#' @rdname phylo
#' @export
as_igraph.phylo = function(x) {
  g = graph_from_edgelist(x[["edge"]])
  g$Vattr[["name"]] = c(x[["tip.label"]], rep(NA, x[["Nnode"]]))
  g$Eattr[["edge.length"]] = x[["edge.length"]]
  g
}

#' @rdname phylo
#' @export
as_phylo = function(x) {
  structure(list(
    edge = phylo_edge(x),
    tip.label = phylo_tip_label(x),
    edge.length = phylo_edge_length(x),
    Nnode = x$vcount - sum(x$is_sink)
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

phylo_tip_label = function(graph) {
  tip.label = graph$Vattr[["name"]]
  if (is.null(tip.label)) {
    tip.label = graph$sink
  } else {
    tip.label = tip.label[graph$is_sink]
  }
  as.character(tip.label)
}

phylo_edge_length = function(graph) {
  edge.length = graph$Eattr[["edge.length"]]
  if (is.null(edge.length)) {
    edge.length = rep(1, graph$ecount)
  }
  edge.length
}
