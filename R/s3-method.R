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
#' Vertex attributes "x" and "y" are used as the cartesian coordinates for plotting.
#' They can be set by layout functions beforehand, or within `augment()`.
#' `plot()` internally calls `augment()`.
#' @param x An [igraph_ptr] object.
#' @param layout A layout function or a `Vattr(x)`-like data.frame with "x" and "y".
#'   If not provided, [layout_nicely()] is applied,
#'   which does nothing if "x" and "y" are already set in vertex attributes.
#' @param ... Extra arguments passed to the layout function.
#' @returns `augment()` returns a data frame to be used with [ggplot2::ggplot()].
#' @seealso [layout_random()] and others for layout functions.
#' @rdname plot
#' @export
#' @examples
#' g = graph_tree(5L) |> layout_reingold_tilford()
#'
#' augment(g)
#'
#' plot(g) + ggplot2::theme_minimal(base_size = 14)
augment.igraph_ptr = function(x, layout = NULL, ...) {
  if (is.null(layout)) {
    layout_nicely(x, ...)
  } else if (is.function(layout)) {
    layout(x, ...)
  } else if (is.data.frame(layout)) {
    stopifnot(utils::hasName(layout, c("x", "y")))
    stopifnot(nrow(layout) == vcount(x))
    Vattr(x, "x") = layout$x
    Vattr(x, "y") = layout$y
  } else {
    stop("Invalid type '", typeof(layout), "' for argument 'layout'", call. = FALSE)
  }
  root = Vsource(x)
  from = c(root, igraph_from(x))
  to = c(root, igraph_to(x))
  segment_df(from, to, Vattr(x)$x, Vattr(x)$y, Vnames(x))
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

#' @param lwd Passed to [ggplot2::geom_segment()].
#' @param cex,col,pch Passed to [ggplot2::geom_point()] and [ggplot2::geom_text()].
#' @returns `plot.igraph_ptr()` returns a ggplot object.
#' @rdname plot
#' @export
plot.igraph_ptr = function(x, ..., lwd = 0.6, cex = 6, col = "#cccccc", pch = 16) {
  .df = augment(x, ...)
  ggplot2::ggplot(.df) +
    ggplot2::aes(.data$x, .data$y) +
    ggplot2::geom_segment(ggplot2::aes(xend = .data$xend, yend = .data$yend), linewidth = lwd) +
    ggplot2::geom_point(shape = pch, size = cex, colour = col) +
    ggplot2::geom_text(ggplot2::aes(label = .data$to), size = cex * 0.6)
}
