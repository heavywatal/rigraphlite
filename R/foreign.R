#' Read graphs from files
#'
#' Currently attributes are not supported.
#' @inheritParams common_params
#' @param file A string specifying the file path.
#' @param format Estimated from the file extension if not provided.
#' @param ... Additional arguments passed to specific reading functions.
#' @returns A [`igraph_ptr`] object.
#' @seealso [write_graph()].
#' @source <https://igraph.org/c/doc/igraph-Foreign.html>
#' @rdname read
#' @export
#'
read_graph = function(
  file,
  format = c("edgelist", "ncol", "lgl", "graphml", "gml", "pajek", "dl"), ...
) {
  format = if (missing(format)) {
    tools::file_ext(file)
  } else {
    match.arg(format)
  }
  switch(format,
    edgelist = read_graph_edgelist(file, ...),
    ncol = read_graph_ncol(file, ...),
    lgl = read_graph_lgl(file, ...),
    graphml = read_graph_graphml(file, ...),
    gml = read_graph_gml(file, ...),
    pajek = read_graph_pajek(file, ...),
    net = read_graph_pajek(file, ...),
    dl = read_graph_dl(file, ...),
    stop("Unsupported file format: ", format, call. = FALSE)
  )
}

#' @rdname read
#' @export
read_graph_edgelist = function(file, directed = FALSE) {
  .Call(`_igraphlite_read_graph_edgelist_`, file, directed) |> set_ptr_class()
}

#' @param names A logical value indicating whether to read vertex names.
#' @rdname read
#' @export
read_graph_ncol = function(file, names = FALSE, directed = FALSE) {
  .Call(`_igraphlite_read_graph_ncol_`, file, names, directed) |> set_ptr_class()
}

#' @rdname read
#' @export
read_graph_lgl = function(file, names = FALSE, directed = FALSE) {
  .Call(`_igraphlite_read_graph_lgl_`, file, names, directed) |> set_ptr_class()
}

#' @param index An integer specifying which graph to read (starting from 0).
#' @rdname read
#' @export
read_graph_graphml = function(file, index = 0L) {
  .Call(`_igraphlite_read_graph_graphml_`, file, index) |> set_ptr_class()
}

#' @rdname read
#' @export
read_graph_gml = function(file) {
  .Call(`_igraphlite_read_graph_gml_`, file) |> set_ptr_class()
}

#' @rdname read
#' @export
read_graph_pajek = function(file) {
  .Call(`_igraphlite_read_graph_pajek_`, file) |> set_ptr_class()
}

#' @rdname read
#' @export
read_graph_dl = function(file, directed = FALSE) {
  .Call(`_igraphlite_read_graph_dl_`, file, directed) |> set_ptr_class()
}

#' Write graphs to files
#'
#' Currently attributes are not supported.
#' @inheritParams common_params
#' @param file A string specifying the file path.
#' @param format Estimated from the file extension if not provided.
#' @param ... Additional arguments passed to specific writing functions.
#' @returns The input graph is returned invisibly.
#' @seealso [read_graph()].
#' @source <https://igraph.org/c/doc/igraph-Foreign.html>
#' @rdname write
#' @export
write_graph = function(
  graph,
  file,
  format = c("edgelist", "ncol", "lgl", "graphml", "gml", "pajek", "dot", "leda"), ...
) {
  format = if (missing(format)) {
    tools::file_ext(file)
  } else {
    match.arg(format)
  }
  switch(format,
    edgelist = write_graph_edgelist(graph, file, ...),
    ncol = write_graph_ncol(graph, file, ...),
    lgl = write_graph_lgl(graph, file, ...),
    graphml = write_graph_graphml(graph, file, ...),
    gml = write_graph_gml(graph, file, ...),
    pajek = write_graph_pajek(graph, file, ...),
    net = write_graph_pajek(graph, file, ...),
    dot = write_graph_dot(graph, file, ...),
    leda = write_graph_leda(graph, file, ...),
    stop("Unsupported file format: ", format, call. = FALSE)
  )
}

#' @rdname write
#' @export
write_graph_edgelist = function(graph, file) {
  invisible(.Call(`_igraphlite_write_graph_edgelist_`, graph, file))
}

#' @rdname write
#' @export
write_graph_ncol = function(graph, file) {
  invisible(.Call(`_igraphlite_write_graph_ncol_`, graph, file))
}

#' @param isolates A logical value indicating whether to include isolated vertices.
#' @rdname write
#' @export
write_graph_lgl = function(graph, file, isolates = TRUE) {
  invisible(.Call(`_igraphlite_write_graph_lgl_`, graph, file, isolates))
}

#' @param prefixattr A logical value indicating whether to fix non-unique attribute names.
#' @rdname write
#' @export
write_graph_graphml = function(graph, file, prefixattr = FALSE) {
  invisible(.Call(`_igraphlite_write_graph_graphml_`, graph, file, prefixattr))
}

#' @param creator A string specifying the creator of the GML file.
#' @rdname write
#' @export
write_graph_gml = function(graph, file, creator = "igraphlite") {
  invisible(.Call(`_igraphlite_write_graph_gml_`, graph, file, creator))
}

#' @rdname write
#' @export
write_graph_pajek = function(graph, file) {
  invisible(.Call(`_igraphlite_write_graph_pajek_`, graph, file))
}

#' @rdname write
#' @export
write_graph_dot = function(graph, file) {
  invisible(.Call(`_igraphlite_write_graph_dot_`, graph, file))
}

#' @rdname write
#' @export
write_graph_leda = function(graph, file) {
  invisible(.Call(`_igraphlite_write_graph_leda_`, graph, file))
}
