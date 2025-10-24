// <https://igraph.org/c/html/latest/igraph-Isomorphism.html>
#include "igraph.hpp"

#include "vector.hpp"

#include <igraph/igraph_isomorphism.h>

[[cpp11::register]] bool
isomorphic_(const cpp11::external_pointer<IGraph>& graph1,
            const cpp11::external_pointer<IGraph>& graph2) {
  igraph_bool_t res;
  igraph_isomorphic(graph1->data(), graph2->data(), &res);
  return res;
}

[[cpp11::register]] bool
subisomorphic_(const cpp11::external_pointer<IGraph>& graph1,
               const cpp11::external_pointer<IGraph>& graph2) {
  igraph_bool_t res;
  igraph_subisomorphic(graph1->data(), graph2->data(), &res);
  return res;
}

[[cpp11::register]] SEXP
canonical_permutation_(const cpp11::external_pointer<IGraph>& graph,
    const cpp11::integers& colors) {
  IVector<AsIndices> labeling(graph->vcount());
  igraph_canonical_permutation(
    graph->data(),
    colors.empty() ? nullptr : IVectorIntView(colors).data(),
    labeling.data());
  return labeling.wrap();
}
