#include "igraphlite_types.h"
#include "igraph.hpp"

#include "vector.hpp"

#include <igraph/igraph_interface.h>
#include <igraph/igraph_constructors.h>

RCPP_MODULE(igraph) {
  Rcpp::class_<IGraph>("IGraph")
    .constructor<int, bool>() // igraph_empty()

    // Basic interface
    .const_method("vcount", &IGraph::vcount)
    .const_method("ecount", &IGraph::ecount)
    .const_method("neighbors", &IGraph::neighbors)
    .const_method("is_directed", &IGraph::is_directed)
    .const_method("degree", &IGraph::degree)

    .const_method("are_connected", &IGraph::are_connected)
    .const_method("shortest_paths", &IGraph::shortest_paths)
    .const_method("neighborhood_size", &IGraph::neighborhood_size)

    .const_method("edgelist", &IGraph::edgelist)
    .const_method("from", &IGraph::from)
    .const_method("to", &IGraph::to)
    .property("V", &IGraph::getV, &IGraph::setV)
    .property("E", &IGraph::getE, &IGraph::setE)
  ;

  // Workaround: free functions in RcppExport.cpp cannot return incomplete class
  Rcpp::function("graph_from_symbolic_edgelist", &IGraph::graph_from_symbolic_edgelist,
    Rcpp::List::create(Rcpp::_["edgelist"], Rcpp::_["directed"] = true)
  );

  Rcpp::function("graph_from_edgelist", &IGraph::graph_from_edgelist,
    Rcpp::List::create(Rcpp::_["edgelist"], Rcpp::_["directed"] = true)
  );

  Rcpp::function("igraph_create", &IGraph::create,
    Rcpp::List::create(Rcpp::_["edges"], Rcpp::_["n"] = 0, Rcpp::_["directed"] = true)
  );

  Rcpp::function("igraph_tree", &IGraph::tree,
    Rcpp::List::create(Rcpp::_["n"], Rcpp::_["children"] = 2, Rcpp::_["mode"] = 0)
  );
}


IGraph::~IGraph() noexcept {
  if (data_) igraph_destroy(data_.get());
}

IGraph::IGraph(const IGraph& other) noexcept {
  igraph_copy(data_.get(), other.data_.get());
  Vattr_ = other.Vattr_;
  Eattr_ = other.Eattr_;
}

IGraph::IGraph(int n, bool directed) {
  igraph_empty(data_.get(), n, directed);
  init_attr();
}

IGraph::IGraph(const Rcpp::NumericVector& edges, int n, bool directed) {
  igraph_create(data_.get(), ISelector(edges).data(), n, directed);
  init_attr();
}

inline Rcpp::CharacterVector tibble_class() {
  return Rcpp::CharacterVector::create("tbl_df", "tbl", "data.frame");
}

inline void set_rownames(Rcpp::DataFrame& df, int n) {
  df.attr("row.names") = Rcpp::IntegerVector{Rcpp::IntegerVector::get_na(), -n};
}

inline void mutate(Rcpp::DataFrame& df, const char* name, Rcpp::RObject value) {
  Rcpp::List attr_holder;
  Rf_copyMostAttrib(df, attr_holder);
  df[name] = value;
  Rf_copyMostAttrib(attr_holder, df);
}

IGraph IGraph::graph_from_symbolic_edgelist(Rcpp::IntegerMatrix edgelist, bool directed) {
  auto sym_edges = Rcpp::as_vector(Rcpp::transpose(edgelist));
  auto symbols = Rcpp::sort_unique(sym_edges);
  auto edges = Rcpp::match(sym_edges, symbols);
  IGraph g(Rcpp::as<Rcpp::NumericVector>(edges), 0, directed);
  mutate(g.Vattr_, "name", symbols);
  return g;
}

IGraph IGraph::graph_from_edgelist(Rcpp::NumericMatrix edgelist, bool directed) {
  return IGraph(Rcpp::transpose(edgelist), 0, directed);
}

IGraph IGraph::create(const Rcpp::NumericVector& edges, int n, bool directed) {
  return IGraph(edges, n, directed);
}

IGraph IGraph::tree(int n, int children, int mode) {
  IGraph g;
  igraph_tree(g.data(), n, children, static_cast<igraph_tree_mode_t>(mode));
  g.init_attr();
  return g;
}


long IGraph::vcount() const {
  return igraph_vcount(data_.get());
}

long IGraph::ecount() const {
  return igraph_ecount(data_.get());
}

Rcpp::NumericVector
IGraph::neighbors(const int node, const int mode) const {
  IVector iv;
  igraph_neighbors(data_.get(), iv.data(), node, static_cast<igraph_neimode_t>(mode));
  return iv;
}

bool IGraph::is_directed() const {
  return igraph_is_directed(data_.get());
}

Rcpp::NumericVector
IGraph::degree(const Rcpp::NumericVector& vids, const int mode, const bool loops) const {
  const R_xlen_t n = vids.size();
  IVector res(n > 0 ? n : vcount());
  igraph_degree(
    data_.get(), res.data(),
    (n > 0) ? ISelector(vids) : igraph_vss_all(),
    static_cast<igraph_neimode_t>(mode), loops);
  return res;
}


void IGraph::init_attr() {
  Vattr_.attr("class") = tibble_class();
  Eattr_.attr("class") = tibble_class();
  set_rownames(Vattr_, vcount());
  set_rownames(Eattr_, ecount());
}

Rcpp::NumericVector IGraph::from() const {return as_rvector(data_->from) + 1;}
Rcpp::NumericVector IGraph::to() const {return as_rvector(data_->to) + 1;}
