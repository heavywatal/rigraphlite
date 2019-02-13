#include "igraph.hpp"

#include "vector.hpp"
#include "matrix.hpp"

#include <igraph/igraph_structural.h>
#include <igraph/igraph_paths.h>
#include <igraph/igraph_neighborhood.h>

Rcpp::LogicalVector
IGraph::are_connected(int v1, int v2) const {
  igraph_bool_t res;
  igraph_are_connected(data_.get(), v1, v2, &res);
  return static_cast<bool>(res);
}

namespace impl {
  inline void shortest_paths(
    const igraph_t* graph, igraph_matrix_t* res,
    igraph_vs_t from, igraph_vs_t to,
    const igraph_vector_t* weights, igraph_neimode_t mode,
    const std::string& algorithm) {

    if (algorithm.empty() || algorithm == "unweighted") {
      igraph_shortest_paths(graph, res, from, to, mode);
    } else if (algorithm == "dijkstra") {
      igraph_shortest_paths_dijkstra(graph, res, from, to, weights, mode);
    } else if (algorithm == "bellman-ford") {
      igraph_shortest_paths_bellman_ford(graph, res, from, to, weights, mode);
    } else if (algorithm == "johnson") {
      igraph_shortest_paths_johnson(graph, res, from, to, weights);
    }
  }
}

Rcpp::NumericMatrix
IGraph::shortest_paths(
  const Rcpp::NumericVector& from, const Rcpp::NumericVector& to,
  const Rcpp::NumericVector& weights, int mode, const std::string& algorithm) const {

  const bool all = (from.size() == 0);
  IMatrix res(all ? vcount() : from.size(), all ? vcount() : to.size());
  if (all) {
    impl::shortest_paths(
      data_.get(), res.data(),
      igraph_vss_all(), igraph_vss_all(),
      weights.size() ? IVectorView(weights).data() : nullptr,
      static_cast<igraph_neimode_t>(mode), algorithm);
  } else {
    impl::shortest_paths(
      data_.get(), res.data(),
      ISelector(from), ISelector(to),
      weights.size() ? IVectorView(weights).data() : nullptr,
      static_cast<igraph_neimode_t>(mode), algorithm);
  }
  Rcpp::NumericMatrix out(res);
  if (!all) {
    Rcpp::rownames(out) = Rcpp::StringVector(from);
    Rcpp::colnames(out) = Rcpp::StringVector(to);
  }
  return out;
}

Rcpp::NumericVector
IGraph::path_length_hist(bool directed) const {
  IVector res(vcount()); // rough estimate; resized as needed
  double unconnected;
  igraph_path_length_hist(data_.get(), res.data(), &unconnected, directed);
  return res;
}

// [[Rcpp::export]]
Rcpp::IntegerVector
path_length_count_within(const IGraph& graph, const Rcpp::NumericVector& vids, bool directed) {
  std::map<int, int> counter;
  IMatrix res(1, 1);
  const auto cvids = Rcpp::as<Rcpp::IntegerVector>(vids) - 1;
  for (const int i: cvids) {
    auto vs_i = igraph_vss_1(i);
    for (const int j: cvids) {
      if (i <= j) continue;
      igraph_shortest_paths(graph.data(), res.data(), vs_i, igraph_vss_1(j), IGRAPH_ALL);
      ++counter[static_cast<int>(res.at(0, 0))];
    }
  }
  const int max_len = counter.rbegin()->first;
  Rcpp::IntegerVector output(max_len);
  for (const auto& p: counter) {
    output[p.first - 1] = p.second;
  }
  return output;
}

// [[Rcpp::export]]
Rcpp::IntegerVector
path_length_count_between(const IGraph& graph, const Rcpp::NumericVector& from, const Rcpp::NumericVector& to, bool directed) {
  std::map<double, int> counter;
  IMatrix res(1, 1);
  const int nrow = from.size();
  const int ncol = to.size();
  const auto cfrom = Rcpp::as<Rcpp::IntegerVector>(from) - 1;
  const auto cto = Rcpp::as<Rcpp::IntegerVector>(to) - 1;
  for (int i = 0; i < nrow; ++i) {
    auto vs_i = igraph_vss_1(cfrom[i]);
    for (int j = 0; j < ncol; ++j) {
      if (i <= j) continue;
      igraph_shortest_paths(graph.data(), res.data(), vs_i, igraph_vss_1(cto[j]), IGRAPH_ALL);
      ++counter[res.at(0, 0)];
    }
  }
  const int max_len = static_cast<int>(counter.rbegin()->first);
  Rcpp::IntegerVector output(max_len);
  for (const auto& p: counter) {
    output[static_cast<int>(p.first) - 1] = p.second;
  }
  return output;
}

Rcpp::NumericVector
IGraph::neighborhood_size(const Rcpp::NumericVector& vids, const int order, const int mode, const int mindist) const {
  IVector res(vids.size());
  igraph_neighborhood_size(
    data_.get(), res.data(), ISelector(vids), order,
    static_cast<igraph_neimode_t>(mode), mindist);
  return res;
}

Rcpp::List
IGraph::neighborhood(const Rcpp::NumericVector& vids, const int order, const int mode, const int mindist) const {
  const long n = vids.size();
  IVectorPtr<AsIndices> res(n);
  igraph_neighborhood(
    data_.get(), res.data(), ISelector(vids), order,
    static_cast<igraph_neimode_t>(mode), mindist);
  return res;
}

IGraph::IGraph(const IGraph& other, const Rcpp::NumericVector& vids, int impl): IGraph::IGraph() {
  igraph_induced_subgraph(
    other.data_.get(), data_.get(), ISelector(vids),
    static_cast<igraph_subgraph_implementation_t>(impl));
  init_attr();
}
