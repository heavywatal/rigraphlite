#' Conversion between tbl_tree and igraph
#'
#' @source <https://cran.r-project.org/package=tidytree>
#' @param x An object to convert.

#' @rdname tbl_tree
#' @export
as_igraph.tbl_tree = function(x) {
  el = cbind(x[["parent"]], x[["node"]])
  idx = (el[, 1L] != el[, 2L])
  g = graph_from_edgelist(el[idx, ])
  g$Vattr[["name"]] = x[["label"]]
  g$Eattr[["branch.length"]] = x[["branch.length"]][idx]
  g
}

#' @rdname tbl_tree
#' @export
as_tbl_tree = function(x) {
  el = phylo_edge(x)
  colnames(el) = c("parent", "node")
  root = setdiff(x$V, el[, 2L])
  res = as.data.frame(rbind(c(root, root), el))
  res["branch.length"] = c(NA_real_, branch_length(x))
  res = res[order(res[["node"]]), ]
  old_ids = c(x$sink, setdiff(x$V, x$sink))
  res["label"] = Vnames(x)[old_ids[res[["node"]]]]
  row.names(res) = seq_len(nrow(res))
  class(res) = c("tbl_tree", "tbl_df", "tbl", "data.frame")
  res
}

branch_length = function(graph) {
  graph$Eattr[["branch.length"]] %||% rep(1, graph$ecount)
}
