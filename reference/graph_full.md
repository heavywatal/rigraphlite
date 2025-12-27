# Create a full graph (complete graph)

In a full graph, every vertex is connected to every other vertex.

## Usage

``` r
graph_full(n, directed = FALSE, self_loops = FALSE)
```

## Arguments

- n:

  An integer value, the number of vertices.

- directed:

  A logical value, whether to consider directed paths. Ignored for
  undirected graphs.

- self_loops:

  A logical value, whether to include self-loops.

## Value

An
[`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object.

## See also

Other deterministic generators:
[`graph_create()`](https://heavywatal.github.io/rigraphlite/reference/graph_create.md),
[`graph_empty()`](https://heavywatal.github.io/rigraphlite/reference/constructors.md),
[`graph_famous()`](https://heavywatal.github.io/rigraphlite/reference/graph_famous.md),
[`graph_hypercube()`](https://heavywatal.github.io/rigraphlite/reference/graph_hypercube.md),
[`graph_kary_tree()`](https://heavywatal.github.io/rigraphlite/reference/graph_tree.md),
[`graph_lcf()`](https://heavywatal.github.io/rigraphlite/reference/graph_lcf.md),
[`graph_square_lattice()`](https://heavywatal.github.io/rigraphlite/reference/graph_lattice.md),
[`graph_star()`](https://heavywatal.github.io/rigraphlite/reference/graph_star.md)

## Examples

``` r
graph_full(4L)
#> $V  tibble [4 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 6 × 2
#>    from    to
#>   <int> <int>
#> 1     2     1
#> 2     3     1
#> 3     4     1
#> 4     3     2
#> 5     4     2
#> 6     4     3
graph_full(4L, directed = TRUE)
#> $V  tibble [4 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 12 × 2
#>     from    to
#>    <int> <int>
#>  1     1     2
#>  2     1     3
#>  3     1     4
#>  4     2     1
#>  5     2     3
#>  6     2     4
#>  7     3     1
#>  8     3     2
#>  9     3     4
#> 10     4     1
#> 11     4     2
#> 12     4     3
```
