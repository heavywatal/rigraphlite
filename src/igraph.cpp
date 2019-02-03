// [[Rcpp::plugins(cpp14)]]
#include "igraphlite_types.h"

#include <Rcpp.h>

#include <igraph/igraph_interface.h>
#include <igraph/igraph_constructors.h>

RCPP_MODULE(igraph) {
  Rcpp::class_<igraph_t>("igraph_t");

  Rcpp::function("igraph_vcount", &igraph_vcount);
  Rcpp::function("igraph_ecount", &igraph_ecount);
}

// [[Rcpp::export]]
igraph_t make_empty_graph(int n, bool directed = true) {
  igraph_t g;
  igraph_empty(&g, n, directed);
  return g;
}

// [[Rcpp::export]]
igraph_t make_graph(const Rcpp::NumericVector& edges, int n = 0, bool directed = true) {
  igraph_t g;
  igraph_vector_t v;
  igraph_vector_view(&v, &(edges[0]), edges.size());
  igraph_create(&g, &v, n, directed);
  return g;
}

// [[Rcpp::export]]
igraph_t make_tree(int n, int children = 2, int mode = 0) {
  igraph_t g;
  igraph_tree(&g, n, children, static_cast<igraph_tree_mode_t>(mode));
  return g;
}
