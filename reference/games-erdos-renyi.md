# The Erdős-Rényi and related models

Classical random graph models with a fixed number of vertices.

## Usage

``` r
erdos_renyi_game_gnm(n, m, directed = FALSE, edge_type_sw = 0L)

erdos_renyi_game_gnp(n, p, directed = FALSE, edge_type_sw = 0L)
```

## Source

<https://igraph.org/c/html/latest/igraph-Games.html#erdos-renyi-games>

## Arguments

- n:

  The number of vertices.

- m:

  The number of edges.

- directed:

  A logical value, whether to consider directed paths. Ignored for
  undirected graphs.

- edge_type_sw:

  The types of edges to allow in the graph: {0: simple, 1: loops, 6:
  multiple, 7: loops and multiple}.

- p:

  The probability of edge creation or rewiring.

## Value

An
[`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object.

## Examples

``` r
gnm = erdos_renyi_game_gnm(5L, 5L)
gnp = erdos_renyi_game_gnp(5L, 0.5)
```
