# Graph Components

Graph Components

## Usage

``` r
subcomponent(graph, vid, mode = 1L)

connected_components(graph, connectedness = 1L)

is_connected(graph, connectedness = 1L)

count_reachable(graph, mode = 1L)

transitive_closure(graph)

articulation_points(graph)

bridges(graph)

is_biconnected(graph)

subcomponents(graph, vids, mode = 1L)
```

## Source

<https://igraph.org/c/doc/igraph-Structural.html#graph-components>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- vid:

  An integer value of vertex ID.

- mode:

  An integer value of edge type to count; {1: OUT, 2: IN, 3: ALL}.

- connectedness:

  An integer indicating the type of connectedness: {1: WEAK (ignore edge
  directions), 2: STRONG}

- vids:

  An integer vector of vertex IDs.

## Value

`subcomponent()` returns the IDs of the vertices reachable from the
given vertex.

`connected_components()` returns component IDs for each vertex.

`is_connected()` and `is_biconnected()` return logical values.

`count_reachable()` returns an integer vector of the number of reachable
vertices from each vertex including itself.

`transitive_closure()` returns the transitive closure graph.

`articulation_points()` and `bridges()` return vertex IDs and edge IDs,
respectively.

`subcomponents()` returns a list of integer vectors by applying
`subcomponent()` for each vertex in `vids`.

## See also

[`induced_subgraph()`](https://heavywatal.github.io/rigraphlite/reference/subgraph.md)

## Examples

``` r
g = graph_tree(5L)
subcomponent(g, 2L)
#> [1] 2 4 5

connected_components(g)
#> [1] 1 1 1 1 1

is_connected(g)
#> [1] TRUE

count_reachable(g)
#> [1] 5 3 1 1 1

transitive_closure(g)
#> $V  tibble [5 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 6 × 2
#>    from    to
#>   <int> <int>
#> 1     1     2
#> 2     1     3
#> 3     1     4
#> 4     1     5
#> 5     2     4
#> 6     2     5

articulation_points(g)
#> [1] 2 1

bridges(g)
#> [1] 3 4 1 2

is_biconnected(g)
#> [1] FALSE

subcomponents(g, c(1L, 2L))
#> [[1]]
#> [1] 1 2 3 4 5
#> 
#> [[2]]
#> [1] 2 4 5
#> 
```
