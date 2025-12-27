# Basic Properties

Basic Properties

## Usage

``` r
are_adjacent(graph, from, to)
```

## Source

<https://igraph.org/c/doc/igraph-Structural.html#basic-properties>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- from:

  An integer vector of vertex IDs.

- to:

  An integer vector of vertex IDs.

## Value

A logical, `TRUE` if `from` and `to` are adjacent, `FALSE` otherwise.

## See also

[`edge()`](https://heavywatal.github.io/rigraphlite/reference/basic-adjacent.md),
[`neighbors()`](https://heavywatal.github.io/rigraphlite/reference/basic-adjacent.md),
[`incident()`](https://heavywatal.github.io/rigraphlite/reference/basic-adjacent.md)
for similar operations.
[`as_adjlist()`](https://heavywatal.github.io/rigraphlite/reference/adjlist.md)
and
[`degree()`](https://heavywatal.github.io/rigraphlite/reference/basic-adjacent.md)
can apply to all vertices at once.

## Examples

``` r
g = graph_tree(5L)
are_adjacent(g, 1L, 2L)
#> [1] TRUE
are_adjacent(g, 1L, 4L)
#> [1] FALSE
```
