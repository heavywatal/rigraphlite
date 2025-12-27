# Edge rewiring models

`rewire_edges()` creates a copy of the input graph, and rewires edges
randomly with probability `p` for each edge.

## Usage

``` r
watts_strogatz_game(dim, size, nei, p, edge_type_sw = 0L)

rewire_edges(graph, p, edge_type_sw = 0L)
```

## Source

<https://igraph.org/c/html/latest/igraph-Games.html#edge-rewiring-games>

## Arguments

- dim:

  The dimension of the lattice.

- size:

  The size of the lattice along each dimension.

- nei:

  The size of the neighborhood for each vertex.

- p:

  The probability of edge creation or rewiring.

- edge_type_sw:

  The types of edges to allow in the graph: {0: simple, 1: loops, 6:
  multiple, 7: loops and multiple}.

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

## Value

An
[`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object.

## See also

[`rewire()`](https://heavywatal.github.io/rigraphlite/reference/games-degree-constrained.md)
for the degree-preserving edge rewiring model.

## Examples

``` r
regular = watts_strogatz_game(1L, 20L, 2L, 0)
random = watts_strogatz_game(1L, 20L, 2L, 1)
small_world = watts_strogatz_game(1L, 20L, 2L, 0.1)
small_world2 = rewire_edges(regular, 0.1)
```
