#' @export
as.data.frame.Rcpp_IGraph = function(x, ...) {
  df = data.frame(
    from = as_vnames(x, x$from),
    to = as_vnames(x, x$to),
    x$Eattr,
    stringsAsFactors = FALSE
  )
  class(df) = c("tbl_df", "tbl", "data.frame")
  df
}

#' @export
as.matrix.Rcpp_IGraph = function(x, ...) {
  x$as_edgelist()
}

#' @importFrom generics augment
#' @export
generics::augment

#' @export
augment.Rcpp_IGraph = function(x, ...) {
  if (!all(utils::hasName(x$Vattr, c("x", "y")))) {
    layout_nicely(x)
  }
  root = x$source
  from = c(root, x$from)
  to = c(root, x$to)
  df_from = x$Vattr[from, c("x", "y")]
  df_to = stats::setNames(x$Vattr[to, c("x", "y")], c("xend", "yend"))
  df = cbind(from = as_vnames(x, from), to = as_vnames(x, to), df_from, df_to)
  class(df) = c("tbl_df", "tbl", "data.frame")
  df
}

#' @export
plot.Rcpp_IGraph = function(x, ...) {
  data = augment(x, ...)
  ggplot2::ggplot(data) +
    ggplot2::geom_segment(ggplot2::aes_(~x, ~y, xend = ~xend, yend = ~yend))
}
