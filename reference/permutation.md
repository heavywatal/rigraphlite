# Permute the vertices

Call `permutate_vertices()` with the output of `canonical_permutation()`
to create the canonical form of a graph. Note that the edge order may
differ even after canonicalization.

## Usage

``` r
canonical_permutation(graph, colors = integer(0L))

permutate_vertices(graph, permutation)
```

## Source

<https://igraph.org/c/html/latest/igraph-Isomorphism.html#igraph_permute_vertices>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- colors:

  An optional vertex color vector in integer.

- permutation:

  An integer vector, whose i-th element specifies the index of the
  vertex in the original graph that will become vertex i in the new
  graph.

## Value

`canonical_permutation()` returns an integer vector.

`permutate_vertices()` returns an
[`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object isomorphic to the input `graph`.

## See also

[`topological_sorting()`](https://heavywatal.github.io/rigraphlite/reference/cycles-acyclic.md).

## Examples

``` r
g1 = graph_create(c(1L, 2L, 1L, 3L), directed = FALSE)
g2 = graph_create(c(3L, 2L, 3L, 1L), directed = FALSE)
isomorphic(g1, g2)
#> [1] TRUE
is_same_graph(g1, g2)
#> [1] FALSE
# as.matrix(g1) and as.matrix(g2) may differ

g1can = permutate_vertices(g1, canonical_permutation(g1))
g2can = permutate_vertices(g2, canonical_permutation(g2))
is_same_graph(g1can, g2can)
#> [1] TRUE

isomorphic(g1, permutate_vertices(g1, c(3L, 2L, 1L)))
#> [1] TRUE
```
