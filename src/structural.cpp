#include "igraph.hpp"

#include "vector.hpp"
#include "matrix.hpp"

#include <igraph/igraph_structural.h>
#include <igraph/igraph_neighborhood.h>

[[cpp11::register]]
bool
are_adjacent_(const cpp11::external_pointer<IGraph> graph, int v1, int v2) {
  igraph_bool_t res;
  igraph_are_adjacent(graph->data(), --v1, --v2, &res);
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
