# Create a graph with the specified edges

Create a graph with the specified edges

## Usage

``` r
graph_create(edges, n = 0L, directed = TRUE)
```

## Arguments

- edges:

  An integer vector of vertex IDs; the first two elements are the first
  edge, etc.

- n:

  An integer value, the number of vertices.

- directed:

  A logical value, whether to consider directed paths. Ignored for
  undirected graphs.

## Value

An
[`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object.

## See also

[`as_igraph()`](https://heavywatal.github.io/rigraphlite/reference/conversion.md),
[`graph_from_data_frame()`](https://heavywatal.github.io/rigraphlite/reference/conversion-impl.md)

Other deterministic generators:
[`graph_empty()`](https://heavywatal.github.io/rigraphlite/reference/constructors.md),
[`graph_famous()`](https://heavywatal.github.io/rigraphlite/reference/graph_famous.md),
[`graph_full()`](https://heavywatal.github.io/rigraphlite/reference/graph_full.md),
[`graph_hypercube()`](https://heavywatal.github.io/rigraphlite/reference/graph_hypercube.md),
[`graph_kary_tree()`](https://heavywatal.github.io/rigraphlite/reference/graph_tree.md),
[`graph_lcf()`](https://heavywatal.github.io/rigraphlite/reference/graph_lcf.md),
[`graph_square_lattice()`](https://heavywatal.github.io/rigraphlite/reference/graph_lattice.md),
[`graph_star()`](https://heavywatal.github.io/rigraphlite/reference/graph_star.md)

## Examples

``` r
graph_create(seq_len(6L))
#> $V  tibble [6 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 3 × 2
#>    from    to
#>   <int> <int>
#> 1     1     2
#> 2     3     4
#> 3     5     6
```
