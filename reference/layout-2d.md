# 2D layout generators

Layout functions add `x` and `y` vertex attributes to the graph object.
The object is modified in place, and its shallow copy is returned.

## Usage

``` r
layout_random(graph)

layout_circle(graph, order = integer(0L))

layout_star(graph, center, order = integer(0L))

layout_grid(graph, width = 0L)

layout_drl(graph)

layout_fruchterman_reingold(graph, grid = 2L)

layout_mds(graph, dist)
```

## Source

<https://igraph.org/c/doc/igraph-Layout.html#two-d-layout-generators>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- order:

  An integer vector of vertex IDs including `center`.

- center:

  An vertex ID.

- width:

  The number of vertices in a single row of the grid.

- grid:

  An integer value, whether to use the (fast but less accurate) grid
  based algorithm; {0: GRID, 1: NOGRID, 2: AUTOGRID}.

- dist:

  A distance matrix.

## Value

An
[`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object with vertex attributes `x` and `y`.

## See also

Other layouts:
[`layout_nicely()`](https://heavywatal.github.io/rigraphlite/reference/layout.md),
[`layout_reingold_tilford()`](https://heavywatal.github.io/rigraphlite/reference/layout-tree.md)

## Examples

``` r
igraph_rng_seed(24601L)
g = graph_tree(5L)

layout_random(g) |> Vattr()
#> # A tibble: 5 × 2
#>        x       y
#>    <dbl>   <dbl>
#> 1 -0.298 -0.124 
#> 2  0.544 -0.347 
#> 3  0.364 -0.209 
#> 4 -0.577 -0.671 
#> 5 -0.338  0.0251

layout_circle(g) |> Vattr()
#> # A tibble: 5 × 2
#>        x      y
#>    <dbl>  <dbl>
#> 1  1      0    
#> 2  0.309  0.951
#> 3 -0.809  0.588
#> 4 -0.809 -0.588
#> 5  0.309 -0.951

layout_star(g, center = 1L) |> Vattr()
#> # A tibble: 5 × 2
#>           x         y
#>       <dbl>     <dbl>
#> 1  0         0       
#> 2  1   e+ 0  0       
#> 3  6.12e-17  1   e+ 0
#> 4 -1   e+ 0  1.22e-16
#> 5 -1.84e-16 -1   e+ 0

layout_grid(g) |> Vattr()
#> # A tibble: 5 × 2
#>       x     y
#>   <dbl> <dbl>
#> 1     0     0
#> 2     1     0
#> 3     2     0
#> 4     0     1
#> 5     1     1

layout_drl(g) |> Vattr()
#> # A tibble: 5 × 2
#>       x     y
#>   <dbl> <dbl>
#> 1 -12.7 -5.17
#> 2 -12.2 -5.90
#> 3 -12.9 -4.65
#> 4 -12.7 -6.55
#> 5 -11.7 -5.98

layout_fruchterman_reingold(g) |> Vattr()
#> # A tibble: 5 × 2
#>        x      y
#>    <dbl>  <dbl>
#> 1  0.225 -0.296
#> 2 -1.28  -0.235
#> 3  1.51  -0.349
#> 4 -2.16  -1.20 
#> 5 -2.08   0.795

layout_mds(g, dist = distances(g)) |> Vattr()
#> # A tibble: 5 × 2
#>        x         y
#>    <dbl>     <dbl>
#> 1  0.707 -5.38e-16
#> 2 -0.354  8.32e-17
#> 3  1.77  -1.90e-17
#> 4 -1.06  -1   e+ 0
#> 5 -1.06   1.00e+ 0
```
