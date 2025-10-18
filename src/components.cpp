#include "igraph.hpp"

#include "vector.hpp"

#include <igraph/igraph_components.h>
#include <igraph/igraph_reachability.h>

[[cpp11::register]] SEXP
connected_components_(const cpp11::external_pointer<IGraph> graph, const int mode) {
  IVector<AsIndices> membership(graph->vcount());
  igraph_connected_components(graph->data(), membership.data(),
    nullptr, nullptr, static_cast<igraph_connectedness_t>(mode));
  return membership.wrap();
}

[[cpp11::register]] bool
is_connected_(const cpp11::external_pointer<IGraph> graph, const int mode) {
  igraph_bool_t res;
  igraph_is_connected(graph->data(), &res, static_cast<igraph_connectedness_t>(mode));
  return res;
}

[[cpp11::register]] SEXP
count_reachable_(const cpp11::external_pointer<IGraph> graph, const int mode) {
  IVector<AsValues> res(graph->vcount());
  igraph_count_reachable(graph->data(), res.data(), static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

[[cpp11::register]] SEXP
transitive_closure_(const cpp11::external_pointer<IGraph> graph) {
  cpp11::external_pointer<IGraph> p(new IGraph());
  igraph_transitive_closure(graph->data(), p->data());
  p->init_attr();
  return p;
}

[[cpp11::register]] SEXP
articulation_points_(const cpp11::external_pointer<IGraph> graph) {
  IVector<AsIndices> res(graph->vcount());
  igraph_articulation_points(graph->data(), res.data());
  return res.wrap();
}

[[cpp11::register]] SEXP
bridges_(const cpp11::external_pointer<IGraph> graph) {
  IVector<AsIndices> res(graph->ecount());
  igraph_bridges(graph->data(), res.data());
  return res.wrap();
}

[[cpp11::register]] bool
is_biconnected_(const cpp11::external_pointer<IGraph> graph) {
  igraph_bool_t res;
  igraph_is_biconnected(graph->data(), &res);
  return res;
}
