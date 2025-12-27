# Acyclic graphs and feedback sets

A directed acyclic graph (DAG) is a directed graph with no directed
cycles. For directed graphs, only directed cycles are considered.

## Usage

``` r
is_dag(graph)

is_acyclic(graph)

topological_sorting(graph, mode = 1L)
```

## Source

<https://igraph.org/c/doc/igraph-Cycles.html#acyclic-graphs-feedback-sets>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- mode:

  An integer value of edge type to count; {1: OUT, 2: IN, 3: ALL}.

## Value

A logical value.

## See also

[`permutate_vertices()`](https://heavywatal.github.io/rigraphlite/reference/permutation.md)
to use the output of `topological_sorting()`.

## Examples

``` r
dag = graph_tree(5L)
tree = graph_tree(5L, mode = 2L)
ring = graph_ring(5L)

is_dag(dag)
#> [1] TRUE
is_dag(tree)
#> [1] FALSE
is_dag(ring)
#> [1] FALSE

is_acyclic(dag)
#> [1] TRUE
is_acyclic(tree)
#> [1] TRUE
is_acyclic(ring)
#> [1] FALSE

topological_sorting(dag)
#> [1] 1 2 3 4 5
```
