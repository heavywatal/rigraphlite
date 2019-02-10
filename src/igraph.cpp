#include "igraphlite_types.h"

#include "vector.hpp"

#include <igraph/igraph_interface.h>
#include <igraph/igraph_constructors.h>

RCPP_MODULE(igraph) {
  Rcpp::class_<IGraph>("IGraph")
    .constructor<int, bool>() // igraph_empty()
    .constructor<const IGraph&, Rcpp::NumericVector, int>()

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

    .const_method("edgelist", &IGraph::edgelist)
    .const_method("from", &IGraph::from)
    .const_method("to", &IGraph::to)
    .const_method("oi", &IGraph::oi)
    .const_method("ii", &IGraph::ii)
    .const_method("os", &IGraph::os)
    .const_method("is", &IGraph::is)
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

Rcpp::NumericVector IGraph::from() const {return as_rvector(data_->from) + 1;}
Rcpp::NumericVector IGraph::to() const {return as_rvector(data_->to) + 1;}
Rcpp::NumericVector IGraph::oi() const {return as_rvector(data_->oi) + 1;}
Rcpp::NumericVector IGraph::ii() const {return as_rvector(data_->ii) + 1;}
Rcpp::NumericVector IGraph::os() const {return as_rvector(data_->os) + 1;}
Rcpp::NumericVector IGraph::is() const {return as_rvector(data_->is) + 1;}

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
// Attributes

namespace impl {

  inline Rcpp::CharacterVector tibble_class() {
    return Rcpp::CharacterVector::create("tbl_df", "tbl", "data.frame");
  }

  inline void set_rownames(Rcpp::DataFrame& df, int n) {
    df.attr("row.names") = Rcpp::IntegerVector{Rcpp::IntegerVector::get_na(), -n};
  }

  inline void mutate(Rcpp::DataFrame& df, const char* name, const Rcpp::RObject& value) {
    Rcpp::List attr_holder;
    Rf_copyMostAttrib(df, attr_holder);
    df[name] = value;
    Rf_copyMostAttrib(attr_holder, df);
  }

}

void IGraph::setV(const char* name, const Rcpp::RObject& value) {
  impl::mutate(Vattr_, name, value);
}

void IGraph::setE(const char* name, const Rcpp::RObject& value) {
  impl::mutate(Eattr_, name, value);
}

void IGraph::init_attr() {
  Vattr_.attr("class") = impl::tibble_class();
  Eattr_.attr("class") = impl::tibble_class();
  impl::set_rownames(Vattr_, vcount());
  impl::set_rownames(Eattr_, ecount());
}
