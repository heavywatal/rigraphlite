#include "igraph.hpp"
#include "vector.hpp"
#include "dataframe.hpp"

#include <Rinternals.h>

#include <igraph/igraph_interface.h>

long IGraph::vcount() const {
  return igraph_vcount(data_.get());
}

long IGraph::ecount() const {
  return igraph_ecount(data_.get());
}

bool IGraph::is_directed() const {
  return igraph_is_directed(data_.get());
}

cpp11::integers
IGraph::edge(int eid) const {
  cpp11::writable::integers res(2);
  igraph_edge(data_.get(), --eid, &INTEGER(res)[0], &INTEGER(res)[1]);
  INTEGER(res)[0] += 1;
  INTEGER(res)[1] += 1;
  return res;
}

cpp11::doubles
IGraph::neighbors(int node, const int mode) const {
  IVector<AsIndicesInPlace> res(1);
  igraph_neighbors(data_.get(), res.data(), --node, static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

cpp11::doubles
IGraph::incident(int node, const int mode) const {
  IVector<AsIndicesInPlace> res(1);
  igraph_incident(data_.get(), res.data(), --node, static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

cpp11::doubles
IGraph::degree(const cpp11::doubles& vids, const int mode, const bool loops) const {
  const R_xlen_t n = vids.size();
  IVector<AsValues> res(n > 0 ? n : vcount());
  igraph_degree(
    data_.get(), res.data(),
    (n > 0) ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    static_cast<igraph_neimode_t>(mode), loops);
  return res.wrap();
}

void IGraph::add_edges(const cpp11::doubles& edges) {
  const long new_vs = static_cast<long>(std::max(edges)) - vcount();
  if (new_vs) add_vertices(new_vs);
  igraph_add_edges(data_.get(), ISelectorInPlace(edges).data(), nullptr);
  impl::append_na_rows(Eattr_, edges.size() / 2);
}

void IGraph::add_vertices(int n) {
  igraph_add_vertices(data_.get(), n, nullptr);
  impl::append_na_rows(Vattr_, n);
}

void IGraph::delete_edges(const cpp11::doubles& eids) {
  ISelectorInPlace ceids(eids);
  auto idx = Rcpp::as<cpp11::integers>(ceids.wrap());
  impl::filter(Eattr_, impl::negate(idx, ecount()));
  igraph_delete_edges(data_.get(), ceids.ess());
}

void IGraph::delete_vertices(const cpp11::doubles& vids) {
  cpp11::logicals eidx = Rcpp::in(from(), vids) | Rcpp::in(to(), vids);
  impl::filter(Eattr_, !eidx);
  ISelectorInPlace cvids(vids);
  auto idx = Rcpp::as<cpp11::integers>(cvids.wrap());
  impl::filter(Vattr_, impl::negate(idx, vcount()));
  igraph_delete_vertices(data_.get(), cvids.vss());
}
