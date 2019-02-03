// [[Rcpp::plugins(cpp14)]]
#include "igraphlite_types.h"

#include <Rcpp.h>

#include <igraph/igraph_interface.h>

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
