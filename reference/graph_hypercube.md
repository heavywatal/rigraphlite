# Create an n-dimensional hypercube graph

The hypercube graph `Q_n` has `2^n` vertices and `2^(n-1) n` edges.

## Usage

``` r
graph_hypercube(n, directed = FALSE)
```

## Source

<https://igraph.org/c/doc/igraph-Generators.html#igraph_hypercube>

## Arguments

- n:

  The dimension of the hypercube graph.

- directed:

  A logical value, whether to consider directed paths. Ignored for
  undirected graphs.

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
[`graph_kary_tree()`](https://heavywatal.github.io/rigraphlite/reference/graph_tree.md),
[`graph_lcf()`](https://heavywatal.github.io/rigraphlite/reference/graph_lcf.md),
[`graph_square_lattice()`](https://heavywatal.github.io/rigraphlite/reference/graph_lattice.md),
[`graph_star()`](https://heavywatal.github.io/rigraphlite/reference/graph_star.md)

## Examples

``` r
graph_hypercube(3L)
#> $V  tibble [8 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 12 × 2
#>     from    to
#>    <int> <int>
#>  1     2     1
#>  2     3     1
#>  3     5     1
#>  4     4     2
#>  5     6     2
#>  6     4     3
#>  7     7     3
#>  8     8     4
#>  9     6     5
#> 10     7     5
#> 11     8     6
#> 12     8     7
```
