# The simple interface for graph isomorphism

In simple terms, two graphs are isomorphic if they become
indistinguishable from each other once their vertex labels are removed.

## Usage

``` r
isomorphic(graph1, graph2)

subisomorphic(graph1, graph2)
```

## Source

<https://igraph.org/c/html/latest/igraph-Isomorphism.html#isomorphism-simple-interface>

## Arguments

- graph1, graph2:

  Two
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  objects to compare.

## Value

A logical value.

`subisomorphic()` returns `TRUE` if `graph2` is isomorphic to a subgraph
of `graph1`.

## See also

[`is_same_graph()`](https://heavywatal.github.io/rigraphlite/reference/basic-macros.md).

## Examples

``` r
g1 = graph_create(c(1L, 2L, 1L, 3L), directed = FALSE)
g2 = graph_create(c(3L, 2L, 3L, 1L), directed = FALSE)
isomorphic(g1, g2)
#> [1] TRUE
subisomorphic(g1, g2)
#> [1] TRUE

g3 = graph_create(c(1L, 2L, 1L, 3L, 3L, 4L), directed = FALSE)
subisomorphic(g3, g1)
#> [1] TRUE
subisomorphic(g1, g3)
#> [1] FALSE
```
