#include "igraphlite_types.h"

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
    .const_method("path_length_hist", &IGraph::path_length_hist)
    .const_method("neighborhood_size", &IGraph::neighborhood_size)
    .const_method("induced_subgraph", &IGraph::induced_subgraph)

    .const_method("edgelist", &IGraph::edgelist)
    .const_method("from", &IGraph::from)
    .const_method("to", &IGraph::to)
    .property("V", &IGraph::getV, &IGraph::setV)
    .property("E", &IGraph::getE, &IGraph::setE)
  ;
}

IGraph::IGraph(): data_(std::make_unique<igraph_t>()) {}

IGraph::~IGraph() noexcept {
  if (data_) igraph_destroy(data_.get());
}

IGraph::IGraph(const IGraph& other) noexcept: IGraph::IGraph() {
  igraph_copy(data_.get(), other.data_.get());
  Vattr_ = other.Vattr_;
  Eattr_ = other.Eattr_;
}

IGraph::IGraph(IGraph&& other) = default;

IGraph::IGraph(int n, bool directed): IGraph::IGraph() {
  igraph_empty(data_.get(), n, directed);
  init_attr();
}

IGraph::IGraph(const Rcpp::NumericVector& edges, int n, bool directed): IGraph::IGraph() {
  igraph_create(data_.get(), ISelector(edges).data(), n, directed);
  init_attr();
}

IGraph::IGraph(int n, int children, int mode): IGraph::IGraph() {
  igraph_tree(data_.get(), n, children, static_cast<igraph_tree_mode_t>(mode));
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

namespace impl {

template <int RTYPE> inline
IGraph graph_from_symbolic_edgelist(Rcpp::Matrix<RTYPE> edgelist, bool directed) {
  auto sym_edges = Rcpp::as_vector(Rcpp::transpose(edgelist));
  auto symbols = Rcpp::sort_unique(sym_edges);
  auto edges = Rcpp::match(sym_edges, symbols);
  IGraph g(Rcpp::as<Rcpp::NumericVector>(edges), 0, directed);
  g.setV("name", symbols);
  return g;
}

template <int RTYPE> inline
IGraph graph_from_data_frame(Rcpp::DataFrame df, bool directed = true) {
  using T = Rcpp::Vector<RTYPE>;
  auto g = graph_from_symbolic_edgelist(Rcpp::cbind<T, T>(df.at(0), df.at(1)), directed);
  const long n = df.ncol();
  if (n > 2) {
    Rcpp::StringVector names = df.attr("names");
    for (long i = 2; i < n; ++i) {
      g.setE(names[i], df[i]);
    }
  }
  return g;
}

}

// [[Rcpp::export]]
IGraph graph_from_symbolic_edgelist(Rcpp::RObject edgelist, bool directed = true) {
  switch (edgelist.sexp_type()) {
    case INTSXP:  return impl::graph_from_symbolic_edgelist(Rcpp::Matrix<INTSXP>(edgelist), directed);
    case REALSXP: return impl::graph_from_symbolic_edgelist(Rcpp::Matrix<REALSXP>(edgelist), directed);
    case STRSXP:  return impl::graph_from_symbolic_edgelist(Rcpp::Matrix<STRSXP>(edgelist), directed);
    default:
      throw std::range_error("Invalid type for vertex names");
  }
}

// [[Rcpp::export]]
IGraph graph_from_data_frame(Rcpp::DataFrame df, bool directed = true) {
  switch (TYPEOF(df.at(0))) {
    case INTSXP:  return impl::graph_from_data_frame<INTSXP>(df, directed);
    case REALSXP: return impl::graph_from_data_frame<REALSXP>(df, directed);
    case STRSXP:  return impl::graph_from_data_frame<STRSXP>(df, directed);
    default:
      throw std::range_error("Invalid type for vertex names");
  }
}

// [[Rcpp::export]]
IGraph graph_from_edgelist(Rcpp::NumericMatrix edgelist, bool directed = true) {
  return IGraph(Rcpp::transpose(edgelist), 0, directed);
}

// [[Rcpp::export]]
IGraph graph_create(const Rcpp::NumericVector& edges, int n = 0, bool directed = true) {
  return IGraph(edges, n, directed);
}

// [[Rcpp::export]]
IGraph graph_tree(int n, int children = 2, int mode = 0) {
  return IGraph(n, children, mode);
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


void IGraph::setV(const char* name, Rcpp::RObject value) {
  mutate(Vattr_, name, value);
}

void IGraph::setE(const char* name, Rcpp::RObject value) {
  mutate(Eattr_, name, value);
}

void IGraph::init_attr() {
  Vattr_.attr("class") = tibble_class();
  Eattr_.attr("class") = tibble_class();
  set_rownames(Vattr_, vcount());
  set_rownames(Eattr_, ecount());
}

Rcpp::NumericVector IGraph::from() const {return as_rvector(data_->from) + 1;}
Rcpp::NumericVector IGraph::to() const {return as_rvector(data_->to) + 1;}
