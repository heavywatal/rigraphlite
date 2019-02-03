// [[Rcpp::plugins(cpp14)]]
#include "igraphlite_types.h"

#include <Rcpp.h>

#include <igraph/igraph_interface.h>
#include <igraph/igraph_constructors.h>

RCPP_MODULE(igraph) {
  Rcpp::class_<igraph_t>("igraph_t");

  Rcpp::function("igraph_vcount", &igraph_vcount);
  Rcpp::function("igraph_ecount", &igraph_ecount);
  Rcpp::function("igraph_is_directed", &igraph_is_directed);
}

Rcpp::NumericVector from(const igraph_t& graph) {
  return Rcpp::NumericVector(graph.from.stor_begin, graph.from.stor_end);
}

Rcpp::NumericVector to(const igraph_t& graph) {
  return Rcpp::NumericVector(graph.to.stor_begin, graph.to.stor_end);
}

// [[Rcpp::export]]
Rcpp::NumericMatrix edgelist(const igraph_t& graph) {
  return Rcpp::cbind(from(graph), to(graph));
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

// [[Rcpp::export]]
Rcpp::NumericVector
degree(const igraph_t& graph, const Rcpp::NumericVector& vs, int mode = 3, bool loops = false) {
  igraph_vector_t ivs;
  igraph_vector_view(&ivs, &(vs[0]), vs.size());
  igraph_vector_t res;
  igraph_vector_init(&res, vs.size());
  igraph_degree(&graph, &res, igraph_vss_vector(&ivs), static_cast<igraph_neimode_t>(mode), loops);
  return Rcpp::NumericVector(res.stor_begin, res.stor_end);
}
