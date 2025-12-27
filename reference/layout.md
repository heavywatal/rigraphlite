# Choose a layout algorithm automatically

Layout functions add `x` and `y` vertex attributes to the graph object.
The object is modified in place, and its shallow copy is returned.

## Usage

``` r
layout_nicely(graph, ...)
```

## Source

<https://r.igraph.org/reference/layout_nicely.html>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- ...:

  Additional arguments passed to the layout function.

## Value

An
[`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object with vertex attributes `x` and `y`.

## See also

Other layouts:
[`layout_random()`](https://heavywatal.github.io/rigraphlite/reference/layout-2d.md),
[`layout_reingold_tilford()`](https://heavywatal.github.io/rigraphlite/reference/layout-tree.md)

## Examples

``` r
layout_nicely(graph_tree(5L)) |> Vattr()
#> # A tibble: 5 × 2
#>        x     y
#>    <dbl> <dbl>
#> 1 -3.00  1.85 
#> 2 -1.50  1.92 
#> 3 -4.29  1.80 
#> 4 -0.694 2.95 
#> 5 -0.612 0.961
```
