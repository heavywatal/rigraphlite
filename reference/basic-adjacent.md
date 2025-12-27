# Basic query operations to get adjacency

Basic query operations to get adjacency

## Usage

``` r
edge(graph, eid)

edges(graph, eids = integer(0), bycol = FALSE)

get_eids(graph, edges, directed = is_directed(graph), error = TRUE)

get_all_eids_between(graph, from, to, directed = is_directed(graph))

neighbors(graph, vid, mode = 3L, loops = 1L, multiple = TRUE)

incident(graph, vid, mode = 3L, loops = 1L)

degree(graph, vids = integer(0), mode = 3L, loops = 1L)
```

## Source

<https://igraph.org/c/doc/igraph-Basic.html#basic-query-operations>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- eid:

  An integer value of edge ID.

- eids:

  An integer vector of edge IDs.

- bycol:

  A logical value to specify the result format. If `FALSE` (default),
  the result is an edge list compatible with
  [`add_edges()`](https://heavywatal.github.io/rigraphlite/reference/basic-add-delete.md).
  If `TRUE`, the result is suitable for making a 2-column matrix as
  returned by
  [`as.matrix.igraph_ptr()`](https://heavywatal.github.io/rigraphlite/reference/conversion.md).

- edges:

  An integer vector of vertex IDs; the first two elements are the first
  edge, etc.

- directed:

  A logical value, whether to consider directed paths. Ignored for
  undirected graphs.

- error:

  A logical value, whether to raise an error or assign `0` for
  non-existing edges.

- from:

  An integer vector of vertex IDs.

- to:

  An integer vector of vertex IDs.

- vid:

  An integer value of vertex ID.

- mode:

  An integer value of edge type to count; {1: OUT, 2: IN, 3: ALL}.

- loops:

  whether self-loop should be counted.

- multiple:

  A logical value, whether to keep multiple (parallel) edges.

- vids:

  An integer vector of vertex IDs.

## Value

`edge()` and `edges()` return the head and tail vertices of edges.

`get_eids()` returns the edge IDs of given vertex pairs.

`get_all_eids_between()` returns all edge IDs between two vertices.

`neighbors()` returns the adjacent vertices to a vertex.

`incident()` returns the incident edges of a vertex.

`degree()` returns the degrees of vertices in a graph.

## See also

[`as_adjlist()`](https://heavywatal.github.io/rigraphlite/reference/adjlist.md)
and
[`as_inclist()`](https://heavywatal.github.io/rigraphlite/reference/adjlist.md)
for the all-vertices version of `neighbors()` and `incident()`.

[`is_sink()`](https://heavywatal.github.io/rigraphlite/reference/sink.md),
[`is_source()`](https://heavywatal.github.io/rigraphlite/reference/sink.md),
[`Vsink()`](https://heavywatal.github.io/rigraphlite/reference/sink.md),
[`Vsource()`](https://heavywatal.github.io/rigraphlite/reference/sink.md)
for shortcuts to get zero-degree vertices.

## Examples

``` r
g = graph_tree(5L)
edge(g, 1L)
#> [1] 1 2

edges(g, c(1L, 3L))
#> [1] 1 2 2 4

get_eids(g, c(1L, 2L, 2L, 4L))
#> [1] 1 3

get_all_eids_between(g, 1L, 2L)
#> [1] 1

neighbors(g, 1L)
#> [1] 2 3

incident(g, 1L)
#> [1] 1 2

degree(g, mode = 1L)
#> [1] 2 2 0 0 0

degree(g, mode = 2L)
#> [1] 0 1 1 1 1

degree(g, mode = 3L)
#> [1] 2 3 1 1 1
```
