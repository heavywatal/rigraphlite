# Creates a graph from LCF notation

LCF notation (named after Lederberg, Coxeter, and Frucht) is a concise
notation for 3-regular Hamiltonian graphs.

`graph_circulant(n, shifts)` is roughly equivalent to
`graph_lcf(n, c(1L, shifts), n)`.

## Usage

``` r
graph_lcf(n, shifts, repeats = n)

graph_circulant(n, shifts, directed = FALSE)
```

## Source

<https://igraph.org/c/html/latest/igraph-Generators.html#igraph_lcf>

## Arguments

- n:

  An integer value, the number of vertices.

- shifts:

  An integer vector giving the shifts. For `graph_lcf()`, it gives
  additional edges to a cycle backbone, while for `graph_circulant()`,
  it gives all the edges.

- repeats:

  The number of repeats for the shifts.

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
[`graph_hypercube()`](https://heavywatal.github.io/rigraphlite/reference/graph_hypercube.md),
[`graph_kary_tree()`](https://heavywatal.github.io/rigraphlite/reference/graph_tree.md),
[`graph_square_lattice()`](https://heavywatal.github.io/rigraphlite/reference/graph_lattice.md),
[`graph_star()`](https://heavywatal.github.io/rigraphlite/reference/graph_star.md)

## Examples

``` r
graph_lcf(5L, 2L, 5L)
#> $V  tibble [5 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 10 × 2
#>     from    to
#>    <int> <int>
#>  1     2     1
#>  2     3     1
#>  3     4     1
#>  4     5     1
#>  5     3     2
#>  6     4     2
#>  7     5     2
#>  8     4     3
#>  9     5     3
#> 10     5     4

graph_circulant(5L, 2L, directed = TRUE)
#> $V  tibble [5 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 5 × 2
#>    from    to
#>   <int> <int>
#> 1     1     3
#> 2     2     4
#> 3     3     5
#> 4     4     1
#> 5     5     2
```
