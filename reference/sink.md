# Shortcuts to get sink/source vertices.

These are simple wrappers around
[`degree()`](https://heavywatal.github.io/rigraphlite/reference/basic-adjacent.md)
to get zero-degree vertices.

## Usage

``` r
is_sink(graph)

is_source(graph)

Vsink(graph)

Vsource(graph)
```

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

## Value

`is_sink()` and `is_source()` return a logical vector indicating whether
the vertices in the graph are terminating or starting points,
respectively.

`Vsink()` and `Vsource()` return the terminating and starting vertices
of a graph, respectively.

## Examples

``` r
g = graph_tree(5L)
is_sink(g)
#> [1] FALSE FALSE  TRUE  TRUE  TRUE
is_source(g)
#> [1]  TRUE FALSE FALSE FALSE FALSE
Vsink(g)
#> [1] 3 4 5
Vsource(g)
#> [1] 1
```
