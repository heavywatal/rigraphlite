# Adding and deleting vertices and edges

Unlike many other R functions, these functions modify a graph in place.
The shallow copy of the graph is returned invisibly, which can be used
with the pipe operator, but does not need to be assigned to a variable.

## Usage

``` r
add_edges(graph, edges)

add_vertices(graph, n)

delete_edges(graph, eids)

delete_vertices(graph, vids)
```

## Source

<https://igraph.org/c/html/latest/igraph-Basic.html#adding-and-deleting-vertices-and-edges>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- edges:

  An integer vector of vertex IDs; the first two elements are the first
  edge, etc.

- n:

  An integer, the number of vertices to add.

- eids:

  An integer vector of edge IDs.

- vids:

  An integer vector of vertex IDs.

## Value

A shallow copy of the modified
[`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object.

## See also

[`graph_copy()`](https://heavywatal.github.io/rigraphlite/reference/constructors.md)
for shallow vs. deep copy of graph objects.

## Examples

``` r
g = graph_empty()

# The graph is modified in place
add_vertices(g, 6L)
add_edges(g, c(1L, 2L))
g
#> $V  tibble [6 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 1 × 2
#>    from    to
#>   <int> <int>
#> 1     1     2

# Invisibly returned objects can be used with the pipe operator.
g |>
  add_edges(c(3L, 4L)) |>
  delete_edges(1L) |>
  delete_vertices(6L) |>
  print()
#> $V  tibble [5 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 1 × 2
#>    from    to
#>   <int> <int>
#> 1     3     4

# No need to assign the result
g
#> $V  tibble [5 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 1 × 2
#>    from    to
#>   <int> <int>
#> 1     3     4
```
