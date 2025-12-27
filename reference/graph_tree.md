# Create a tree graph

A k-ary tree is a tree where each vertex has up to *k* children. The
symmetry of the graph depends on `n`.

## Usage

``` r
graph_kary_tree(n, children = 2L, mode = 0L)

# graph_tree = graph_kary_tree
```

## Arguments

- n:

  An integer value, the number of vertices.

- children:

  Integer, the number of children of a vertex in the tree.

- mode:

  An integer value, `igraph_tree_mode_t` {0: OUT, 1: IN, 2: UNDIRECTED}

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
[`graph_lcf()`](https://heavywatal.github.io/rigraphlite/reference/graph_lcf.md),
[`graph_square_lattice()`](https://heavywatal.github.io/rigraphlite/reference/graph_lattice.md),
[`graph_star()`](https://heavywatal.github.io/rigraphlite/reference/graph_star.md)

## Examples

``` r
graph_kary_tree(5L)
#> $V  tibble [5 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 4 × 2
#>    from    to
#>   <int> <int>
#> 1     1     2
#> 2     1     3
#> 3     2     4
#> 4     2     5
```
