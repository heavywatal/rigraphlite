# Quick access to edge list columns

If only one of the two columns in the edge list is needed, these
functions provide a more efficient way to access them.

## Usage

``` r
igraph_from(graph)

igraph_to(graph)
```

## Source

<https://github.com/igraph/igraph/blob/master/include/igraph_datatype.h>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

## Value

`igraph_from()` returns the head vertices of all the edges.

`igraph_to()` returns the tail vertices of all the edges.

## See also

[`as.matrix.igraph_ptr()`](https://heavywatal.github.io/rigraphlite/reference/conversion.md)
and
[`as.data.frame.igraph_ptr()`](https://heavywatal.github.io/rigraphlite/reference/conversion.md)
to get entire edge lists.

## Examples

``` r
g = graph_create(seq_len(6L))
igraph_from(g)
#> [1] 1 3 5
igraph_to(g)
#> [1] 2 4 6
```
