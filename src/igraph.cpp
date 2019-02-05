#include "igraphlite_types.h"
#include "igraph.hpp"

RCPP_MODULE(igraph) {
  Rcpp::class_<IGraph>("IGraph")
    .constructor<int, bool>() // igraph_empty()
    .const_method("is_directed", &IGraph::is_directed)
    .const_method("from", &IGraph::from)
    .const_method("to", &IGraph::to)
    .const_method("vcount", &IGraph::vcount)
    .const_method("ecount", &IGraph::ecount)
    .property("V", &IGraph::getV, &IGraph::setV)
    .property("E", &IGraph::getE, &IGraph::setE)
  ;

  // Workaround: free functions in RcppExport.cpp cannot return incomplete class
  Rcpp::function("igraph_create", &IGraph::create,
    Rcpp::List::create(Rcpp::_["edges"], Rcpp::_["n"] = 0, Rcpp::_["directed"] = true)
  );

  Rcpp::function("igraph_tree", &IGraph::tree,
    Rcpp::List::create(Rcpp::_["n"], Rcpp::_["children"] = 2, Rcpp::_["mode"] = 0)
  );
}

// [[Rcpp::export]]
Rcpp::NumericMatrix edgelist(const IGraph& graph) {
  return Rcpp::cbind(graph.from(), graph.to());
}

// [[Rcpp::export]]
Rcpp::NumericVector
impl_degree_all(const IGraph& graph, int mode = 3, bool loops = true) {
  IVector res(graph.vcount());
  igraph_degree(graph.data(), res.data(), igraph_vss_all(), static_cast<igraph_neimode_t>(mode), loops);
  return res;
}

// [[Rcpp::export]]
Rcpp::NumericVector
impl_degree(const IGraph& graph, const Rcpp::NumericVector& vs, int mode = 3, bool loops = true) {
  IVector res(vs.size());
  IVectorView ivs(vs);
  igraph_degree(graph.data(), res.data(), igraph_vss_vector(ivs.data()), static_cast<igraph_neimode_t>(mode), loops);
  return res;
}
