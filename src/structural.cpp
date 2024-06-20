#include "igraph.hpp"

#include "vector.hpp"
#include "matrix.hpp"

#include <igraph/igraph_structural.h>
#include <igraph/igraph_operators.h>
#include <igraph/igraph_paths.h>
#include <igraph/igraph_neighborhood.h>

// [[Rcpp::export]]
Rcpp::LogicalVector
are_adjacent_(const IGraph& graph, int v1, int v2) {
  igraph_bool_t res;
  igraph_are_adjacent(graph.data(), --v1, --v2, &res);
  return static_cast<bool>(res);
}

namespace impl {
  inline void distances(
    const igraph_t* graph, igraph_matrix_t* res,
    igraph_vs_t from, igraph_vs_t to,
    const igraph_vector_t* weights, igraph_neimode_t mode,
    const std::string& algorithm) {

    if (algorithm.empty() || algorithm == "unweighted") {
      igraph_distances(graph, res, from, to, mode);
    } else if (algorithm == "dijkstra") {
      igraph_distances_dijkstra(graph, res, from, to, weights, mode);
    } else if (algorithm == "bellman-ford") {
      igraph_distances_bellman_ford(graph, res, from, to, weights, mode);
    } else if (algorithm == "johnson") {
      igraph_distances_johnson(graph, res, from, to, weights);
    }
  }

  inline void get_shortest_paths(
    const igraph_t* graph, igraph_vector_int_list_t* res,
    igraph_integer_t from, igraph_vs_t&& to,
    const igraph_vector_t* weights, igraph_neimode_t mode) {

    if (weights) {
      igraph_get_shortest_paths_dijkstra(graph, res, nullptr, from, std::move(to), weights, mode, nullptr, nullptr);
    } else {
      igraph_get_shortest_paths(graph, res, nullptr, from, std::move(to), mode, nullptr, nullptr);
    }
  }

  inline void get_all_shortest_paths(
    const igraph_t* graph, igraph_vector_int_list_t* res,
    igraph_integer_t from, igraph_vs_t&& to,
    const igraph_vector_t* weights, igraph_neimode_t mode) {

    if (weights) {
      igraph_get_all_shortest_paths_dijkstra(graph, res, nullptr, nullptr, from, std::move(to), weights, mode);
    } else {
      igraph_get_all_shortest_paths(graph, res, nullptr, nullptr, from, std::move(to), mode);
    }
  }
}

// [[Rcpp::export]]
Rcpp::NumericMatrix
distances_(
  const IGraph& graph, const Rcpp::IntegerVector& from, const Rcpp::IntegerVector& to,
  const Rcpp::NumericVector& weights, int mode, const std::string& algorithm) {

  const int from_size = from.size();
  const int to_size = to.size();
  const int nrow = from_size > 0 ? from_size : graph.vcount();
  const int ncol = to_size > 0 ? to_size : graph.vcount();
  IMatrix res(nrow, ncol);
  impl::distances(graph.data(), res.data(),
                  from_size > 0 ? ISelector(from).vss() : igraph_vss_all(),
                  to_size > 0 ? ISelector(to).vss() : igraph_vss_all(),
                  weights.size() ? IVectorView(weights).data() : nullptr,
                  static_cast<igraph_neimode_t>(mode), algorithm);
  if (from_size > 0) {
    res.rownames(Rcpp::StringVector(from));
  }
  if (to_size > 0) {
    res.colnames(Rcpp::StringVector(to));
  }
  return res.wrap();
}

// experimental
// [[Rcpp::export]]
Rcpp::NumericVector
mean_distances_cpp_(const IGraph& graph,
  const Rcpp::IntegerVector& from, const Rcpp::IntegerVector& to,
  const Rcpp::NumericVector& weights, int mode, const std::string& algorithm) {

  const int to_size = to.size();
  const ISelector to_selector(to);
  const igraph_vs_t to_vss(to_size > 0 ? to_selector.vss() : igraph_vss_all());
  const igraph_vector_t* cweights = weights.size() ? IVectorView(weights).data() : nullptr;
  IMatrix res(1, to_size > 0 ? to_size : graph.vcount());
  double total = 0.0;
  int num_paths = 0;
  for (const int from_i: from.size() > 0 ? from : Rcpp::seq_len(graph.vcount())) {
    impl::distances(graph.data(), res.data(),
                    igraph_vss_1(from_i - 1), to_vss, cweights,
                    static_cast<igraph_neimode_t>(mode), algorithm);
    const auto& v = res.data()->data;
    for (auto p = v.stor_begin; p < v.end; ++p) {
      if ((*p != 0) && (*p != IGRAPH_INFINITY)) {
        total += *p;
        ++num_paths;
      }
    }
  }
  return Rcpp::NumericVector(1, total / num_paths);
}

// [[Rcpp::export]]
Rcpp::List
get_shortest_paths_(
  const IGraph& graph, int from, const Rcpp::IntegerVector& to,
  const Rcpp::NumericVector& weights, int mode) {

  const int to_size = to.size();
  IVectorIntList<AsIndicesInPlace> res(to_size > 0 ? to_size : graph.vcount());
  res.init_elements();
  impl::get_shortest_paths(
    graph.data(), res.data(), --from,
    to_size > 0 ? ISelector(to).vss() : igraph_vss_all(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

// [[Rcpp::export]]
Rcpp::List
get_all_shortest_paths_(
  const IGraph& graph, int from, const Rcpp::IntegerVector& to,
  const Rcpp::NumericVector& weights, int mode) {

  const int to_size = to.size();
  IVectorIntList<AsIndicesInPlace> res(to_size > 0 ? to_size : graph.vcount());
  res.init_elements();
  impl::get_all_shortest_paths(
    graph.data(), res.data(), --from,
    to_size > 0 ? ISelector(to).vss() : igraph_vss_all(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

// [[Rcpp::export]]
Rcpp::IntegerVector
get_all_simple_paths_(
  const IGraph& graph, int from, const Rcpp::IntegerVector& to, int cutoff, int mode) {

  const int to_size = to.size();
  IVector<AsIndicesInPlace, InitSizeInt> res(to_size > 0 ? to_size : graph.vcount());
  igraph_get_all_simple_paths(
    graph.data(), res.data(), --from,
    to_size > 0 ? ISelector(to).vss() : igraph_vss_all(),
    cutoff,
    static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

// [[Rcpp::export]]
double
average_path_length_(const IGraph& graph, bool directed) {
  double res;
  igraph_average_path_length(graph.data(), &res, nullptr, directed, true);
  return res;
}

// [[Rcpp::export]]
Rcpp::NumericVector
path_length_hist_(const IGraph& graph, bool directed) {
  IVector<AsValues, InitView> res(graph.vcount()); // rough estimate; resized as needed
  double unconnected;
  igraph_path_length_hist(graph.data(), res.data(), &unconnected, directed);
  return res.wrap();
}

// [[Rcpp::export]]
Rcpp::IntegerVector
path_length_count_within(const IGraph& graph, const Rcpp::IntegerVector& vids, bool directed) {
  std::map<int, int> counter;
  IMatrix res(1, 1);
  for (const int i: vids) {
    auto vs_i = igraph_vss_1(i - 1);
    for (const int j: vids) {
      if (i <= j) continue;
      igraph_distances(graph.data(), res.data(), vs_i, igraph_vss_1(j - 1), IGRAPH_ALL);
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
path_length_count_between(const IGraph& graph, const Rcpp::IntegerVector& from, const Rcpp::IntegerVector& to, bool directed) {
  std::map<int, int> counter;
  IMatrix res(1, 1);
  for (const int i: from) {
    auto vs_i = igraph_vss_1(i - 1);
    for (const int j: to) {
      igraph_distances(graph.data(), res.data(), vs_i, igraph_vss_1(j - 1), IGRAPH_ALL);
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
neighborhood_size_(const IGraph& graph, const Rcpp::IntegerVector& vids, const int order, const int mode, const int mindist) {
  const int n = vids.size();
  IVector<AsValues> res(n > 0 ? n : graph.vcount());
  igraph_neighborhood_size(
    graph.data(), res.data(),
    n > 0 ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    order, static_cast<igraph_neimode_t>(mode), mindist);
  return res.wrap();
}

// [[Rcpp::export]]
Rcpp::List
neighborhood_(const IGraph& graph, const Rcpp::IntegerVector& vids, const int order, const int mode, const int mindist) {
  const int n = vids.size();
  IVectorIntList<AsIndicesInPlace> res(n > 0 ? n : graph.vcount());
  igraph_neighborhood(
    graph.data(), res.data(),
    n > 0 ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    order, static_cast<igraph_neimode_t>(mode), mindist);
  return res.wrap();
}

// [[Rcpp::export]]
Rcpp::IntegerVector
subcomponent_(const IGraph& graph, const int v, const int mode) {
  IVector<AsIndicesInPlace> res(1);
  igraph_subcomponent(graph.data(), res.data(), v - 1, static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

// experimental
// [[Rcpp::export]]
Rcpp::List
subcomponents_(const IGraph& graph, const Rcpp::IntegerVector& vids, const int mode) {
  const ISelector cvids(vids);
  const int n = vids.size();
  Rcpp::List output(n);
  IVector<AsIndicesInPlace> res(1);
  for (int i = 0; i < n; ++i) {
    igraph_subcomponent(graph.data(), res.data(), cvids.at(i), static_cast<igraph_neimode_t>(mode));
    output[i] = res.wrap();
  }
  return output;
}

// [[Rcpp::export]]
IGraph induced_subgraph_(const IGraph& other, const Rcpp::IntegerVector& vids, int impl) {
  return IGraph(other, vids, impl);
}

IGraph::IGraph(const IGraph& other, const Rcpp::IntegerVector& vids, int impl): IGraph::IGraph() {
  igraph_induced_subgraph(
    other.data_.get(), data_.get(), ISelectorInPlace(vids).vss(),
    static_cast<igraph_subgraph_implementation_t>(impl));
  init_attr();
}
