# Create a star graph

In a star graph, every vertex connects only to the center.

## Usage

``` r
graph_star(n, mode = 0L, center = 1L)
```

## Arguments

- n:

  An integer value, the number of vertices.

- mode:

  An integer value, {0: OUT, 1: IN, 2: UNDIRECTED, 3: MUTUAL}

- center:

  Id of the vertex which will be the center of the graph.

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
[`graph_square_lattice()`](https://heavywatal.github.io/rigraphlite/reference/graph_lattice.md)

## Examples

``` r
graph_star(4L, 0L)
#> $V  tibble [4 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 3 × 2
#>    from    to
#>   <int> <int>
#> 1     1     2
#> 2     1     3
#> 3     1     4
graph_star(4L, 1L)
#> $V  tibble [4 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 3 × 2
#>    from    to
#>   <int> <int>
#> 1     2     1
#> 2     3     1
#> 3     4     1
graph_star(4L, 2L)
#> $V  tibble [4 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 3 × 2
#>    from    to
#>   <int> <int>
#> 1     2     1
#> 2     3     1
#> 3     4     1
graph_star(4L, 3L)
#> $V  tibble [4 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 6 × 2
#>    from    to
#>   <int> <int>
#> 1     1     2
#> 2     2     1
#> 3     1     3
#> 4     3     1
#> 5     1     4
#> 6     4     1
```
