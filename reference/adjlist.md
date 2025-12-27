# Adjacency lists and incidence lists

Both lists have the same length as the number of vertices in the graph.

## Usage

``` r
as_adjlist(graph, mode = 3L, loops = 1L, multiple = TRUE)

as_inclist(graph, mode = 3L, loops = 1L)
```

## Source

<https://igraph.org/c/doc/igraph-Data-structures.html#igraph-Adjlists>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- mode:

  An integer value of edge type to count; {1: OUT, 2: IN, 3: ALL}.

- loops:

  An integer value, how to treat loop edges; {0: NO_LOOPS, 1:
  LOOPS/LOOPS_TWICE, 2: LOOPS_ONCE}

- multiple:

  A logical value, whether to keep multiple (parallel) edges.

## Value

`as_adjlist()` returns a list of adjacent vertices for each vertex.

`as_inclist()` returns a list of incident edges for each vertex.

## See also

[`neighbors()`](https://heavywatal.github.io/rigraphlite/reference/basic-adjacent.md)
and
[`incident()`](https://heavywatal.github.io/rigraphlite/reference/basic-adjacent.md)
for single-vertex version.

## Examples

``` r
g = graph_tree(5L)
as_adjlist(g, mode = 1L)
#> [[1]]
#> [1] 2 3
#> 
#> [[2]]
#> [1] 4 5
#> 
#> [[3]]
#> integer(0)
#> 
#> [[4]]
#> integer(0)
#> 
#> [[5]]
#> integer(0)
#> 
as_inclist(g, mode = 1L)
#> [[1]]
#> [1] 1 2
#> 
#> [[2]]
#> [1] 3 4
#> 
#> [[3]]
#> integer(0)
#> 
#> [[4]]
#> integer(0)
#> 
#> [[5]]
#> integer(0)
#> 
```
