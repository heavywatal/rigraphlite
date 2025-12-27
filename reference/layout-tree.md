# Layouts for trees and acyclic graphs

Layout functions add `x` and `y` vertex attributes to the graph object.
The object is modified in place, and its shallow copy is returned.

## Usage

``` r
layout_reingold_tilford(graph, mode = 1L, roots = integer(0))

layout_reingold_tilford_circular(graph, mode = 1L, roots = integer(0))
```

## Source

<https://igraph.org/c/doc/igraph-Layout.html#layouts-for-trees-and-acyclic-graphs>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- mode:

  An integer value of edge type to count; {1: OUT, 2: IN, 3: ALL}.

- roots:

  An integer vector of vertex IDs, the roots of the tree.

## Value

An
[`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object with vertex attributes `x` and `y`.

## See also

Other layouts:
[`layout_nicely()`](https://heavywatal.github.io/rigraphlite/reference/layout.md),
[`layout_random()`](https://heavywatal.github.io/rigraphlite/reference/layout-2d.md)

## Examples

``` r
g = graph_tree(5L)

layout_reingold_tilford(g) |> Vattr()
#> # A tibble: 5 × 2
#>       x     y
#>   <dbl> <dbl>
#> 1   0       0
#> 2  -0.5     1
#> 3   0.5     1
#> 4  -1       2
#> 5   0       2

layout_reingold_tilford_circular(g) |> Vattr()
#> # A tibble: 5 × 2
#>        x      y
#>    <dbl>  <dbl>
#> 1  0      0    
#> 2 -0.105  0.995
#> 3  0.309 -0.951
#> 4  2      0    
#> 5 -1.96  -0.416
```
