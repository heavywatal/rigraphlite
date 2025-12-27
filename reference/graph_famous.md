# Create a famous graph by simply providing its name

See the C library documentation for the list of available graphs.

## Usage

``` r
graph_famous(name)
```

## Source

<https://igraph.org/c/doc/igraph-Generators.html#igraph_famous>

## Arguments

- name:

  A character string, the name of the graph.

## Value

An
[`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object.

## See also

Other deterministic generators:
[`graph_create()`](https://heavywatal.github.io/rigraphlite/reference/graph_create.md),
[`graph_empty()`](https://heavywatal.github.io/rigraphlite/reference/constructors.md),
[`graph_full()`](https://heavywatal.github.io/rigraphlite/reference/graph_full.md),
[`graph_hypercube()`](https://heavywatal.github.io/rigraphlite/reference/graph_hypercube.md),
[`graph_kary_tree()`](https://heavywatal.github.io/rigraphlite/reference/graph_tree.md),
[`graph_lcf()`](https://heavywatal.github.io/rigraphlite/reference/graph_lcf.md),
[`graph_square_lattice()`](https://heavywatal.github.io/rigraphlite/reference/graph_lattice.md),
[`graph_star()`](https://heavywatal.github.io/rigraphlite/reference/graph_star.md)

## Examples

``` r
graph_famous("Diamond")
#> $V  tibble [4 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 5 × 2
#>    from    to
#>   <int> <int>
#> 1     2     1
#> 2     3     1
#> 3     3     2
#> 4     4     2
#> 5     4     3
```
