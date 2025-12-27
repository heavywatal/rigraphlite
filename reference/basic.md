# Basic query operations

Basic query operations

## Usage

``` r
vcount(graph)

ecount(graph)

is_directed(graph)
```

## Source

<https://igraph.org/c/doc/igraph-Basic.html#basic-query-operations>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

## Value

`vcount()` returns the number of vertices in a graph.

`ecount()` returns the number of edges in a graph.

`is_directed()` returns whether the graph is directed.

## Examples

``` r
g = graph_tree(5L)
vcount(g)
#> [1] 5
ecount(g)
#> [1] 4
is_directed(g)
#> [1] TRUE
```
