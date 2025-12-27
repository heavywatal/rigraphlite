# Graph constructors

`graph_empty()` creates an empty graph with a specified number of
vertices. An empty graph in *igraph* is a graph with no edges, which may
have vertices.

`graph_copy()` creates a deep copy of the graph. Normal assignment like
`g2 = g1` creates a shallow copy, which means that the internal data is
shared between the two R objects, and the modification on one of them
will affect the other.

## Usage

``` r
graph_empty(n = 0L, directed = TRUE)

graph_copy(graph)
```

## Arguments

- n:

  An integer, the number of vertices in the graph.

- directed:

  A logical value, whether to consider directed paths. Ignored for
  undirected graphs.

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

## Value

An
[`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object.

## See also

Other deterministic generators:
[`graph_create()`](https://heavywatal.github.io/rigraphlite/reference/graph_create.md),
[`graph_famous()`](https://heavywatal.github.io/rigraphlite/reference/graph_famous.md),
[`graph_full()`](https://heavywatal.github.io/rigraphlite/reference/graph_full.md),
[`graph_hypercube()`](https://heavywatal.github.io/rigraphlite/reference/graph_hypercube.md),
[`graph_kary_tree()`](https://heavywatal.github.io/rigraphlite/reference/graph_tree.md),
[`graph_lcf()`](https://heavywatal.github.io/rigraphlite/reference/graph_lcf.md),
[`graph_square_lattice()`](https://heavywatal.github.io/rigraphlite/reference/graph_lattice.md),
[`graph_star()`](https://heavywatal.github.io/rigraphlite/reference/graph_star.md)

## Examples

``` r
g = graph_empty(4L)
g
#> $V  tibble [4 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 0 × 2
#> # ℹ 2 variables: from <int>, to <int>

g_shallow = g
g_deep = graph_copy(g)
add_edges(g, seq_len(4L))

g_shallow
#> $V  tibble [4 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 2 × 2
#>    from    to
#>   <int> <int>
#> 1     1     2
#> 2     3     4

g_deep
#> $V  tibble [4 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 0 × 2
#> # ℹ 2 variables: from <int>, to <int>
```
