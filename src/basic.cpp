#include "igraph.hpp"
#include "vector.hpp"
#include "dataframe.hpp"

#include <igraph/igraph_interface.h>

// [[Rcpp::export]]
bool is_directed_(const IGraph& graph) {
  return igraph_is_directed(graph.data());
}

// [[Rcpp::export]]
int vcount_(const IGraph& graph) {
  return graph.vcount();
}

// [[Rcpp::export]]
int ecount_(const IGraph& graph) {
  return graph.ecount();
}

int IGraph::vcount() const {
  return igraph_vcount(data_.get());
}

int IGraph::ecount() const {
  return igraph_ecount(data_.get());
}

// [[Rcpp::export]]
Rcpp::IntegerVector
edge_(const IGraph& graph, int eid) {
  IVector<AsIndicesInPlace> res(2);
  auto begin = res.data()->stor_begin;
  igraph_edge(graph.data(), --eid, begin, begin + 1);
  return res.wrap();
}

// [[Rcpp::export]]
Rcpp::IntegerVector
neighbors_(const IGraph& graph, int node, const int mode) {
  IVector<AsIndicesInPlace> res(1);
  igraph_neighbors(graph.data(), res.data(), --node, static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

// [[Rcpp::export]]
Rcpp::IntegerVector
incident_(const IGraph& graph, int node, const int mode) {
  IVector<AsIndicesInPlace> res(1);
  igraph_incident(graph.data(), res.data(), --node, static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

// [[Rcpp::export]]
Rcpp::IntegerVector
degree_(const IGraph& graph, const Rcpp::IntegerVector& vids, const int mode, const bool loops) {
  const R_xlen_t n = vids.size();
  IVector<AsValues> res(n > 0 ? n : graph.vcount());
  igraph_degree(
    graph.data(), res.data(),
    (n > 0) ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    static_cast<igraph_neimode_t>(mode), loops);
  return res.wrap();
}

// [[Rcpp::export]]
void add_vertices_(IGraph* graph, int n) {
  igraph_add_vertices(graph->data(), n, nullptr);
  impl::append_na_rows(graph->Vattr_, n);
}

// [[Rcpp::export]]
void add_edges_(IGraph* graph, const Rcpp::IntegerVector& eids) {
  const int new_vs = Rcpp::max(eids) - graph->vcount();
  if (new_vs) add_vertices_(graph, new_vs);
  igraph_add_edges(graph->data(), ISelectorInPlace(eids).data(), nullptr);
  impl::append_na_rows(graph->Eattr_, eids.size() / 2);
}

// [[Rcpp::export]]
void delete_edges_(IGraph* graph, const Rcpp::IntegerVector& eids) {
  ISelectorInPlace ceids(eids);
  impl::filter(graph->Eattr_, impl::negate(eids, graph->ecount()));
  igraph_delete_edges(graph->data(), ceids.ess());
}

// [[Rcpp::export]]
void delete_vertices_(IGraph* graph, const Rcpp::IntegerVector& vids) {
  Rcpp::LogicalVector eidx = Rcpp::in(graph->from(), vids) | Rcpp::in(graph->to(), vids);
  impl::filter(graph->Eattr_, !eidx);
  ISelectorInPlace cvids(vids);
  impl::filter(graph->Vattr_, impl::negate(vids, graph->vcount()));
  igraph_delete_vertices(graph->data(), cvids.vss());
}
