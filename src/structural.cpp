#include "igraph.hpp"

#include "vector.hpp"
#include "matrix.hpp"

#include <igraph/igraph_structural.h>
#include <igraph/igraph_operators.h>
#include <igraph/igraph_paths.h>
#include <igraph/igraph_neighborhood.h>

#include <map>

cpp11::logicals
IGraph::are_adjacent(int v1, int v2) const {
  igraph_bool_t res;
  igraph_are_adjacent(data_.get(), --v1, --v2, &res);
  return cpp11::logicals({cpp11::r_bool(res)});
}

namespace sugar {
  inline cpp11::integers seq_len(const int n) {
    static auto seq_len = cpp11::package("base")["seq_len"];
    cpp11::sexp range = seq_len(cpp11::as_sexp(n));
    return cpp11::as_integers(range);
  }
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

cpp11::doubles_matrix<>
IGraph::distances(
  const cpp11::integers& from, const cpp11::integers& to,
  const cpp11::doubles& weights, int mode, const std::string& algorithm) const {

  const int from_size = from.size();
  const int to_size = to.size();
  const int nrow = from_size > 0 ? from_size : vcount();
  const int ncol = to_size > 0 ? to_size : vcount();
  IMatrix res(nrow, ncol);
  impl::distances(data_.get(), res.data(),
                  from_size > 0 ? ISelector(from).vss() : igraph_vss_all(),
                  to_size > 0 ? ISelector(to).vss() : igraph_vss_all(),
                  weights.size() ? IVectorView(weights).data() : nullptr,
                  static_cast<igraph_neimode_t>(mode), algorithm);
  if (from_size > 0) {
    res.rownames(cpp11::strings(from));
  }
  if (to_size > 0) {
    res.colnames(cpp11::strings(to));
  }
  return res.wrap();
}

// experimental
cpp11::doubles
IGraph::mean_distances(
  const cpp11::integers& from, const cpp11::integers& to,
  const cpp11::doubles& weights, int mode, const std::string& algorithm) const {

  const int to_size = to.size();
  const ISelector to_selector(to);
  const igraph_vs_t to_vss(to_size > 0 ? to_selector.vss() : igraph_vss_all());
  const igraph_vector_t* cweights = weights.size() ? IVectorView(weights).data() : nullptr;
  IMatrix res(1, to_size > 0 ? to_size : vcount());
  double total = 0.0;
  int num_paths = 0;
  for (const int from_i: from.size() > 0 ? from : sugar::seq_len(vcount())) {
    impl::distances(data_.get(), res.data(),
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
  return cpp11::doubles({total / num_paths});
}

cpp11::list
IGraph::get_shortest_paths(
  int from, const cpp11::integers& to,
  const cpp11::doubles& weights, int mode) const {

  const int to_size = to.size();
  IVectorIntList<AsIndicesInPlace> res(to_size > 0 ? to_size : vcount());
  res.init_elements();
  impl::get_shortest_paths(
    data_.get(), res.data(), --from,
    to_size > 0 ? ISelector(to).vss() : igraph_vss_all(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

cpp11::list
IGraph::get_all_shortest_paths(
  int from, const cpp11::integers& to,
  const cpp11::doubles& weights, int mode) const {

  const int to_size = to.size();
  IVectorIntList<AsIndicesInPlace> res(to_size > 0 ? to_size : vcount());
  res.init_elements();
  impl::get_all_shortest_paths(
    data_.get(), res.data(), --from,
    to_size > 0 ? ISelector(to).vss() : igraph_vss_all(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

cpp11::integers
IGraph::get_all_simple_paths(
  int from, const cpp11::integers& to, int cutoff, int mode) const {

  const int to_size = to.size();
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
  igraph_average_path_length(data_.get(), &res, nullptr, directed, true);
  return res;
}

cpp11::doubles
IGraph::path_length_hist(bool directed) const {
  cpp11::writable::doubles values(vcount());
  IVector<AsValues, InitView> res(values); // rough estimate; resized as needed
  double unconnected;
  igraph_path_length_hist(data_.get(), res.data(), &unconnected, directed);
  return res.wrap();
}

// [[cpp11::register]]
cpp11::integers
path_length_count_within(const IGraph& graph, const cpp11::integers& vids, bool directed) {
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
  cpp11::writable::integers output(max_len);
  for (const auto& p: counter) {
    output[p.first - 1] = p.second;
  }
  return output;
}

// [[cpp11::register]]
cpp11::integers
path_length_count_between(const IGraph& graph, const cpp11::integers& from, const cpp11::integers& to, bool directed) {
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
  cpp11::writable::integers output(max_len);
  for (const auto& p: counter) {
    output[p.first - 1] = p.second;
  }
  return output;
}

cpp11::integers
IGraph::neighborhood_size(const cpp11::integers& vids, const int order, const int mode, const int mindist) const {
  const int n = vids.size();
  IVector<AsValues> res(n);
  igraph_neighborhood_size(
    data_.get(), res.data(), n ? ISelectorInPlace(vids).vss() : igraph_vss_all(), order,
    static_cast<igraph_neimode_t>(mode), mindist);
  return res.wrap();
}

cpp11::list
IGraph::neighborhood(const cpp11::integers& vids, const int order, const int mode, const int mindist) const {
  const int n = vids.size();
  IVectorIntList<AsIndicesInPlace> res(n);
  igraph_neighborhood(
    data_.get(), res.data(), n ? ISelectorInPlace(vids).vss() : igraph_vss_all(), order,
    static_cast<igraph_neimode_t>(mode), mindist);
  return res.wrap();
}

cpp11::integers
IGraph::subcomponent(const int v, const int mode) const {
  IVector<AsIndicesInPlace> res(1);
  igraph_subcomponent(data_.get(), res.data(), v - 1, static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

// experimental
cpp11::list
IGraph::subcomponents(const cpp11::integers& vids, const int mode) const {
  const ISelector cvids(vids);
  const int n = vids.size();
  cpp11::writable::list output(n);
  IVector<AsIndicesInPlace> res(1);
  for (int i = 0; i < n; ++i) {
    igraph_subcomponent(data_.get(), res.data(), cvids.at(i), static_cast<igraph_neimode_t>(mode));
    output[i] = res.wrap();
  }
  return output;
}

IGraph::IGraph(const IGraph& other, const cpp11::integers& vids, int impl): IGraph::IGraph() {
  igraph_induced_subgraph(
    other.data_.get(), data_.get(), ISelectorInPlace(vids).vss(),
    static_cast<igraph_subgraph_implementation_t>(impl));
  init_attr();
}
