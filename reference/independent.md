# Independent vertex sets

A vertex set is considered independent if there are no edges between
them.

## Usage

``` r
is_independent_vertex_set(graph, candidate = integer(0L))

independent_vertex_sets(
  graph,
  min_size = 0L,
  max_size = -1L,
  max_results = -1L
)

largest_independent_vertex_sets(graph)

maximal_independent_vertex_sets(
  graph,
  min_size = 0L,
  max_size = -1L,
  max_results = -1L
)

independence_number(graph)
```

## Source

<https://igraph.org/c/doc/igraph-Cliques.html#independent-vertex-sets>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- candidate:

  The vertex set to test for being a clique.

- min_size, max_size:

  An integer specifying the minimum/maximum size of the sets to be
  returned. If negative or zero, no lower bound will be used.

- max_results:

  At most this many sets will be recorded. If negative, no limit is
  applied.
