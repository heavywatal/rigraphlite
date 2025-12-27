# Distance-related Functions

`average_path_length()` and `path_length_hist()` can be computed with
the result of `distances()`, but should be faster as they are written in
C.

## Usage

``` r
distances(
  graph,
  ...,
  weights = numeric(0L),
  from = integer(0L),
  to = from,
  mode = 3L,
  cutoff = -1
)

average_path_length(
  graph,
  ...,
  weights = numeric(0L),
  directed = is_directed(graph),
  unconn = TRUE
)

path_length_hist(graph, directed = is_directed(graph))

eccentricity(graph, weights = numeric(0L), vids = integer(0L), mode = 3L)

diameter(
  graph,
  weights = numeric(0L),
  directed = is_directed(graph),
  unconn = TRUE
)

girth(graph)

radius(graph, weights = numeric(0L), mode = 3L)
```

## Source

<https://igraph.org/c/doc/igraph-Structural.html#shortest-path-related-functions>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- ...:

  Unused, but temporarily included to avoid silent bugs and to prompt
  users to cope with breaking changes in version 1.0.

- weights:

  A numeric vector of edge weights; `TRUE` to use
  `Eattr(graph, "weight")`.

- from:

  An integer vector of vertex IDs.

- to:

  An integer vector of vertex IDs.

- mode:

  An integer value of edge type to count; {1: OUT, 2: IN, 3: ALL}.

- cutoff:

  Maximum length of paths to be considered. Unlimited if negative.

- directed:

  A logical value, whether to consider directed paths. Ignored for
  undirected graphs.

- unconn:

  A logical value.

- vids:

  An integer vector of vertex IDs.

## Value

`distances()` returns a matrix of distances between the vertices.

`average_path_length()` returns a numeric value.

`path_length_hist()` returns an integer vector.

## Examples

``` r
g = graph_tree(5L)
distances(g, mode = 1L)
#>      [,1] [,2] [,3] [,4] [,5]
#> [1,]    0    1    1    2    2
#> [2,]  Inf    0  Inf    1    1
#> [3,]  Inf  Inf    0  Inf  Inf
#> [4,]  Inf  Inf  Inf    0  Inf
#> [5,]  Inf  Inf  Inf  Inf    0
average_path_length(g)
#> [1] 1.333333
path_length_hist(g)
#> [1] 4 2
diameter(g)
#> [1] 2
girth(g)
#> [1] Inf
radius(g)
#> [1] 2
eccentricity(g)
#> [1] 2 2 3 3 3
```
