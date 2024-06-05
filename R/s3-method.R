#' @export
as.data.frame.Rcpp_IGraph = function(x, ...) {
  vnames = Vnames(x)
  df = data.frame(
    from = vnames[igraph_from(x)],
    to = vnames[igraph_to(x)],
    x$Eattr
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

#' Methods for quick visualization
#'
#' @param x Rcpp_Igraph object.
#' @param layout A function or resulting data.frame.
#'   If not provided, [layout_nicely] is applied.
#' @param ... passed to [augment] or layout function.
#' @rdname plot
#' @export
augment.Rcpp_IGraph = function(x, layout = NULL, ...) {
  if (is.null(layout)) {
    layout = layout_nicely(x, ...)
  } else if (is.function(layout)) {
    layout = layout(x, ...)
  }
  if (is.data.frame(layout)) {
    stopifnot(all(utils::hasName(layout, c("x", "y"))))
    stopifnot(nrow(layout) == vcount(x))
  } else {
    stop("Invalid type '", typeof(layout), "' for argument 'layout'")
  }
  root = Vsource(x)
  from = c(root, igraph_from(x))
  to = c(root, igraph_to(x))
  df = segment_df(from, to, layout[["x"]], layout[["y"]], Vnames(x))
  df
}

segment_df = function(from, to, x, y, vnames = NULL) {
  df = data.frame(
    from, to,
    x = x[to],
    y = y[to],
    xend = x[from],
    yend = y[from]
  )
  if (!is.null(vnames)) {
    df$from = vnames[from]
    df$to = vnames[to]
  }
  class(df) = c("tbl_df", "tbl", "data.frame")
  df
}

#' @param lwd passed to [ggplot2::geom_segment].
#' @param cex,col,pch passed to [ggplot2::geom_point] and [ggplot2::geom_text].
#' @rdname plot
#' @export
plot.Rcpp_IGraph = function(x, ..., lwd = 0.5, cex = 5, col = "#cccccc", pch = 16) {
  data = augment(x, ...)
  ggplot2::ggplot(data) +
    ggplot2::aes(.data[["x"]], .data[["y"]]) +
    ggplot2::geom_segment(ggplot2::aes(xend = .data[["xend"]], yend = .data[["yend"]]), linewidth = lwd) +
    ggplot2::geom_point(shape = pch, size = cex, colour = col) +
    ggplot2::geom_text(ggplot2::aes(label = .data[["to"]]), size = cex * 0.6)
}
