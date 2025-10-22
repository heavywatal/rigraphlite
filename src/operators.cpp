// <https://igraph.org/c/doc/igraph-Operators.html>
#include "igraph.hpp"
#include "vector.hpp"
#include "dataframe.hpp"

#include <igraph/igraph_operators.h>

[[cpp11::register]] void
rewire_(const cpp11::external_pointer<IGraph> graph,
    const int n,
    const int edge_type_sw = 0) {
  igraph_rewire(graph->data(), n, edge_type_sw, nullptr);
}

[[cpp11::register]] SEXP
induced_subgraph_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids, int impl) {
  cpp11::external_pointer<IGraph> res(new IGraph());
  igraph_induced_subgraph(
    graph->data(), res->data(), ISelectorInPlace(vids).vss(),
    static_cast<igraph_subgraph_implementation_t>(impl));
  res->Vattr_ = graph->Vattr_;
  impl::filter(&res->Vattr_, vids);
  impl::set_data_frame_attributes(&res->Eattr_, res->ecount()); // TODO
  return res;
}

[[cpp11::register]] SEXP
induced_subgraph_edges_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids) {
  IVector<AsIndices> res(std::min(graph->ecount(), static_cast<int>(vids.size())));
  igraph_induced_subgraph_edges(
    graph->data(), ISelectorInPlace(vids).vss(), res.data());
  return res.wrap();
}

[[cpp11::register]] SEXP
subgraph_from_edges_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& eids, const bool delete_vertices) {
  cpp11::external_pointer<IGraph> res(new IGraph());
  igraph_subgraph_from_edges(
    graph->data(), res->data(), ISelectorInPlace(eids).ess(), delete_vertices
  );
  impl::set_data_frame_attributes(&res->Vattr_, res->vcount()); // TODO
  res->Eattr_ = graph->Eattr_;
  impl::filter(&res->Eattr_, eids);
  return res;
}
