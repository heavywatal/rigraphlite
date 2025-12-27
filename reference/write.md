# Write graphs to files

Currently attributes are not supported.

## Usage

``` r
write_graph(
  graph,
  file,
  format = c("edgelist", "ncol", "lgl", "graphml", "gml", "pajek", "dot", "leda"),
  ...
)

write_graph_edgelist(graph, file)

write_graph_ncol(graph, file)

write_graph_lgl(graph, file, isolates = TRUE)

write_graph_graphml(graph, file, prefixattr = FALSE)

write_graph_gml(graph, file, creator = "igraphlite")

write_graph_pajek(graph, file)

write_graph_dot(graph, file)

write_graph_leda(graph, file)
```

## Source

<https://igraph.org/c/doc/igraph-Foreign.html>

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- file:

  A string specifying the file path.

- format:

  Estimated from the file extension if not provided.

- ...:

  Additional arguments passed to specific writing functions.

- isolates:

  A logical value indicating whether to include isolated vertices.

- prefixattr:

  A logical value indicating whether to fix non-unique attribute names.

- creator:

  A string specifying the creator of the GML file.

## Value

The input graph is returned invisibly.

## See also

[`read_graph()`](https://heavywatal.github.io/rigraphlite/reference/read.md).
