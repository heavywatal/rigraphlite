# Neighborhood of vertices

Neighborhood of vertices

## Usage

``` r
neighborhood_size(
  graph,
  vids = integer(0),
  order = 1L,
  mode = 1L,
  mindist = 0L
)

neighborhood(graph, vids = integer(0), order = 1L, mode = 1L, mindist = 0L)
```

## Source

<https://igraph.org/c/doc/igraph-Structural.html#neighborhood-of-a-vertex>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- vids:

  An integer vector of vertex IDs.

- order:

  An integer giving the order of the neighborhood; e.g., `order = 1L`
  considers only the immediate neighbors.

- mode:

  An integer value of edge type to count; {1: OUT, 2: IN, 3: ALL}.

- mindist:

  The minimum distance to include a vertex in the counting; e.g.,
  `mindist = 1L` excludes the starting vertex itself, and `2L` excludes
  the immediate neighbors.

## Value

`neighborhood_size()` returns an integer vector of the neighborhood
sizes for the given vertices.

`neighborhood()` returns a list of integer vectors, each containing the
vertex IDs of the neighbors of the given vertices.

## Examples

``` r
g = graph_tree(5L)
neighborhood_size(g)
#> [1] 3 3 1 1 1
neighborhood(g)
#> [[1]]
#> [1] 1 2 3
#> 
#> [[2]]
#> [1] 2 4 5
#> 
#> [[3]]
#> [1] 3
#> 
#> [[4]]
#> [1] 4
#> 
#> [[5]]
#> [1] 5
#> 
```
