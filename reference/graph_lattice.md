# Create arbitrary dimensional lattices

A ring/cycle graph is a special case of a lattice graph with one
dimension.

## Usage

``` r
graph_square_lattice(
  dim,
  nei = 1L,
  directed = FALSE,
  mutual = FALSE,
  circular = FALSE
)

graph_triangular_lattice(dims, directed = FALSE, mutual = FALSE)

graph_hexagonal_lattice(dims, directed = FALSE, mutual = FALSE)

graph_ring(n, directed = FALSE, mutual = FALSE, circular = TRUE)

graph_path(n, directed = FALSE, mutual = FALSE)

# graph_cycle = graph_ring

# graph_lattice = graph_square_lattice
```

## Arguments

- dim:

  An integer vector giving the sizes of the lattice in each of its
  dimensions.

- nei:

  An integer distance within which two vertices will be connected.

- directed:

  A logical value, whether to consider directed paths. Ignored for
  undirected graphs.

- mutual:

  A logical, whether to create mutual edges in directed graphs.

- circular:

  A logical, whether to create a closed ring/cycle or an open path.

- dims:

  An integer vector defining the shape of the lattice.

- n:

  An integer value, the number of vertices.

## Value

An
[`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object.

## See also

Other deterministic generators:
[`graph_create()`](https://heavywatal.github.io/rigraphlite/reference/graph_create.md),
[`graph_empty()`](https://heavywatal.github.io/rigraphlite/reference/constructors.md),
[`graph_famous()`](https://heavywatal.github.io/rigraphlite/reference/graph_famous.md),
[`graph_full()`](https://heavywatal.github.io/rigraphlite/reference/graph_full.md),
[`graph_hypercube()`](https://heavywatal.github.io/rigraphlite/reference/graph_hypercube.md),
[`graph_kary_tree()`](https://heavywatal.github.io/rigraphlite/reference/graph_tree.md),
[`graph_lcf()`](https://heavywatal.github.io/rigraphlite/reference/graph_lcf.md),
[`graph_star()`](https://heavywatal.github.io/rigraphlite/reference/graph_star.md)

## Examples

``` r
graph_square_lattice(c(2L, 3L))
#> $V  tibble [6 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 7 × 2
#>    from    to
#>   <int> <int>
#> 1     2     1
#> 2     3     1
#> 3     4     2
#> 4     4     3
#> 5     5     3
#> 6     6     4
#> 7     6     5

graph_triangular_lattice(c(2L, 3L))
#> $V  tibble [6 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 9 × 2
#>    from    to
#>   <int> <int>
#> 1     2     1
#> 2     5     1
#> 3     4     1
#> 4     3     2
#> 5     6     2
#> 6     5     2
#> 7     6     3
#> 8     5     4
#> 9     6     5

graph_hexagonal_lattice(c(2L, 3L))
#> $V  tibble [22 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 27 × 2
#>     from    to
#>    <int> <int>
#>  1     2     1
#>  2     9     1
#>  3     3     2
#>  4     4     3
#>  5    11     3
#>  6     5     4
#>  7     6     5
#>  8    13     5
#>  9     7     6
#> 10    15     7
#> # ℹ 17 more rows

graph_ring(4L)
#> $V  tibble [4 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 4 × 2
#>    from    to
#>   <int> <int>
#> 1     2     1
#> 2     3     2
#> 3     4     3
#> 4     4     1

graph_path(4L)
#> $V  tibble [4 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 3 × 2
#>    from    to
#>   <int> <int>
#> 1     2     1
#> 2     3     2
#> 3     4     3
```
