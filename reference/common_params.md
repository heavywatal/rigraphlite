# Common parameters used throughout the package

This function does nothing. It is designed to be used with
@inheritParams.

## Usage

``` r
common_params(
  graph,
  vids,
  vid,
  from,
  to,
  eids,
  eid,
  edges,
  mode,
  weights,
  directed,
  loops,
  multiple,
  normalized
)
```

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- vids:

  An integer vector of vertex IDs.

- vid:

  An integer value of vertex ID.

- from:

  An integer vector of vertex IDs.

- to:

  An integer vector of vertex IDs.

- eids:

  An integer vector of edge IDs.

- eid:

  An integer value of edge ID.

- edges:

  An integer vector of vertex IDs; the first two elements are the first
  edge, etc.

- mode:

  An integer value of edge type to count; {1: OUT, 2: IN, 3: ALL}.

- weights:

  A numeric vector of edge weights; `TRUE` to use
  `Eattr(graph, "weight")`.

- directed:

  A logical value, whether to consider directed paths. Ignored for
  undirected graphs.

- loops:

  An integer value, how to treat loop edges; {0: NO_LOOPS, 1:
  LOOPS/LOOPS_TWICE, 2: LOOPS_ONCE}

- multiple:

  A logical value, whether to keep multiple (parallel) edges.

- normalized:

  A logical value, whether to normalize the result.
