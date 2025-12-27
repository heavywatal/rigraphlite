# Degree-constrained models

Random graph models with hard or soft degree constraints.

`rewire()` creates a copy of the input graph, and performs `n_trials` of
edge rewirings while preserving the degree sequence.

## Usage

``` r
degree_sequence_game(out_degrees, in_degrees = integer(0), degseq_method = 0L)

k_regular_game(n, k, directed = FALSE, multiple = FALSE)

rewire(graph, n_trials, edge_type_sw = 0L)
```

## Source

<https://igraph.org/c/html/latest/igraph-Games.html#degree-constrained-games>

## Arguments

- out_degrees, in_degrees:

  Integer vectors giving the degree sequences. Undirected graphs are
  generated if an empty `in_degrees` is given.

- degseq_method:

  The method to generate a graph from the degree sequence: {0: smallest,
  1: largest, 2: index}.

- n:

  The number of vertices.

- k:

  The degree of each vertex in an undirected graph, or the out-degree
  and in-degree of each vertex in a directed graph.

- directed:

  A logical value, whether to consider directed paths. Ignored for
  undirected graphs.

- multiple:

  A logical value, whether to keep multiple (parallel) edges.

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- n_trials:

  The number of rewiring trials to perform.

- edge_type_sw:

  The types of edges to allow in the graph: {0: simple, 1: loops, 6:
  multiple, 7: loops and multiple}.

## Value

An
[`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object.

## See also

[`rewire_edges()`](https://heavywatal.github.io/rigraphlite/reference/games-edge-rewiring.md)
for an edge rewiring model without degree constraints.

## Examples

``` r
out_deg = seq_len(4L)
undirected = degree_sequence_game(out_deg)
degree(undirected)
#> [1] 1 2 3 4

in_deg = rev(out_deg)
directed = degree_sequence_game(out_deg, in_deg)
degree(directed, mode = 1L)
#> [1] 1 2 3 4
degree(directed, mode = 2L)
#> [1] 4 3 2 1

k_regular = k_regular_game(7L, 2L)
degree(k_regular)
#> [1] 2 2 2 2 2 2 2
degree(rewire(k_regular, 9L))
#> [1] 2 2 2 2 2 2 2
```
