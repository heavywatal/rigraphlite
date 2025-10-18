// <https://igraph.org/c/doc/igraph-Structural.html#centrality-measures>
#include "igraph.hpp"

#include "vector.hpp"

#include <igraph/igraph_centrality.h>

[[cpp11::register]] SEXP
closeness_(const cpp11::external_pointer<IGraph> graph,
    const cpp11::integers& vids,
    const int mode,
    const cpp11::doubles& weights,
    const bool normalized) {
  const int n = vids.size();
  IVector<AsValues, InitSize> res(n > 0 ? n : graph->vcount());
  igraph_closeness(graph->data(),
    res.data(), nullptr, nullptr,
    n > 0 ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    static_cast<igraph_neimode_t>(mode),
    weights.size() ? IVectorView(weights).data() : nullptr,
    normalized);
  return res.wrap();
}

[[cpp11::register]] SEXP
harmonic_centrality_(const cpp11::external_pointer<IGraph> graph,
    const cpp11::integers& vids,
    const int mode,
    const cpp11::doubles& weights,
    const bool normalized) {
  const int n = vids.size();
  IVector<AsValues, InitSize> res(n > 0 ? n : graph->vcount());
  igraph_harmonic_centrality(graph->data(),
    res.data(),
    n > 0 ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    static_cast<igraph_neimode_t>(mode),
    weights.size() ? IVectorView(weights).data() : nullptr,
    normalized);
  return res.wrap();
}

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

[[cpp11::register]] SEXP
pagerank_(const cpp11::external_pointer<IGraph> graph,
    const cpp11::doubles& weights,
    const cpp11::doubles& reset,
    const double damping,
    const bool directed,
    const cpp11::integers& vids) {
  const int n = vids.size();
  IVector<AsValues, InitSize> res(n > 0 ? n : graph->vcount());
  if (reset.size() > 0) {
    igraph_personalized_pagerank(graph->data(),
      weights.size() ? IVectorView(weights).data() : nullptr,
      res.data(), nullptr,
      IVectorView(reset).data(),
      damping,
      directed,
      n > 0 ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
      IGRAPH_PAGERANK_ALGO_PRPACK,
      nullptr);
  } else {
    igraph_pagerank(graph->data(),
      weights.size() ? IVectorView(weights).data() : nullptr,
      res.data(), nullptr,
      damping,
      directed,
      n > 0 ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
      IGRAPH_PAGERANK_ALGO_PRPACK,
      nullptr);
  }
  return res.wrap();
}

[[cpp11::register]] SEXP
constraint_(const cpp11::external_pointer<IGraph> graph,
    const cpp11::integers& vids,
    const cpp11::doubles& weights) {
  const int n = vids.size();
  IVector<AsValues, InitSize> res(n > 0 ? n : graph->vcount());
  igraph_constraint(graph->data(),
    res.data(),
    n > 0 ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    weights.size() ? IVectorView(weights).data() : nullptr);
  return res.wrap();
}

[[cpp11::register]] SEXP
eigenvector_centrality_(const cpp11::external_pointer<IGraph> graph,
    const int mode, const cpp11::doubles& weights) {
  IVector<AsValues, InitSize> res(graph->vcount());
  igraph_eigenvector_centrality(graph->data(),
    res.data(), nullptr,
    static_cast<igraph_neimode_t>(mode),
    weights.size() ? IVectorView(weights).data() : nullptr,
    nullptr);
  return res.wrap();
}

[[cpp11::register]] SEXP
hub_and_authority_scores_(const cpp11::external_pointer<IGraph> graph,
    const cpp11::doubles& weights) {
  IVector<AsValues, InitSize> hub(graph->vcount());
  IVector<AsValues, InitSize> authority(graph->vcount());
  igraph_hub_and_authority_scores(graph->data(),
    hub.data(), authority.data(), nullptr,
    weights.size() ? IVectorView(weights).data() : nullptr,
    nullptr);
  cpp11::writable::data_frame res = {
    cpp11::named_arg("hub") = hub.wrap(),
    cpp11::named_arg("authority") = authority.wrap()
  };
  return res;
}

[[cpp11::register]] SEXP
convergence_degree_(const cpp11::external_pointer<IGraph> graph) {
  IVector<AsValues, InitSize> res(graph->ecount());
  igraph_convergence_degree(graph->data(), res.data(), nullptr, nullptr);
  return res.wrap();
}
