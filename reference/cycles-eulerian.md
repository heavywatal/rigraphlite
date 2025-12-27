# Eulerian cycles and paths

An Eulerian path traverses each edge of the graph precisely once. A
closed Eulerian path is referred to as an Eulerian cycle.

## Usage

``` r
is_eulerian(graph)
```

## Source

<https://igraph.org/c/doc/igraph-Cycles.html#eulerian-cycles>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

## Value

A logical value with two elements: "has a path" and "has a cycle".

## Examples

``` r
is_eulerian(graph_tree(5L))
#> [1] FALSE FALSE

is_eulerian(graph_square_lattice(5L))
#> [1]  TRUE FALSE

is_eulerian(graph_ring(5L))
#> [1] TRUE TRUE
```
