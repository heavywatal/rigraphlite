# Non-simple graphs: multiple and loop edges

Multiple edges are those that connect the same pair of vertices, where
the direction is also taken into account in directed graphs. Loop here
means auto-loop/self-loop, i.e., an edge that connects a vertex to
itself.

## Usage

``` r
is_simple(graph, directed = is_directed(graph))

has_loop(graph)

count_loops(graph)

has_multiple(graph)

count_multiple(graph, eids = integer(0L))
```

## Source

<https://igraph.org/c/doc/igraph-Structural.html#non-simple-graphs-multiple-and-loop-edges>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- directed:

  A logical value, whether to consider directed paths. Ignored for
  undirected graphs.

- eids:

  An integer vector of edge IDs.

## Value

Logical or integer values.

## Examples

``` r
g = graph_tree(5L)
g = add_edges(g, c(1L, 1L)) # add a loop
g = add_edges(g, c(1L, 2L)) # add a multiple edge
g = add_edges(g, c(2L, 1L)) # not a multiple edge in directed graph

is_simple(g)
#> [1] FALSE
has_loop(g)
#> [1] TRUE
count_loops(g)
#> [1] 1
has_multiple(g)
#> [1] TRUE
count_multiple(g)
#> [1] 2 1 1 1 1 2 1
```
