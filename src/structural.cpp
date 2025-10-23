#include "igraph.hpp"

#include "vector.hpp"

#include <igraph/igraph_structural.h>
#include <igraph/igraph_neighborhood.h>

[[cpp11::register]]
bool
are_adjacent_(const cpp11::external_pointer<IGraph> graph, int v1, int v2) {
  igraph_bool_t res;
  igraph_are_adjacent(graph->data(), --v1, --v2, &res);
  return res;
}

[[cpp11::register]] bool
is_simple_(const cpp11::external_pointer<IGraph> graph, const bool directed) {
  igraph_bool_t res;
  igraph_is_simple(graph->data(), &res, directed);
  return res;
}

[[cpp11::register]] bool
is_acyclic_(const cpp11::external_pointer<IGraph> graph) {
  igraph_bool_t res;
  igraph_is_acyclic(graph->data(), &res);
  return res;
}

[[cpp11::register]] bool
has_loop_(const cpp11::external_pointer<IGraph> graph) {
  igraph_bool_t res;
  igraph_has_loop(graph->data(), &res);
  return res;
}

[[cpp11::register]] int
count_loops_(const cpp11::external_pointer<IGraph> graph) {
  int res;
  igraph_count_loops(graph->data(), &res);
  return res;
}

[[cpp11::register]] bool
has_multiple_(const cpp11::external_pointer<IGraph> graph) {
  igraph_bool_t res;
  igraph_has_multiple(graph->data(), &res);
  return res;
}

[[cpp11::register]] SEXP
count_multiple_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& eids) {
  const int n = eids.size();
  IVector<AsValues> res(n > 0 ? n : graph->ecount());
  igraph_count_multiple(graph->data(), res.data(),
    n > 0 ? ISelectorInPlace(eids).ess() : igraph_ess_all(igraph_edgeorder_type_t::IGRAPH_EDGEORDER_ID));
  return res.wrap();
}

[[cpp11::register]] double
girth_(const cpp11::external_pointer<IGraph> graph) {
  double res;
  igraph_girth(graph->data(), &res, nullptr);
  return res;
}

[[cpp11::register]] SEXP
neighborhood_size_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids, const int order, const int mode, const int mindist) {
  const int n = vids.size();
  IVector<AsValues> res(n > 0 ? n : graph->vcount());
  igraph_neighborhood_size(
    graph->data(), res.data(),
    n > 0 ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    order, static_cast<igraph_neimode_t>(mode), mindist);
  return res.wrap();
}

[[cpp11::register]] SEXP
neighborhood_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids, const int order, const int mode, const int mindist) {
  const int n = vids.size();
  IVectorIntList<AsIndices> res;
  res.reserve(n > 0 ? n : graph->vcount());
  igraph_neighborhood(
    graph->data(), res.data(),
    n > 0 ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    order, static_cast<igraph_neimode_t>(mode), mindist);
  return res.wrap();
}

[[cpp11::register]] SEXP
subcomponent_(const cpp11::external_pointer<IGraph> graph, const int v, const int mode) {
  IVector<AsIndices> res(1);
  igraph_subcomponent(graph->data(), res.data(), v - 1, static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

[[cpp11::register]] int
maxdegree_(const cpp11::external_pointer<IGraph> graph,
    const cpp11::integers& vids,
    const int mode,
    const int loops) {
  const int n = vids.size();
  int res;
  igraph_maxdegree(graph->data(), &res,
    n > 0 ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    static_cast<igraph_neimode_t>(mode),
    static_cast<igraph_loops_t>(loops));
  return res;
}

[[cpp11::register]] SEXP
strength_(const cpp11::external_pointer<IGraph> graph,
    const cpp11::integers& vids,
    const int mode,
    const int loops,
    const cpp11::doubles& weights) {
  const int n = vids.size();
  IVector<AsValues, InitSize> res(n > 0 ? n : graph->vcount());
  igraph_strength(graph->data(), res.data(),
    n > 0 ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    static_cast<igraph_neimode_t>(mode),
    static_cast<igraph_loops_t>(loops),
    weights.size() ? IVectorView(weights).data() : nullptr);
  return res.wrap();
}

// experimental
[[cpp11::register]] SEXP
subcomponents_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids, const int mode) {
  const ISelectorInPlace cvids(vids);
  const int n = vids.size();
  cpp11::writable::list output(n);
  IVector<AsIndices> res(1);
  for (int i = 0; i < n; ++i) {
    igraph_subcomponent(graph->data(), res.data(), cvids.at(i), static_cast<igraph_neimode_t>(mode));
    output[i] = res.wrap();
  }
  return output;
}
