# Read graphs from files

Currently attributes are not supported.

## Usage

``` r
read_graph(
  file,
  format = c("edgelist", "ncol", "lgl", "graphml", "gml", "pajek", "dl"),
  ...
)

read_graph_edgelist(file, directed = FALSE)

read_graph_ncol(file, names = FALSE, directed = FALSE)

read_graph_lgl(file, names = FALSE, directed = FALSE)

read_graph_graphml(file, index = 0L)

read_graph_gml(file)

read_graph_pajek(file)

read_graph_dl(file, directed = FALSE)
```

## Source

<https://igraph.org/c/doc/igraph-Foreign.html>

## Arguments

- file:

  A string specifying the file path.

- format:

  Estimated from the file extension if not provided.

- ...:

  Additional arguments passed to specific reading functions.

- directed:

  A logical value, whether to consider directed paths. Ignored for
  undirected graphs.

- names:

  A logical value indicating whether to read vertex names.

- index:

  An integer specifying which graph to read (starting from 0).

## Value

A
[`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object.

## See also

[`write_graph()`](https://heavywatal.github.io/rigraphlite/reference/write.md).
