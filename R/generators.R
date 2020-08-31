#' Create graph from R objects
#'
#' @seealso [graph_create()]
#' @param x A vector, matrix, or data.frame.
#' @rdname as_igraph
#' @export
as_igraph = function(x) UseMethod("as_igraph")

#' @rdname as_igraph
#' @export
as_igraph.default = function(x) {
  graph_create(x)
}

#' @rdname as_igraph
#' @export
as_igraph.matrix = function(x) {
  if (is.numeric(x)) {
    graph_from_edgelist(x)
  } else {
    graph_from_symbolic_edgelist(x)
  }
}

#' @rdname as_igraph
#' @export
as_igraph.data.frame = function(x) {
  graph_from_data_frame(x) |> as_Rcpp_IGraph()
}

#' @param df data.frame that includes an edgelist and edge attributes.
#' @param edgelist Two-column matrix.
#' @param directed Boolean
#' @rdname as_igraph
#' @export
graph_from_data_frame = function(df, directed = TRUE) {
  .Call(`_igraphlite_graph_from_data_frame_`, df, directed) |> as_Rcpp_IGraph()
}

#' @rdname as_igraph
#' @export
graph_from_symbolic_edgelist = function(edgelist, directed = TRUE) {
  .Call(`_igraphlite_graph_from_symbolic_edgelist_`, edgelist, directed) |> as_Rcpp_IGraph()
}

#' @rdname as_igraph
#' @export
graph_from_edgelist = function(edgelist, directed = TRUE) {
  .Call(`_igraphlite_graph_from_edgelist_`, edgelist, directed) |> as_Rcpp_IGraph()
}

#' Deterministic Graph Generators
#'
#' @param edges The edges to add, the first two elements are the first edge, etc.
#' @param n Integer, the number of vertices in the graph.
#' @param directed Boolean
#' @param mutual Boolean
#' @param circular Boolean
#' @param mode Integer;
#'   - `igraph_star_mode_t` \{0: OUT, 1: IN, 2: MUTUAL, 3: UNDIRECTED\}
#'   - `igraph_tree_mode_t` \{0: OUT, 1: IN, 2: UNDIRECTED\}
#' @seealso [as_igraph()], [graph_from_data_frame()]
#' @source <https://igraph.org/c/doc/igraph-Generators.html>
#' @rdname generators
#' @export
graph_create = function(edges, n = 0L, directed = TRUE) {
  .Call(`_igraphlite_graph_create_`, edges, n, directed) |> as_Rcpp_IGraph()
}

#' @param center Id of the vertex which will be the center of the graph.
#' @rdname generators
#' @export
graph_star = function(n, mode = 0L, center = 1L) {
  .Call(`_igraphlite_graph_star_`, n, mode, center) |> as_Rcpp_IGraph()
}

#' @param dim Vector giving the sizes of the lattice in each of its dimensions.
#' @param nei Integer distance within which two vertices will be connected.
#' @rdname generators
#' @export
graph_lattice = function(dim, nei = 1L, directed = FALSE, mutual = FALSE, circular = FALSE) {
  .Call(`_igraphlite_graph_lattice_`, dim, nei, directed, mutual, circular) |> as_Rcpp_IGraph()
}

#' @rdname generators
#' @export
graph_ring = function(n, directed = FALSE, mutual = FALSE, circular = TRUE) {
  .Call(`_igraphlite_graph_ring_`, n, directed, mutual, circular) |> as_Rcpp_IGraph()
}

#' @param children Integer, the number of children of a vertex in the tree.
#' @rdname generators
#' @export
graph_tree = function(n, children = 2L, mode = 0L) {
  .Call(`_igraphlite_graph_tree_`, n, children, mode) |> as_Rcpp_IGraph()
}

#' @rdname generators
#' @export
graph_full = function(n, directed = FALSE, mutual = FALSE) {
  .Call(`_igraphlite_graph_full_`, n, directed, mutual) |> as_Rcpp_IGraph()
}

#' @param name \{Bull, Chvatal, Coxeter, Cubical, Diamond, Dodecahedral,
#'   Dodecahedron, Folkman, Franklin, Frucht, Grotzsch, Heawood, Herschel, House,
#'   HouseX, Icosahedral, Icosahedron, Krackhardt_Kite, Levi, McGee, Meredith,
#'   Noperfectmatching, Nonline, Octahedral, Octahedron, Petersen, Robertson,
#'   Smallestcyclicgroup, Tetrahedral, Tetrahedron, Thomassen, Tutte,
#'   Uniquely3colorable, Walther, Zachary\}
#' @rdname generators
#' @export
graph_famous = function(name) {
  .Call(`_igraphlite_graph_famous_`, name) |> as_Rcpp_IGraph()
}

as_Rcpp_IGraph = function(g) {
  class(g) = c("Rcpp_IGraph", "externalptr")
  g
}
