#include "igraph.hpp"
#include "vector.hpp"
#include "dataframe.hpp"

#include <igraph/igraph_interface.h>

SEXP IGraph::V() const {
  return Vattr_.attr(R_RowNamesSymbol);
}

[[cpp11::register]]
SEXP V_(const cpp11::external_pointer<IGraph> graph) {
  return graph->V();
}

SEXP IGraph::E() const {
  return Eattr_.attr(R_RowNamesSymbol);
}

[[cpp11::register]]
SEXP E_(const cpp11::external_pointer<IGraph> graph) {
  return graph->E();
}

[[cpp11::register]]
int vcount_(const cpp11::external_pointer<IGraph> graph) {
  return igraph_vcount(graph->data());
}

[[cpp11::register]]
int ecount_(const cpp11::external_pointer<IGraph> graph) {
  return igraph_ecount(graph->data());
}

int IGraph::vcount() const {
  return igraph_vcount(data_.get());
}

int IGraph::ecount() const {
  return igraph_ecount(data_.get());
}

[[cpp11::register]]
bool is_directed_(const cpp11::external_pointer<IGraph> graph) {
  return igraph_is_directed(graph->data());
}

[[cpp11::register]]
cpp11::integers
edge_(const cpp11::external_pointer<IGraph> graph, int eid) {
  IVector<AsIndices> res(2);
  auto begin = res.data()->stor_begin;
  igraph_edge(graph->data(), --eid, begin, begin + 1);
  return res.wrap();
}

[[cpp11::register]]
cpp11::integers
neighbors_(const cpp11::external_pointer<IGraph> graph, int node, const int mode) {
  IVector<AsIndices> res(1);
  igraph_neighbors(graph->data(), res.data(), --node, static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

[[cpp11::register]]
cpp11::integers
incident_(const cpp11::external_pointer<IGraph> graph, int node, const int mode) {
  IVector<AsIndices> res(1);
  igraph_incident(graph->data(), res.data(), --node, static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

[[cpp11::register]]
cpp11::integers
degree_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids, const int mode, const bool loops) {
  const R_xlen_t n = vids.size();
  IVector<AsValues> res(n > 0 ? n : graph->vcount());
  igraph_degree(
    graph->data(), res.data(),
    (n > 0) ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    static_cast<igraph_neimode_t>(mode), loops);
  return res.wrap();
}

[[cpp11::register]]
void add_vertices_(cpp11::external_pointer<IGraph> graph, int n) {
  igraph_add_vertices(graph->data(), n, nullptr);
  impl::append_na_rows(graph->Vattr_, n);
}

[[cpp11::register]]
void add_edges_(cpp11::external_pointer<IGraph> graph, const cpp11::integers& edges) {
  const int new_vs = *std::max_element(edges.begin(), edges.end()) - graph->vcount();
  if (new_vs) add_vertices_(graph, new_vs);
  igraph_add_edges(graph->data(), ISelectorInPlace(edges).data(), nullptr);
  impl::append_na_rows(graph->Eattr_, edges.size() / 2);
}

[[cpp11::register]]
void delete_edges_(cpp11::external_pointer<IGraph> graph, const cpp11::integers& eids) {
  ISelectorInPlace ceids(eids);
  impl::filter(graph->Eattr_, impl::negate(eids, graph->ecount()));
  igraph_delete_edges(graph->data(), ceids.ess());
}

[[cpp11::register]]
void delete_vertices_(cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids) {
  impl::filter(graph->Eattr_, impl::Rcpp_or(impl::Rcpp_in(graph->from(), vids), impl::Rcpp_in(graph->to(), vids)));
  ISelectorInPlace cvids(vids);
  impl::filter(graph->Vattr_, impl::negate(vids, graph->vcount()));
  igraph_delete_vertices(graph->data(), cvids.vss());
}
