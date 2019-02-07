#include "igraphlite_types.h"
#include "igraph.hpp"

RCPP_MODULE(igraph) {
  Rcpp::class_<IGraph>("IGraph")
    .constructor<int, bool>() // igraph_empty()

    // Basic interface
    .const_method("vcount", &IGraph::vcount)
    .const_method("ecount", &IGraph::ecount)
    .const_method("neighbors", &IGraph::neighbors)
    .const_method("is_directed", &IGraph::is_directed)
    .const_method("degree", &IGraph::degree)

    .const_method("edgelist", &IGraph::edgelist)
    .const_method("from", &IGraph::from)
    .const_method("to", &IGraph::to)
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

void IGraph::init_attr() {
  Rcpp::StringVector cls{"tbl_df", "tbl", "data.frame"};
  Vattr_.attr("class") = cls;
  Eattr_.attr("class") = cls;
  Vattr_.attr("row.names") = Rcpp::seq_len(vcount());
  Eattr_.attr("row.names") = Rcpp::seq_len(ecount());
}

Rcpp::NumericVector
IGraph::neighbors(const int node, const int mode) const {
  IVector iv;
  igraph_neighbors(&data_, iv.data(), node, static_cast<igraph_neimode_t>(mode));
  return iv;
}

Rcpp::NumericVector
IGraph::degree(const Rcpp::NumericVector& vids, const int mode, const bool loops) const {
  const R_xlen_t n = vids.size();
  IVector res(n > 0 ? n : vcount());
  igraph_vs_t vs;
  if (n > 0) {
    IVectorView ivs(vids);
    igraph_vs_vector(&vs, ivs.data());
  } else {
    igraph_vs_all(&vs);
  }
  igraph_degree(&data_, res.data(), std::move(vs), static_cast<igraph_neimode_t>(mode), loops);
  return res;
}
