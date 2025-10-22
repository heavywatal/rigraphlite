// <https://igraph.org/c/html/latest/igraph-Games.html>
#include "igraph.hpp"
#include "vector.hpp"

#include <igraph/igraph_games.h>

[[cpp11::register]] SEXP
erdos_renyi_game_gnm_(const int n, const int m, const bool directed = 0,
    const int edge_type_sw = 0) {
  cpp11::external_pointer<IGraph> p(new IGraph());
  igraph_erdos_renyi_game_gnm(p->data(), n, m, directed, edge_type_sw, IGRAPH_EDGE_UNLABELED);
  p->init_attr();
  return p;
}

[[cpp11::register]] SEXP
erdos_renyi_game_gnp_(const int n, const double p_, const bool directed = 0,
    const int edge_type_sw = 0) {
  cpp11::external_pointer<IGraph> p(new IGraph());
  igraph_erdos_renyi_game_gnp(p->data(), n, p_, directed, edge_type_sw, IGRAPH_EDGE_UNLABELED);
  p->init_attr();
  return p;
}

[[cpp11::register]] SEXP
degree_sequence_game_(const cpp11::integers& out_degrees,
    const cpp11::integers& in_degrees,
    const int method = 0) {
  cpp11::external_pointer<IGraph> p(new IGraph());
  igraph_degree_sequence_game(p->data(),
      IVector<AsValues, InitViewInt>(out_degrees).data(),
      in_degrees.empty() ? nullptr : IVector<AsValues, InitViewInt>(in_degrees).data(),
      static_cast<igraph_degseq_t>(method));
  p->init_attr();
  return p;
}

[[cpp11::register]] SEXP
k_regular_game_(const int n, const int k,
    const bool directed = false,
    const bool multiple = false) {
  cpp11::external_pointer<IGraph> p(new IGraph());
  igraph_k_regular_game(p->data(), n, k, directed, multiple);
  p->init_attr();
  return p;
}

[[cpp11::register]] SEXP
watts_strogatz_game_(const int dim,
    const int size,
    const int nei,
    const double prob,
    const int edge_type_sw = 0) {
  cpp11::external_pointer<IGraph> p(new IGraph());
  igraph_watts_strogatz_game(p->data(), dim, size, nei, prob, edge_type_sw);
  p->init_attr();
  return p;
}

[[cpp11::register]] void
rewire_edges_(const cpp11::external_pointer<IGraph> graph, const double prob,
    const int edge_type_sw = 0) {
  igraph_rewire_edges(graph->data(), prob, edge_type_sw);
}
