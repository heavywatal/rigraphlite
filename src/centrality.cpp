// <https://igraph.org/c/doc/igraph-Structural.html#centrality-measures>
#include "igraph.hpp"

#include "vector.hpp"

#include <igraph/igraph_centrality.h>

[[cpp11::register]] SEXP
betweenness_(const cpp11::external_pointer<IGraph> graph,
    const cpp11::doubles& weights,
    const cpp11::integers& vids,
    const bool directed,
    const bool normalized,
    const double cutoff) {
  IVector<AsValues, InitSize> res(graph->ecount());
  igraph_betweenness_cutoff(graph->data(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    res.data(),
    vids.size() ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    directed,
    normalized,
    cutoff);
  return res.wrap();
}

[[cpp11::register]] SEXP
betweenness_subset_(const cpp11::external_pointer<IGraph> graph,
    const cpp11::doubles& weights,
    const cpp11::integers& sources,
    const cpp11::integers& targets,
    const cpp11::integers& vids,
    const bool directed,
    const bool normalized) {
  IVector<AsValues, InitSize> res(graph->ecount());
  igraph_betweenness_subset(graph->data(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    res.data(),
    sources.size() ? ISelector(sources).vss() : igraph_vss_all(),
    targets.size() ? ISelector(targets).vss() : igraph_vss_all(),
    vids.size() ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    directed,
    normalized);
  return res.wrap();
}

[[cpp11::register]] SEXP
edge_betweenness_(const cpp11::external_pointer<IGraph> graph,
    const cpp11::doubles& weights,
    const cpp11::integers& eids,
    const bool directed,
    const bool normalized,
    const double cutoff) {
  IVector<AsValues, InitSize> res(graph->ecount());
  igraph_edge_betweenness_cutoff(graph->data(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    res.data(),
    eids.size() ? ISelectorInPlace(eids).ess() : igraph_ess_all(igraph_edgeorder_type_t::IGRAPH_EDGEORDER_ID),
    directed,
    normalized,
    cutoff);
  return res.wrap();
}

[[cpp11::register]] SEXP
edge_betweenness_subset_(const cpp11::external_pointer<IGraph> graph,
    const cpp11::doubles& weights,
    const cpp11::integers& sources,
    const cpp11::integers& targets,
    const cpp11::integers& eids,
    const bool directed,
    const bool normalized) {
  IVector<AsValues, InitSize> res(graph->ecount());
  igraph_edge_betweenness_subset(graph->data(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    res.data(),
    sources.size() ? ISelector(sources).vss() : igraph_vss_all(),
    targets.size() ? ISelector(targets).vss() : igraph_vss_all(),
    eids.size() ? ISelectorInPlace(eids).ess() : igraph_ess_all(igraph_edgeorder_type_t::IGRAPH_EDGEORDER_ID),
    directed,
    normalized);
  return res.wrap();
}
