# Cliques

A graph is considered complete if all pairs of different vertices are
adjacent. Cliques are fully connected subgraphs of a graph.

## Usage

``` r
is_complete(graph)

is_clique(graph, candidate = integer(0L), directed = is_directed(graph))

cliques(graph, min_size = 0L, max_size = -1L, max_results = -1L)

clique_size_hist(graph, min_size = 0L, max_size = -1L)

largest_cliques(graph)

maximal_cliques(graph, min_size = 0L, max_size = -1L, max_results = -1L)

maximal_cliques_count(graph, min_size = 0L, max_size = -1L)

maximal_cliques_hist(graph, min_size = 0L, max_size = -1L)

clique_number(graph)
```

## Source

<https://igraph.org/c/doc/igraph-Cliques.html#cliques>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- candidate:

  The vertex set to test for being a clique.

- directed:

  A logical value, whether to consider directed paths. Ignored for
  undirected graphs.

- min_size, max_size:

  An integer specifying the minimum/maximum size of the sets to be
  returned. If negative or zero, no lower bound will be used.

- max_results:

  At most this many sets will be recorded. If negative, no limit is
  applied.

## Value

`is_complete()` and `is_clique()` return a logical value.
