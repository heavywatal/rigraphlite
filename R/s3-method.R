#' @export
as.data.frame.Rcpp_IGraph = function(x, ...) {
  x$as_data_frame
}

#' @export
as.matrix.Rcpp_IGraph = function(x, ...) {
  x$as_edgelist
}
