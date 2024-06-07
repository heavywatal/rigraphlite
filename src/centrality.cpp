#include "igraph.hpp"

#include "vector.hpp"

#include <igraph/igraph_centrality.h>

// [[Rcpp::export]]
Rcpp::NumericVector edge_betweenness_(const IGraph& graph, const bool directed, const Rcpp::NumericVector& weights) {
  IVector<AsValues, InitSize> res(graph.ecount());
  igraph_edge_betweenness(graph.data(), res.data(), directed, weights.size() ? IVectorView(weights).data() : nullptr);
  return res.wrap();
}

// [[Rcpp::export]]
Rcpp::NumericVector edge_betweenness_subset_(const IGraph& graph, const bool directed,
    const Rcpp::IntegerVector& eids,
    const Rcpp::NumericVector& weights,
    const Rcpp::IntegerVector& sources,
    const Rcpp::IntegerVector& targets) {
  IVector<AsValues, InitSize> res(graph.ecount());
  igraph_edge_betweenness_subset(
    graph.data(), res.data(),
    eids.size() ? ISelector(eids).ess() : igraph_ess_all(igraph_edgeorder_type_t::IGRAPH_EDGEORDER_ID),
    directed,
    sources.size() > 0 ? ISelector(sources).vss() : igraph_vss_all(),
    targets.size() > 0 ? ISelector(targets).vss() : igraph_vss_all(),
    weights.size() ? IVectorView(weights).data() : nullptr
  );
  return res.wrap();
}
