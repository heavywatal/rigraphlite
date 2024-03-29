#include "igraph.hpp"
#include "vector.hpp"
#include "dataframe.hpp"

#include <igraph/igraph_interface.h>

int IGraph::vcount() const {
  return igraph_vcount(data_.get());
}

int IGraph::ecount() const {
  return igraph_ecount(data_.get());
}

bool IGraph::is_directed() const {
  return igraph_is_directed(data_.get());
}

Rcpp::IntegerVector
IGraph::edge(int eid) const {
  IVector<AsIndicesInPlace> res(2);
  auto begin = res.data()->stor_begin;
  igraph_edge(data_.get(), --eid, begin, begin + 1);
  return res.wrap();
}

Rcpp::IntegerVector
IGraph::neighbors(int node, const int mode) const {
  IVector<AsIndicesInPlace> res(1);
  igraph_neighbors(data_.get(), res.data(), --node, static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

Rcpp::IntegerVector
IGraph::incident(int node, const int mode) const {
  IVector<AsIndicesInPlace> res(1);
  igraph_incident(data_.get(), res.data(), --node, static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

Rcpp::IntegerVector
IGraph::degree(const Rcpp::IntegerVector& vids, const int mode, const bool loops) const {
  const R_xlen_t n = vids.size();
  IVector<AsValues> res(n > 0 ? n : vcount());
  igraph_degree(
    data_.get(), res.data(),
    (n > 0) ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    static_cast<igraph_neimode_t>(mode), loops);
  return res.wrap();
}

void IGraph::add_edges(const Rcpp::IntegerVector& edges) {
  const int new_vs = Rcpp::max(edges) - vcount();
  if (new_vs) add_vertices(new_vs);
  igraph_add_edges(data_.get(), ISelectorInPlace(edges).data(), nullptr);
  impl::append_na_rows(Eattr_, edges.size() / 2);
}

void IGraph::add_vertices(int n) {
  igraph_add_vertices(data_.get(), n, nullptr);
  impl::append_na_rows(Vattr_, n);
}

void IGraph::delete_edges(const Rcpp::IntegerVector& eids) {
  ISelectorInPlace ceids(eids);
  impl::filter(Eattr_, impl::negate(eids, ecount()));
  igraph_delete_edges(data_.get(), ceids.ess());
}

void IGraph::delete_vertices(const Rcpp::IntegerVector& vids) {
  Rcpp::LogicalVector eidx = Rcpp::in(from(), vids) | Rcpp::in(to(), vids);
  impl::filter(Eattr_, !eidx);
  ISelectorInPlace cvids(vids);
  impl::filter(Vattr_, impl::negate(vids, vcount()));
  igraph_delete_vertices(data_.get(), cvids.vss());
}
