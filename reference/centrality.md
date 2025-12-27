# Centrality measures

The betweenness centrality of a vertex or an edge is the number of
geodesics going through it.

## Usage

``` r
closeness(
  graph,
  vids = integer(0),
  mode = 1L,
  weights = numeric(0),
  normalized = TRUE
)

harmonic_centrality(
  graph,
  vids = integer(0),
  mode = 1L,
  weights = numeric(0),
  normalized = TRUE
)

betweenness(
  graph,
  ...,
  weights = numeric(0),
  from = integer(0),
  to = integer(0),
  vids = integer(0),
  directed = is_directed(graph),
  normalized = FALSE,
  cutoff = -1
)

edge_betweenness(
  graph,
  ...,
  weights = numeric(0),
  from = integer(0),
  to = integer(0),
  eids = integer(0),
  directed = is_directed(graph),
  normalized = FALSE,
  cutoff = -1
)

edge_betweenness_subset(
  graph,
  ...,
  weights = numeric(0),
  from = integer(0),
  to = integer(0),
  eids = integer(0),
  directed = is_directed(graph),
  normalized = FALSE
)

pagerank(
  graph,
  weights = numeric(0),
  reset = numeric(0),
  damping = 0.85,
  directed = is_directed(graph),
  vids = integer(0)
)

constraint(graph, vids = integer(0), weights = numeric(0))

maxdegree(graph, vids = integer(0), mode = 1L, loops = 1L)

strength(graph, vids = integer(0), mode = 1L, loops = 1L, weights = numeric(0))

eigenvector_centrality(graph, mode = 1L, weights = numeric(0))

hub_and_authority_scores(graph, weights = numeric(0))

convergence_degree(graph)
```

## Source

<https://igraph.org/c/doc/igraph-Structural.html#centrality-measures>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- vids:

  An integer vector of vertex IDs.

- mode:

  An integer value of edge type to count; {1: OUT, 2: IN, 3: ALL}.

- weights:

  A numeric vector of edge weights; `TRUE` to use
  `Eattr(graph, "weight")`.

- normalized:

  A logical value, whether to normalize the result.

- ...:

  Unused, but temporarily included to avoid silent bugs and to prompt
  users to cope with breaking changes in version 1.0.

- from:

  An integer vector of vertex IDs.

- to:

  An integer vector of vertex IDs.

- directed:

  A logical value, whether to consider directed paths. Ignored for
  undirected graphs.

- cutoff:

  Maximum length of paths to be considered. Unlimited if negative.

- eids:

  An integer vector of edge IDs.

- reset:

  A numeric vector of probabilities for each vertex to be a reset point.
  If empty, uniform probabilities are assumed.

- damping:

  A numeric value between 0 and 1, the damping factor. Walking restarts
  from a random vertex with probability 1 - `damping`.

- loops:

  An integer value, how to treat loop edges; {0: NO_LOOPS, 1:
  LOOPS/LOOPS_TWICE, 2: LOOPS_ONCE}

## Value

`closeness()` returns the inverse of the mean distance to all other
vertices.

`harmonic_centrality()` returns the mean inverse distance to all other
vertices.

`betweenness()` returns a numeric vector of betweenness for each vertex
in the graph.

`edge_betweenness()` returns a numeric vector of edge betweenness for
each edge in the graph.

`edge_betweenness_subset()` is a variant of `edge_betweenness()` that
computes the betweenness using a subset of paths between `from` and
`to`.

`pagerank()` returns a numeric vector of PageRank scores for each
vertex.

`constraint()` returns a numeric vector of Burt's constraint scores.

`maxdegree()` is equivalent to `max(degree(graph))`.

`strength()` of a vertex is the sum of the weights of its incident
edges.

`eigenvector_centrality()` of each vertex is proportional to the sum of
eigenvector centralities of its neighbors.

`hub_and_authority_scores()` are a generalization of the ideas behind
eigenvector centrality to directed graphs.

`convergence_degree()` returns the normalized value of the difference
between the size of the input set and the output set.

## Examples

``` r
g = graph_tree(5L)
closeness(g, mode = 3L)
#> [1] 0.6666667 0.8000000 0.4444444 0.5000000 0.5000000
closeness(g, mode = 3L, normalized = FALSE)
#> [1] 0.1666667 0.2000000 0.1111111 0.1250000 0.1250000

harmonic_centrality(g, mode = 3L)
#> [1] 0.7500000 0.8750000 0.5416667 0.5833333 0.5833333
harmonic_centrality(g, mode = 3L, normalized = FALSE)
#> [1] 3.000000 3.500000 2.166667 2.333333 2.333333

betweenness(g)
#> [1] 0 2 0 0 0

edge_betweenness(g)
#> [1] 3 1 2 2
edge_betweenness(g, from = Vsource(g), to = Vsink(g))
#> [1] 2 1 1 1
edge_betweenness(g, normalized = TRUE)
#> [1] 0.15 0.05 0.10 0.10
edge_betweenness(g, cutoff = 1)
#> [1] 1 1 1 1

pagerank(g)
#> [1] 0.1416180 0.2018056 0.2018056 0.2273854 0.2273854

constraint(g)
#> [1] 0.5000000 0.3333333 1.0000000 1.0000000 1.0000000

maxdegree(g, mode = 3L)
#> [1] 3

strength(g, mode = 3L)
#> [1] 2 3 1 1 1

eigenvector_centrality(g, mode = 3L)
#> [1] 0.7653669 1.0000000 0.4142136 0.5411961 0.5411961

convergence_degree(g)
#> [1] -0.5000000  0.0000000  0.3333333  0.3333333

hub_and_authority_scores(g)
#>   hub authority
#> 1   0         0
#> 2   1         0
#> 3   0         0
#> 4   0         1
#> 5   0         1
```
