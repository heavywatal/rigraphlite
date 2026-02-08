// <https://igraph.org/c/doc/igraph-Cliques.html>
#include "igraph.hpp"
#include "vector.hpp"

#include <igraph/igraph_cliques.h>

[[cpp11::register]] SEXP
cliques_(const cpp11::external_pointer<IGraph> graph,
    const int min_size, const int max_size, const int max_results) {
  IVectorIntList<AsIndices> res;
  igraph_cliques(graph->data(), res.data(), min_size, max_size, max_results);
  return res.wrap();
}

[[cpp11::register]] SEXP
clique_size_hist_(const cpp11::external_pointer<IGraph> graph,
    const int min_size, const int max_size) {
  IVector<AsValues, InitSize> res(max_size > 0 ? max_size + 1 : 0);
  igraph_clique_size_hist(graph->data(), res.data(), min_size, max_size);
  return res.wrap();
}

[[cpp11::register]] SEXP
largest_cliques_(const cpp11::external_pointer<IGraph> graph) {
  IVectorIntList<AsIndices> res;
  igraph_largest_cliques(graph->data(), res.data());
  return res.wrap();
}

[[cpp11::register]] SEXP
maximal_cliques_(const cpp11::external_pointer<IGraph> graph,
    const int min_size, const int max_size, const int max_results) {
  IVectorIntList<AsIndices> res;
  igraph_maximal_cliques(graph->data(), res.data(), min_size, max_size, max_results);
  return res.wrap();
}

[[cpp11::register]] int
maximal_cliques_count_(const cpp11::external_pointer<IGraph> graph,
    const int min_size, const int max_size) {
  igraph_int_t res;
  igraph_maximal_cliques_count(graph->data(), &res, min_size, max_size);
  return res;
}

[[cpp11::register]] SEXP
maximal_cliques_hist_(const cpp11::external_pointer<IGraph> graph,
    const int min_size, const int max_size) {
  IVector<AsValues, InitSize> res(max_size > 0 ? max_size + 1 : 0);
  igraph_maximal_cliques_hist(graph->data(), res.data(), min_size, max_size);
  return res.wrap();
}

[[cpp11::register]] int
clique_number_(const cpp11::external_pointer<IGraph> graph) {
  igraph_int_t res;
  igraph_clique_number(graph->data(), &res);
  return res;
}

[[cpp11::register]] SEXP
independent_vertex_sets_(const cpp11::external_pointer<IGraph> graph,
    const int min_size, const int max_size, const int max_results) {
  IVectorIntList<AsIndices> res;
  igraph_independent_vertex_sets(graph->data(), res.data(), min_size, max_size, max_results);
  return res.wrap();
}

[[cpp11::register]] SEXP
largest_independent_vertex_sets_(const cpp11::external_pointer<IGraph> graph) {
  IVectorIntList<AsIndices> res;
  igraph_largest_independent_vertex_sets(graph->data(), res.data());
  return res.wrap();
}

[[cpp11::register]] SEXP
maximal_independent_vertex_sets_(const cpp11::external_pointer<IGraph> graph,
    const int min_size, const int max_size, const int max_results) {
  IVectorIntList<AsIndices> res;
  igraph_maximal_independent_vertex_sets(graph->data(), res.data(), min_size, max_size, max_results);
  return res.wrap();
}

[[cpp11::register]] int
independence_number_(const cpp11::external_pointer<IGraph> graph) {
  igraph_int_t res;
  igraph_independence_number(graph->data(), &res);
  return res;
}
