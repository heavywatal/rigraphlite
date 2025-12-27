# Miscellaneous operators

`induced_subgraph()` can be achieved in two steps with
`induced_subgraph_edges()` and `subgraph_from_edges()`, but it is much
slower than expected.

## Usage

``` r
induced_subgraph(graph, vids, impl = 0L)

induced_subgraph_edges(graph, vids)

subgraph_from_edges(graph, eids, delete_vertices = TRUE)
```

## Source

<https://igraph.org/c/doc/igraph-Operators.html#miscellaneous-operators>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- vids:

  An integer vector of vertex IDs.

- impl:

  An integer value, how to construct a new graph: {0: AUTO, 1:
  COPY_AND_DELETE, 2: CREATE_FROM_SCRATCH}

- eids:

  An integer vector of edge IDs.

- delete_vertices:

  whether to delete the unused vertices.

## Value

An
[`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object.

## See also

[`delete_vertices()`](https://heavywatal.github.io/rigraphlite/reference/basic-add-delete.md)

## Examples

``` r
g = graph_tree(5L)
induced_subgraph(g, seq_len(3L))
#> $V  tibble [3 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 2 × 2
#>    from    to
#>   <int> <int>
#> 1     1     2
#> 2     1     3

edges = induced_subgraph_edges(g, seq_len(3L)) |> print()
#> [1] 1 2

subgraph_from_edges(g, edges)
#> $V  tibble [3 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 2 × 2
#>    from    to
#>   <int> <int>
#> 1     1     2
#> 2     1     3
```
