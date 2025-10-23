// <https://igraph.org/c/doc/igraph-Basic.html#basic-query-operations>
#include "igraph.hpp"
#include "vector.hpp"
#include "dataframe.hpp"

#include <igraph/igraph_interface.h>

[[cpp11::register]] SEXP
graph_empty_(int n = 0, bool directed = true) {
  cpp11::external_pointer<IGraph> p(new IGraph());
  igraph_empty(p->data(), n, directed);
  p->init_attr();
  return p;
}

[[cpp11::register]] SEXP
graph_copy_(const cpp11::external_pointer<IGraph> graph) {
  return cpp11::external_pointer<IGraph>(new IGraph(*graph.get()));
}

[[cpp11::register]]
int vcount_(const cpp11::external_pointer<IGraph> graph) {
  return igraph_vcount(graph->data());
}

[[cpp11::register]]
int ecount_(const cpp11::external_pointer<IGraph> graph) {
  return igraph_ecount(graph->data());
}

[[cpp11::register]]
bool is_directed_(const cpp11::external_pointer<IGraph> graph) {
  return igraph_is_directed(graph->data());
}

[[cpp11::register]] SEXP
edge_(const cpp11::external_pointer<IGraph> graph, int eid) {
  IVector<AsIndices> res(2);
  auto begin = res.data()->stor_begin;
  igraph_edge(graph->data(), --eid, begin, begin + 1);
  return res.wrap();
}

[[cpp11::register]] SEXP
neighbors_(const cpp11::external_pointer<IGraph> graph, int node, const int mode, int loops, bool multiple) {
  IVector<AsIndices> res(1);
  igraph_neighbors(graph->data(), res.data(), --node,
    static_cast<igraph_neimode_t>(mode), static_cast<igraph_loops_t>(loops), multiple);
  return res.wrap();
}

[[cpp11::register]] SEXP
incident_(const cpp11::external_pointer<IGraph> graph, int node, const int mode, const int loops) {
  IVector<AsIndices> res(1);
  igraph_incident(graph->data(), res.data(), --node,
    static_cast<igraph_neimode_t>(mode), static_cast<igraph_loops_t>(loops));
  return res.wrap();
}

[[cpp11::register]] SEXP
degree_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids, const int mode, const int loops) {
  const R_xlen_t n = vids.size();
  IVector<AsValues> res(n > 0 ? n : graph->vcount());
  igraph_degree(
    graph->data(), res.data(),
    (n > 0) ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    static_cast<igraph_neimode_t>(mode), static_cast<igraph_loops_t>(loops));
  return res.wrap();
}

[[cpp11::register]]
void add_vertices_(cpp11::external_pointer<IGraph> graph, int n) {
  if (n <= 0) return;
  igraph_add_vertices(graph->data(), n, nullptr);
  impl::append_na_rows(&graph->Vattr_, n);
}

[[cpp11::register]]
void add_edges_(cpp11::external_pointer<IGraph> graph, const cpp11::integers& edges) {
  const int new_vs = std::max(0, *std::max_element(edges.begin(), edges.end()) - graph->vcount());
  if (new_vs) add_vertices_(graph, new_vs);
  igraph_add_edges(graph->data(), ISelectorInPlace(edges).data(), nullptr);
  impl::append_na_rows(&graph->Eattr_, edges.size() / 2);
}

[[cpp11::register]]
void delete_edges_(cpp11::external_pointer<IGraph> graph, const cpp11::integers& eids) {
  impl::filter(&graph->Eattr_, eids, true);
  igraph_delete_edges(graph->data(), ISelectorInPlace(eids).ess());
}

[[cpp11::register]]
void delete_vertices_(cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids) {
  impl::filter(&graph->Eattr_, impl::R_in(graph->from(), vids) | impl::R_in(graph->to(), vids), true);
  impl::filter(&graph->Vattr_, vids, true);
  igraph_delete_vertices(graph->data(), ISelectorInPlace(vids).vss());
}

[[cpp11::register]] int
VCOUNT_MAX() { return IGRAPH_VCOUNT_MAX; }

[[cpp11::register]] int
ECOUNT_MAX() { return IGRAPH_ECOUNT_MAX; }

[[cpp11::register]] int
UNLIMITED() { return IGRAPH_UNLIMITED; }
