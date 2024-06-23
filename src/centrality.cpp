// <https://igraph.org/c/doc/igraph-Structural.html#centrality-measures>
#include "igraph.hpp"

#include "vector.hpp"

#include <igraph/igraph_centrality.h>

[[cpp11::register]] SEXP
edge_betweenness_(const cpp11::external_pointer<IGraph> graph,
  const bool directed, const cpp11::doubles& weights) {
  IVector<AsValues, InitSize> res(graph->ecount());
  igraph_edge_betweenness(graph->data(), res.data(), directed, weights.size() ? IVectorView(weights).data() : nullptr);
  return res.wrap();
}

[[cpp11::register]] SEXP
edge_betweenness_subset_(const cpp11::external_pointer<IGraph> graph,
    const bool directed,
    const cpp11::integers& eids,
    const cpp11::doubles& weights,
    const cpp11::integers& sources,
    const cpp11::integers& targets) {
  IVector<AsValues, InitSize> res(graph->ecount());
  igraph_edge_betweenness_subset(
    graph->data(), res.data(),
    eids.size() ? ISelector(eids).ess() : igraph_ess_all(igraph_edgeorder_type_t::IGRAPH_EDGEORDER_ID),
    directed,
    sources.size() > 0 ? ISelector(sources).vss() : igraph_vss_all(),
    targets.size() > 0 ? ISelector(targets).vss() : igraph_vss_all(),
    weights.size() ? IVectorView(weights).data() : nullptr
  );
  return res.wrap();
}
