# Efficiency measures

The global efficiency of a network is defined as the average of inverse
distances. The local efficiency of a network around a vertex is the
global efficiency of the subgraph after removing the vertex.

## Usage

``` r
global_efficiency(graph, weights = numeric(0L), directed = is_directed(graph))

local_efficiency(
  graph,
  weights = numeric(0L),
  vids = integer(0L),
  directed = is_directed(graph),
  mode = 3L
)

average_local_efficiency(
  graph,
  weights = numeric(0L),
  directed = is_directed(graph),
  mode = 3L
)
```

## Source

<https://igraph.org/c/doc/igraph-Structural.html#efficiency-measures>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- weights:

  A numeric vector of edge weights; `TRUE` to use
  `Eattr(graph, "weight")`.

- directed:

  A logical value, whether to consider directed paths. Ignored for
  undirected graphs.

- vids:

  An integer vector of vertex IDs.

- mode:

  An integer value of edge type to count; {1: OUT, 2: IN, 3: ALL}.

## Value

A numeric vector.

## Examples

``` r
g = graph_tree(7L, mode = 2L)
global_efficiency(g)
#> [1] 0.5634921

local_efficiency(g)
#> [1] 0 0 0 0 0 0 0

average_local_efficiency(g)
#> [1] 0
```
