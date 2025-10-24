#' Create a graph with the specified edges
#'
#' @inheritParams common_params
#' @param n An integer value, the number of vertices.
#' @returns An [`igraph_ptr`] object.
#' @seealso [as_igraph()], [graph_from_data_frame()]
#' @family deterministic generators
#' @export
#' @examples
#' graph_create(seq_len(6L))
graph_create = function(edges, n = 0L, directed = TRUE) {
  if (is.integer(edges)) {
    g = .Call(`_igraphlite_graph_create_`, edges, n, directed)
  } else {
    g = .Call(`_igraphlite_graph_from_symbolic_edges_`, edges, directed)
    add_vertices(g, n - length(edges))
  }
  set_ptr_class(g)
}


#' Create a star graph
#'
#' In a star graph, every vertex connects only to the center.
#' @inheritParams graph_create
#' @param mode An integer value, \{0: OUT, 1: IN, 2: UNDIRECTED, 3: MUTUAL\}
#' @param center Id of the vertex which will be the center of the graph.
#' @returns An [`igraph_ptr`] object.
#' @family deterministic generators
#' @export
#' @examples
#' graph_star(4L, 0L)
#' graph_star(4L, 1L)
#' graph_star(4L, 2L)
#' graph_star(4L, 3L)
graph_star = function(n, mode = 0L, center = 1L) {
  .Call(`_igraphlite_graph_star_`, n, mode, center - 1L) |> set_ptr_class()
}

#' Create an n-dimensional hypercube graph
#'
#' The hypercube graph `Q_n` has `2^n` vertices and `2^(n-1) n` edges.
#' @source <https://igraph.org/c/doc/igraph-Generators.html#igraph_hypercube>
#' @param n The dimension of the hypercube graph.
#' @returns An [`igraph_ptr`] object.
#' @family deterministic generators
#' @examples
#' graph_hypercube(3L)
#' @inheritParams graph_create
#' @export
graph_hypercube = function(n, directed = FALSE) {
  .Call(`_igraphlite_graph_hypercube_`, n, directed) |> set_ptr_class()
}

#' Create arbitrary dimensional lattices
#'
#' A ring/cycle graph is a special case of a lattice graph with one dimension.
#' @inheritParams graph_create
#' @param dim An integer vector giving the sizes of the lattice in each of its dimensions.
#' @param nei An integer distance within which two vertices will be connected.
#' @param mutual A logical, whether to create mutual edges in directed graphs.
#' @param circular A logical, whether to create a closed ring/cycle or an open path.
#' @returns An [`igraph_ptr`] object.
#' @family deterministic generators
#' @examples
#' graph_square_lattice(c(2L, 3L))
#'
#' graph_triangular_lattice(c(2L, 3L))
#'
#' graph_hexagonal_lattice(c(2L, 3L))
#'
#' graph_ring(4L)
#'
#' graph_path(4L)
#' @rdname graph_lattice
#' @export
graph_square_lattice = function(dim, nei = 1L, directed = FALSE, mutual = FALSE, circular = FALSE) {
  .Call(`_igraphlite_graph_square_lattice_`, dim, nei, directed, mutual, circular) |> set_ptr_class()
}

#' @param dims An integer vector defining the shape of the lattice.
#' @rdname graph_lattice
#' @export
graph_triangular_lattice = function(dims, directed = FALSE, mutual = FALSE) {
  .Call(`_igraphlite_graph_triangular_lattice_`, dims, directed, mutual) |> set_ptr_class()
}

#' @rdname graph_lattice
#' @export
graph_hexagonal_lattice = function(dims, directed = FALSE, mutual = FALSE) {
  .Call(`_igraphlite_graph_hexagonal_lattice_`, dims, directed, mutual) |> set_ptr_class()
}

#' @rdname graph_lattice
#' @export
graph_ring = function(n, directed = FALSE, mutual = FALSE, circular = TRUE) {
  .Call(`_igraphlite_graph_ring_`, n, directed, mutual, circular) |> set_ptr_class()
}

#' @rdname graph_lattice
#' @export
graph_path = function(n, directed = FALSE, mutual = FALSE) {
  .Call(`_igraphlite_graph_ring_`, n, directed, mutual, FALSE) |> set_ptr_class()
}

#' @rdname graph_lattice
#' @export
#' @usage # graph_cycle = graph_ring
graph_cycle = graph_ring

#' @rdname graph_lattice
#' @export
#' @usage # graph_lattice = graph_square_lattice
graph_lattice = graph_square_lattice

#' Creates a graph from LCF notation
#'
#' @description
#' LCF notation (named after Lederberg, Coxeter, and Frucht) is a concise notation
#' for 3-regular Hamiltonian graphs.
#'
#' `graph_circulant(n, shifts)` is roughly equivalent to `graph_lcf(n, c(1L, shifts), n)`.
#' @source <https://igraph.org/c/html/latest/igraph-Generators.html#igraph_lcf>
#' @inheritParams graph_create
#' @param shifts An integer vector giving the shifts.
#' For `graph_lcf()`, it gives additional edges to a cycle backbone,
#' while for `graph_circulant()`, it gives all the edges.
#' @param repeats The number of repeats for the shifts.
#' @returns An [`igraph_ptr`] object.
#' @family deterministic generators
#' @examples
#' graph_lcf(5L, 2L, 5L)
#'
#' graph_circulant(5L, 2L, directed = TRUE)
#' @rdname graph_lcf
#' @export
graph_lcf = function(n, shifts, repeats = n) {
  .Call(`_igraphlite_graph_lcf_`, n, shifts, repeats) |> set_ptr_class()
}

#' @rdname graph_lcf
#' @export
graph_circulant = function(n, shifts, directed = FALSE) {
  .Call(`_igraphlite_graph_circulant_`, n, shifts, directed) |> set_ptr_class()
}

#' Create a tree graph
#'
#' A k-ary tree is a tree where each vertex has up to *k* children.
#' The symmetry of the graph depends on `n`.
#' @inheritParams graph_create
#' @param mode An integer value,
#' `igraph_tree_mode_t` \{0: OUT, 1: IN, 2: UNDIRECTED\}
#' @param children Integer, the number of children of a vertex in the tree.
#' @returns An [`igraph_ptr`] object.
#' @rdname graph_tree
#' @family deterministic generators
#' @export
#' @examples
#' graph_kary_tree(5L)
graph_kary_tree = function(n, children = 2L, mode = 0L) {
  .Call(`_igraphlite_graph_kary_tree_`, n, children, mode) |> set_ptr_class()
}

#' @rdname graph_tree
#' @export
#' @usage # graph_tree = graph_kary_tree
graph_tree = graph_kary_tree


#' Create a full graph (complete graph)
#'
#' In a full graph, every vertex is connected to every other vertex.
#' @inheritParams graph_create
#' @param self_loops A logical value, whether to include self-loops.
#' @returns An [`igraph_ptr`] object.
#' @family deterministic generators
#' @export
#' @examples
#' graph_full(4L)
#' graph_full(4L, directed = TRUE)
graph_full = function(n, directed = FALSE, self_loops = FALSE) {
  .Call(`_igraphlite_graph_full_`, n, directed, self_loops) |> set_ptr_class()
}


#' Create a famous graph by simply providing its name
#'
#' See the C library documentation for the list of available graphs.
#' @source <https://igraph.org/c/doc/igraph-Generators.html#igraph_famous>
#' @param name A character string, the name of the graph.
#' @returns An [`igraph_ptr`] object.
#' @family deterministic generators
#' @export
#' @examples
#' graph_famous("Diamond")
graph_famous = function(name) {
  .Call(`_igraphlite_graph_famous_`, name) |> set_ptr_class()
}

set_ptr_class = function(g) {
  class(g) = c("igraph_ptr", "externalptr")
  g
}
