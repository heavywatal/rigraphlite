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
