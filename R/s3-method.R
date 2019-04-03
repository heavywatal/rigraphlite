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

#' @param layout A function or resulting data.frame
#' @export
augment.Rcpp_IGraph = function(x, layout = NULL, ...) {
  layout = if (is.null(layout)) {
    layout_nicely(x)
  } else if (is.function(layout)) {
    layout(x)
  } else if (!is.data.frame(layout)) {
    stop("Invalid type '", typeof(layout), "' for argument 'layout'")
  }
  root = x$source
  from = c(root, x$from)
  to = c(root, x$to)
  df_from = stats::setNames(layout[from, c("x", "y")], c("xfrom", "yfrom"))
  df_to = layout[to, c("x", "y")]
  df = cbind(from = as_vnames(x, from), to = as_vnames(x, to), df_to, df_from)
  class(df) = c("tbl_df", "tbl", "data.frame")
  df
}

#' @export
plot.Rcpp_IGraph = function(x, ..., lwd = 0.5, cex = 5, col = "#cccccc", pch = 16) {
  data = augment(x, ...)
  ggplot2::ggplot(data, ggplot2::aes_(~x, ~y)) +
    ggplot2::geom_segment(ggplot2::aes_(xend = ~xfrom, yend = ~yfrom), size = lwd) +
    ggplot2::geom_point(shape = pch, size = cex, colour = col) +
    ggplot2::geom_text(ggplot2::aes_(label = ~to), size = cex * 0.6)
}
