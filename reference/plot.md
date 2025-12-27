# Methods for quick visualization

Vertex attributes "x" and "y" are used as the cartesian coordinates for
plotting. They can be set by layout functions beforehand, or within
[`augment()`](https://generics.r-lib.org/reference/augment.html).
[`plot()`](https://rdrr.io/r/graphics/plot.default.html) internally
calls [`augment()`](https://generics.r-lib.org/reference/augment.html).

## Usage

``` r
# S3 method for class 'igraph_ptr'
augment(x, layout = NULL, ...)

# S3 method for class 'igraph_ptr'
plot(x, ..., lwd = 0.6, cex = 6, col = "#cccccc", pch = 16)
```

## Arguments

- x:

  An
  [igraph_ptr](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- layout:

  A layout function or a `Vattr(x)`-like data.frame with "x" and "y". If
  not provided,
  [`layout_nicely()`](https://heavywatal.github.io/rigraphlite/reference/layout.md)
  is applied, which does nothing if "x" and "y" are already set in
  vertex attributes.

- ...:

  Extra arguments passed to the layout function.

- lwd:

  Passed to
  [`ggplot2::geom_segment()`](https://ggplot2.tidyverse.org/reference/geom_segment.html).

- cex, col, pch:

  Passed to
  [`ggplot2::geom_point()`](https://ggplot2.tidyverse.org/reference/geom_point.html)
  and
  [`ggplot2::geom_text()`](https://ggplot2.tidyverse.org/reference/geom_text.html).

## Value

[`augment()`](https://generics.r-lib.org/reference/augment.html) returns
a data frame to be used with
[`ggplot2::ggplot()`](https://ggplot2.tidyverse.org/reference/ggplot.html).

`plot.igraph_ptr()` returns a ggplot object.

## See also

[`layout_random()`](https://heavywatal.github.io/rigraphlite/reference/layout-2d.md)
and others for layout functions.

## Examples

``` r
g = graph_tree(5L) |> layout_reingold_tilford()

augment(g)
#> # A tibble: 5 × 6
#>    from    to     x     y  xend  yend
#>   <int> <int> <dbl> <dbl> <dbl> <dbl>
#> 1     1     1   0       0   0       0
#> 2     1     2  -0.5     1   0       0
#> 3     1     3   0.5     1   0       0
#> 4     2     4  -1       2  -0.5     1
#> 5     2     5   0       2  -0.5     1

plot(g) + ggplot2::theme_minimal(base_size = 14)
```
