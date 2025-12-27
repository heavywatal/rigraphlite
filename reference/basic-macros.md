# Miscellaneous macros

igraphlite uses 32-bit igraph, which limits the maximum number of
vertices to `2 ** 31 - 2`.

## Usage

``` r
IGRAPH_VCOUNT_MAX

IGRAPH_ECOUNT_MAX

IGRAPH_UNLIMITED

expand_path_to_pairs(vids)

is_same_graph(graph1, graph2)
```

## Format

An object of class `integer` of length 1.

## Source

<https://igraph.org/c/doc/igraph-Basic.html#misc-helper-functions>

## Arguments

- vids:

  An integer vector of vertex IDs.

- graph1, graph2:

  Two
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  objects to compare.

## Value

`is_same_graph()` returns a logical value. It verifies that the two
graphs have the same directedness, the same number of vertices, and that
they contain precisely the same edges (regardless of their ordering)
when written in terms of vertex indices. Graph attributes are not taken
into account.

## See also

[`isomorphic()`](https://heavywatal.github.io/rigraphlite/reference/isomorphic.md)
and
[`subisomorphic()`](https://heavywatal.github.io/rigraphlite/reference/isomorphic.md).

## Examples

``` r
IGRAPH_VCOUNT_MAX
#> [1] 2147483646

IGRAPH_ECOUNT_MAX
#> [1] 1073741823

IGRAPH_UNLIMITED
#> [1] -1

expand_path_to_pairs(seq_len(4L))
#> [1] 1 2 2 3 3 4

g1 = graph_create(c(1L, 2L, 1L, 3L), directed = FALSE)
g2 = graph_create(c(3L, 2L, 3L, 1L), directed = FALSE)
g3 = graph_create(c(3L, 1L, 3L, 2L), directed = FALSE)
isomorphic(g1, g2)
#> [1] TRUE

is_same_graph(g1, g2)
#> [1] FALSE

is_same_graph(g2, g3)
#> [1] TRUE
```
