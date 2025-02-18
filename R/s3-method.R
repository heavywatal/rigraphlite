#' S3 methods to get and view internal data.
#'
#' @param x igraph_ptr object.
#' @param ... passed to methods.
#' @seealso [graph_from_data_frame()], [graph_from_symbolic_edgelist()]
#' @rdname s3-method
#' @export
as.data.frame.igraph_ptr = function(x, ...) {
  .Call(`_igraphlite_as_data_frame_`, x)
}

#' @rdname s3-method
#' @export
as.matrix.igraph_ptr = function(x, ...) {
  .Call(`_igraphlite_as_edgelist_`, x)
}

#' @rdname s3-method
#' @export
print.igraph_ptr = function(x, ...) {
  cat("$V  ")
  utils::str(Vattr(x))
  print(as.data.frame(x), ...)
  invisible(x)
}

#' @importFrom generics augment
#' @export
generics::augment

#' Methods for quick visualization
#'
#' @param x igraph_ptr object.
#' @param layout A function or resulting data.frame.
#'   If not provided, [layout_nicely()] is applied.
#' @param ... passed to [augment()] or layout function.
#' @rdname plot
#' @export
augment.igraph_ptr = function(x, layout = NULL, ...) {
  if (is.null(layout)) {
    layout = layout_nicely(x, ...)
  } else if (is.function(layout)) {
    layout = layout(x, ...)
  }
  if (is.data.frame(layout)) {
    stopifnot(utils::hasName(layout, c("x", "y")))
    stopifnot(nrow(layout) == vcount(x))
  } else {
    stop("Invalid type '", typeof(layout), "' for argument 'layout'", call. = FALSE)
  }
  root = Vsource(x)
  from = c(root, igraph_from(x))
  to = c(root, igraph_to(x))
  segment_df(from, to, layout[["x"]], layout[["y"]], Vnames(x))
}

segment_df = function(from, to, x, y, vnames = NULL) {
  .df = data.frame(
    from, to,
    x = x[to],
    y = y[to],
    xend = x[from],
    yend = y[from]
  )
  if (!is.null(vnames)) {
    .df$from = vnames[from]
    .df$to = vnames[to]
  }
  class(.df) = c("tbl_df", "tbl", "data.frame")
  .df
}

#' @param lwd passed to [ggplot2::geom_segment()].
#' @param cex,col,pch passed to [ggplot2::geom_point()] and [ggplot2::geom_text()].
#' @rdname plot
#' @export
plot.igraph_ptr = function(x, ..., lwd = 0.5, cex = 5, col = "#cccccc", pch = 16) {
  .df = augment(x, ...)
  ggplot2::ggplot(.df) +
    ggplot2::aes(.data[["x"]], .data[["y"]]) +
    ggplot2::geom_segment(ggplot2::aes(xend = .data[["xend"]], yend = .data[["yend"]]), linewidth = lwd) +
    ggplot2::geom_point(shape = pch, size = cex, colour = col) +
    ggplot2::geom_text(ggplot2::aes(label = .data[["to"]]), size = cex * 0.6)
}
