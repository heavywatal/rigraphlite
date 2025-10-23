// <https://igraph.org/c/doc/igraph-Structural.html#shortest-path-related-functions>
#include "igraph.hpp"

#include "vector.hpp"
#include "matrix.hpp"

#include <igraph/igraph_paths.h>

#include <map>


[[cpp11::register]] SEXP
distances_(
  const cpp11::external_pointer<IGraph> graph, const cpp11::doubles& weights,
  const cpp11::integers& from, const cpp11::integers& to, const int mode, const double cutoff) {

  const int from_size = from.size();
  const int to_size = to.size();
  const int nrow = from_size > 0 ? from_size : graph->vcount();
  const int ncol = to_size > 0 ? to_size : graph->vcount();
  IMatrix res(nrow, ncol);
  if (cutoff > 0.0) {
    igraph_distances_cutoff(graph->data(),
      weights.size() ? IVectorView(weights).data() : nullptr,
      res.data(),
      from_size > 0 ? ISelector(from).vss() : igraph_vss_all(),
      to_size > 0 ? ISelector(to).vss() : igraph_vss_all(),
      static_cast<igraph_neimode_t>(mode), cutoff);
  } else {
    igraph_distances(graph->data(),
      weights.size() ? IVectorView(weights).data() : nullptr,
      res.data(),
      from_size > 0 ? ISelector(from).vss() : igraph_vss_all(),
      to_size > 0 ? ISelector(to).vss() : igraph_vss_all(),
      static_cast<igraph_neimode_t>(mode));
  }
  return res.wrap();
}

[[cpp11::register]] SEXP
get_shortest_paths_(
  const cpp11::external_pointer<IGraph> graph, const cpp11::doubles& weights,
  int from, const cpp11::integers& to, int mode) {
  const int to_size = to.size();
  IVectorIntList<AsIndices> res;
  res.reserve(to_size > 0 ? to_size : graph->vcount());
  igraph_get_shortest_paths(
    graph->data(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    res.data(), nullptr,
    --from,
    to_size > 0 ? ISelectorInPlace(to).vss() : igraph_vss_all(),
    static_cast<igraph_neimode_t>(mode),
    nullptr, nullptr);
  return res.wrap();
}

[[cpp11::register]] SEXP
get_all_shortest_paths_(
  const cpp11::external_pointer<IGraph> graph, const cpp11::doubles& weights,
  int from, const cpp11::integers& to, int mode) {

  const int to_size = to.size();
  IVectorIntList<AsIndices> res;
  res.reserve(to_size > 0 ? to_size : graph->vcount());
  igraph_get_all_shortest_paths(
    graph->data(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    res.data(), nullptr, nullptr, --from,
    to_size > 0 ? ISelectorInPlace(to).vss() : igraph_vss_all(),
    static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

[[cpp11::register]] SEXP
get_all_simple_paths_(
  const cpp11::external_pointer<IGraph> graph,
  int from, const cpp11::integers& to, int mode,
  const int minlen, const int maxlen, const int max_results) {

  const int to_size = to.size();
  IVectorIntList<AsIndices> res;
  igraph_get_all_simple_paths(
    graph->data(), res.data(), --from,
    to_size > 0 ? ISelectorInPlace(to).vss() : igraph_vss_all(),
    static_cast<igraph_neimode_t>(mode),
    minlen, maxlen, max_results);
  return res.wrap();
}

[[cpp11::register]]
double
average_path_length_(
  const cpp11::external_pointer<IGraph> graph,
  const cpp11::doubles& weights, bool directed, bool unconn) {
  double res;
  igraph_average_path_length(graph->data(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    &res, nullptr, directed, unconn);
  return res;
}

[[cpp11::register]] SEXP
path_length_hist_(const cpp11::external_pointer<IGraph> graph, bool directed) {
  cpp11::writable::doubles values(std::log2(graph->vcount()) * 2);
  IVectorView res(values); // rough estimate; resized as needed
  igraph_path_length_hist(graph->data(), res.data(), nullptr, directed);
  return res.wrap();
}

[[cpp11::register]] SEXP
eccentricity_(const cpp11::external_pointer<IGraph> graph,
  const cpp11::doubles& weights,
  const cpp11::integers& vids,
  const int mode) {
  const int n = vids.size();
  IVector<AsValues, InitSize> res(n > 0 ? n : graph->vcount());
  igraph_eccentricity(graph->data(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    res.data(),
    n > 0 ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

[[cpp11::register]] double
diameter_(const cpp11::external_pointer<IGraph> graph,
  const cpp11::doubles& weights,
  bool directed, bool unconn) {
  double res;
  igraph_diameter(graph->data(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    &res, nullptr, nullptr, nullptr, nullptr, directed, unconn);
  return res;
}

[[cpp11::register]] double
radius_(const cpp11::external_pointer<IGraph> graph,
  const cpp11::doubles& weights,
  const int mode) {
  double res;
  igraph_radius(graph->data(),
    weights.size() ? IVectorView(weights).data() : nullptr,
    &res,
    static_cast<igraph_neimode_t>(mode));
  return res;
}

[[cpp11::register]] double
global_efficiency_(
    const cpp11::external_pointer<IGraph> graph,
    const cpp11::doubles& weights,
    const bool directed) {
  double res;
  igraph_global_efficiency(graph->data(),
    weights.empty() ? nullptr: IVectorView(weights).data(),
    &res,
    directed);
  return res;
}

[[cpp11::register]] SEXP
local_efficiency_(
    const cpp11::external_pointer<IGraph> graph,
    const cpp11::doubles& weights,
    const cpp11::integers& vids,
    const bool directed,
    const int mode) {
  const int n = vids.size();
  IVector<AsValues, InitSize> res(n > 0 ? n : graph->vcount());
  igraph_local_efficiency(graph->data(),
    weights.empty() ? nullptr: IVectorView(weights).data(),
    res.data(),
    vids.empty() ? igraph_vss_all() : ISelectorInPlace(vids).vss(),
    directed, static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

[[cpp11::register]] double
average_local_efficiency_(
    const cpp11::external_pointer<IGraph> graph,
    const cpp11::doubles& weights,
    const bool directed,
    const int mode) {
  double res;
  igraph_average_local_efficiency(graph->data(),
    weights.empty() ? nullptr: IVectorView(weights).data(),
    &res,
    directed, static_cast<igraph_neimode_t>(mode));
  return res;
}

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
// experimental

[[cpp11::register]] double
mean_distances_cpp_(
  const cpp11::external_pointer<IGraph> graph, const cpp11::doubles& weights,
  const cpp11::integers& from, const cpp11::integers& to, int mode) {

  const auto weights_data = weights.size() ? IVectorView(weights).data() : nullptr;
  const int from_size = from.size();
  const int true_from_size = from_size > 0 ? from_size : graph->vcount();
  const int to_size = to.size();
  IMatrix res(1, to_size > 0 ? to_size : graph->vcount());
  double total = 0.0;
  int num_paths = 0;
  for (int i = 0; i < true_from_size; ++i) {
    igraph_distances(graph->data(),
      weights_data,
      res.data(),
      igraph_vss_1(from_size > 0 ? from.at(i) - 1 : i),
      to_size > 0 ? ISelector(to).vss() : igraph_vss_all(),
      static_cast<igraph_neimode_t>(mode));
    const auto& v = res.data()->data;
    for (auto p = v.stor_begin; p < v.end; ++p) {
      if ((*p != 0) && (*p != IGRAPH_INFINITY)) {
        total += *p;
        ++num_paths;
      }
    }
  }
  return total / num_paths;
}

[[cpp11::register]] SEXP
path_length_count_within(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids) {
  std::map<int, int> counter;
  IMatrix res(1, 1);
  for (const int i: vids) {
    auto vs_i = igraph_vss_1(i - 1);
    for (const int j: vids) {
      if (i <= j) continue;
      igraph_distances(graph->data(), nullptr, res.data(), vs_i, igraph_vss_1(j - 1), IGRAPH_ALL);
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

[[cpp11::register]] SEXP
path_length_count_between(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& from, const cpp11::integers& to) {
  std::map<int, int> counter;
  IMatrix res(1, 1);
  for (const int i: from) {
    auto vs_i = igraph_vss_1(i - 1);
    for (const int j: to) {
      igraph_distances(graph->data(), nullptr, res.data(), vs_i, igraph_vss_1(j - 1), IGRAPH_ALL);
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
