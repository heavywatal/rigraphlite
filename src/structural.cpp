#include "igraph.hpp"

#include "vector.hpp"
#include "matrix.hpp"

#include <igraph/igraph_structural.h>
#include <igraph/igraph_paths.h>
#include <igraph/igraph_neighborhood.h>

Rcpp::LogicalVector
IGraph::are_connected(int v1, int v2) const {
  igraph_bool_t res;
  igraph_are_connected(data_.get(), --v1, --v2, &res);
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

  inline void get_shortest_paths(
    const igraph_t* graph, igraph_vector_ptr_t* res,
    igraph_integer_t from, igraph_vs_t&& to,
    const igraph_vector_t* weights, igraph_neimode_t mode) {

    if (weights) {
      igraph_get_shortest_paths_dijkstra(graph, res, nullptr, from, std::move(to), weights, mode, nullptr, nullptr);
    } else {
      igraph_get_shortest_paths(graph, res, nullptr, from, std::move(to), mode, nullptr, nullptr);
    }
  }

  inline void get_all_shortest_paths(
    const igraph_t* graph, igraph_vector_ptr_t* res,
    igraph_integer_t from, igraph_vs_t&& to,
    const igraph_vector_t* weights, igraph_neimode_t mode) {

    if (weights) {
      igraph_get_all_shortest_paths_dijkstra(graph, res, nullptr, from, std::move(to), weights, mode);
    } else {
      igraph_get_all_shortest_paths(graph, res, nullptr, from, std::move(to), mode);
    }
  }
}

Rcpp::NumericMatrix
IGraph::shortest_paths(
  const Rcpp::NumericVector& from, const Rcpp::NumericVector& to,
  const Rcpp::NumericVector& weights, int mode, const std::string& algorithm) const {

  const long from_size = from.size();
  const long to_size = to.size();
  const long nrow = from_size > 0 ? from_size : vcount();
  const long ncol = to_size > 0 ? to_size : vcount();
  IMatrix res(nrow, ncol);
  impl::shortest_paths(data_.get(), res.data(),
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
Rcpp::NumericVector
IGraph::mean_distances(
  const Rcpp::NumericVector& from, const Rcpp::NumericVector& to,
  const Rcpp::NumericVector& weights, int mode, const std::string& algorithm) const {

  const long from_size = from.size();
  const long to_size = to.size();
  const Rcpp::IntegerVector cfrom = (from_size > 0 ? Rcpp::as<Rcpp::IntegerVector>(from) : V()) - 1;
  const ISelector to_selector(to);
  const igraph_vs_t to_vss(to_size > 0 ? to_selector.vss() : igraph_vss_all());
  const igraph_vector_t* cweights = weights.size() ? IVectorView(weights).data() : nullptr;
  IMatrix res(1, to_size > 0 ? to_size : vcount());
  double total = 0.0;
  long num_paths = 0;
  for (const int from_i: cfrom) {
    impl::shortest_paths(data_.get(), res.data(),
                         igraph_vss_1(from_i), to_vss, cweights,
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

Rcpp::List
IGraph::get_shortest_paths(
  int from, const Rcpp::NumericVector& to,
  const Rcpp::NumericVector& weights, int mode) const {

  const long to_size = to.size();
  IVectorPtr<AsIndicesInPlace> res(to_size > 0 ? to_size : vcount());
  res.init_elements();
  impl::get_shortest_paths(
    data_.get(), res.data(), --from,
    to_size > 0 ? ISelector(to).vss() : igraph_vss_all(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

Rcpp::List
IGraph::get_all_shortest_paths(
  int from, const Rcpp::NumericVector& to,
  const Rcpp::NumericVector& weights, int mode) const {

  const long to_size = to.size();
  IVectorPtr<AsIndicesInPlace> res(to_size > 0 ? to_size : vcount());
  res.init_elements();
  impl::get_all_shortest_paths(
    data_.get(), res.data(), --from,
    to_size > 0 ? ISelector(to).vss() : igraph_vss_all(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

Rcpp::IntegerVector
IGraph::get_all_simple_paths(
  int from, const Rcpp::NumericVector& to, int cutoff, int mode) const {

  const long to_size = to.size();
  IVector<AsIndicesInPlace, InitSizeInt> res(to_size > 0 ? to_size : vcount());
  igraph_get_all_simple_paths(
    data_.get(), res.data(), --from,
    to_size > 0 ? ISelector(to).vss() : igraph_vss_all(),
    cutoff,
    static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

double
IGraph::average_path_length(bool directed) const {
  double res;
  igraph_average_path_length(data_.get(), &res, directed, true);
  return res;
}

Rcpp::NumericVector
IGraph::path_length_hist(bool directed) const {
  IVector<AsValues> res(vcount()); // rough estimate; resized as needed
  double unconnected;
  igraph_path_length_hist(data_.get(), res.data(), &unconnected, directed);
  return res.wrap();
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
  const long n = vids.size();
  IVector<AsValues> res(n);
  igraph_neighborhood_size(
    data_.get(), res.data(), n ? ISelectorInPlace(vids).vss() : igraph_vss_all(), order,
    static_cast<igraph_neimode_t>(mode), mindist);
  return res.wrap();
}

Rcpp::List
IGraph::neighborhood(const Rcpp::NumericVector& vids, const int order, const int mode, const int mindist) const {
  const long n = vids.size();
  IVectorPtr<AsIndicesInPlace> res(n);
  igraph_neighborhood(
    data_.get(), res.data(), n ? ISelectorInPlace(vids).vss() : igraph_vss_all(), order,
    static_cast<igraph_neimode_t>(mode), mindist);
  return res.wrap();
}

Rcpp::NumericVector
IGraph::subcomponent(const double v, const int mode) const {
  IVector<AsIndicesInPlace> res(1);
  igraph_subcomponent(data_.get(), res.data(), v - 1.0, static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

// experimental
Rcpp::List
IGraph::subcomponents(const Rcpp::NumericVector& vids, const int mode) const {
  const ISelector cvids(vids);
  const long n = vids.size();
  Rcpp::List output(n);
  IVector<AsIndicesInPlace> res(1);
  for (long i = 0; i < n; ++i) {
    igraph_subcomponent(data_.get(), res.data(), cvids.at(i), static_cast<igraph_neimode_t>(mode));
    output[i] = res.wrap();
  }
  return output;
}

IGraph::IGraph(const IGraph& other, const Rcpp::NumericVector& vids, int impl): IGraph::IGraph() {
  igraph_induced_subgraph(
    other.data_.get(), data_.get(), ISelectorInPlace(vids).vss(),
    static_cast<igraph_subgraph_implementation_t>(impl));
  init_attr();
}
