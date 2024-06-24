// Generated by cpp11: do not edit by hand
// clang-format off

#include "igraphlite_types.h"
#include "cpp11/declarations.hpp"
#include <R_ext/Visibility.h>

// attributes.cpp
SEXP V_(const cpp11::external_pointer<IGraph> graph);
extern "C" SEXP _igraphlite_V_(SEXP graph) {
  BEGIN_CPP11
    return cpp11::as_sexp(V_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph)));
  END_CPP11
}
// attributes.cpp
SEXP E_(const cpp11::external_pointer<IGraph> graph);
extern "C" SEXP _igraphlite_E_(SEXP graph) {
  BEGIN_CPP11
    return cpp11::as_sexp(E_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph)));
  END_CPP11
}
// attributes.cpp
SEXP Vnames_(const cpp11::external_pointer<IGraph> graph);
extern "C" SEXP _igraphlite_Vnames_(SEXP graph) {
  BEGIN_CPP11
    return cpp11::as_sexp(Vnames_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph)));
  END_CPP11
}
// attributes.cpp
SEXP from_(const cpp11::external_pointer<IGraph> graph);
extern "C" SEXP _igraphlite_from_(SEXP graph) {
  BEGIN_CPP11
    return cpp11::as_sexp(from_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph)));
  END_CPP11
}
// attributes.cpp
SEXP to_(const cpp11::external_pointer<IGraph> graph);
extern "C" SEXP _igraphlite_to_(SEXP graph) {
  BEGIN_CPP11
    return cpp11::as_sexp(to_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph)));
  END_CPP11
}
// attributes.cpp
SEXP getVattr_(const cpp11::external_pointer<IGraph> graph);
extern "C" SEXP _igraphlite_getVattr_(SEXP graph) {
  BEGIN_CPP11
    return cpp11::as_sexp(getVattr_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph)));
  END_CPP11
}
// attributes.cpp
SEXP getEattr_(const cpp11::external_pointer<IGraph> graph);
extern "C" SEXP _igraphlite_getEattr_(SEXP graph) {
  BEGIN_CPP11
    return cpp11::as_sexp(getEattr_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph)));
  END_CPP11
}
// attributes.cpp
void setVattr_(cpp11::external_pointer<IGraph> graph, SEXP other);
extern "C" SEXP _igraphlite_setVattr_(SEXP graph, SEXP other) {
  BEGIN_CPP11
    setVattr_(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<SEXP>>(other));
    return R_NilValue;
  END_CPP11
}
// attributes.cpp
void setEattr_(cpp11::external_pointer<IGraph> graph, SEXP other);
extern "C" SEXP _igraphlite_setEattr_(SEXP graph, SEXP other) {
  BEGIN_CPP11
    setEattr_(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<SEXP>>(other));
    return R_NilValue;
  END_CPP11
}
// basic.cpp
int vcount_(const cpp11::external_pointer<IGraph> graph);
extern "C" SEXP _igraphlite_vcount_(SEXP graph) {
  BEGIN_CPP11
    return cpp11::as_sexp(vcount_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph)));
  END_CPP11
}
// basic.cpp
int ecount_(const cpp11::external_pointer<IGraph> graph);
extern "C" SEXP _igraphlite_ecount_(SEXP graph) {
  BEGIN_CPP11
    return cpp11::as_sexp(ecount_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph)));
  END_CPP11
}
// basic.cpp
bool is_directed_(const cpp11::external_pointer<IGraph> graph);
extern "C" SEXP _igraphlite_is_directed_(SEXP graph) {
  BEGIN_CPP11
    return cpp11::as_sexp(is_directed_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph)));
  END_CPP11
}
// basic.cpp
SEXP edge_(const cpp11::external_pointer<IGraph> graph, int eid);
extern "C" SEXP _igraphlite_edge_(SEXP graph, SEXP eid) {
  BEGIN_CPP11
    return cpp11::as_sexp(edge_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<int>>(eid)));
  END_CPP11
}
// basic.cpp
SEXP neighbors_(const cpp11::external_pointer<IGraph> graph, int node, const int mode);
extern "C" SEXP _igraphlite_neighbors_(SEXP graph, SEXP node, SEXP mode) {
  BEGIN_CPP11
    return cpp11::as_sexp(neighbors_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<int>>(node), cpp11::as_cpp<cpp11::decay_t<const int>>(mode)));
  END_CPP11
}
// basic.cpp
SEXP incident_(const cpp11::external_pointer<IGraph> graph, int node, const int mode);
extern "C" SEXP _igraphlite_incident_(SEXP graph, SEXP node, SEXP mode) {
  BEGIN_CPP11
    return cpp11::as_sexp(incident_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<int>>(node), cpp11::as_cpp<cpp11::decay_t<const int>>(mode)));
  END_CPP11
}
// basic.cpp
SEXP degree_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids, const int mode, const bool loops);
extern "C" SEXP _igraphlite_degree_(SEXP graph, SEXP vids, SEXP mode, SEXP loops) {
  BEGIN_CPP11
    return cpp11::as_sexp(degree_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(vids), cpp11::as_cpp<cpp11::decay_t<const int>>(mode), cpp11::as_cpp<cpp11::decay_t<const bool>>(loops)));
  END_CPP11
}
// basic.cpp
void add_vertices_(cpp11::external_pointer<IGraph> graph, int n);
extern "C" SEXP _igraphlite_add_vertices_(SEXP graph, SEXP n) {
  BEGIN_CPP11
    add_vertices_(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<int>>(n));
    return R_NilValue;
  END_CPP11
}
// basic.cpp
void add_edges_(cpp11::external_pointer<IGraph> graph, const cpp11::integers& edges);
extern "C" SEXP _igraphlite_add_edges_(SEXP graph, SEXP edges) {
  BEGIN_CPP11
    add_edges_(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(edges));
    return R_NilValue;
  END_CPP11
}
// basic.cpp
void delete_edges_(cpp11::external_pointer<IGraph> graph, const cpp11::integers& eids);
extern "C" SEXP _igraphlite_delete_edges_(SEXP graph, SEXP eids) {
  BEGIN_CPP11
    delete_edges_(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(eids));
    return R_NilValue;
  END_CPP11
}
// basic.cpp
void delete_vertices_(cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids);
extern "C" SEXP _igraphlite_delete_vertices_(SEXP graph, SEXP vids) {
  BEGIN_CPP11
    delete_vertices_(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(vids));
    return R_NilValue;
  END_CPP11
}
// centrality.cpp
SEXP edge_betweenness_(const cpp11::external_pointer<IGraph> graph, const bool directed, const cpp11::doubles& weights);
extern "C" SEXP _igraphlite_edge_betweenness_(SEXP graph, SEXP directed, SEXP weights) {
  BEGIN_CPP11
    return cpp11::as_sexp(edge_betweenness_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const bool>>(directed), cpp11::as_cpp<cpp11::decay_t<const cpp11::doubles&>>(weights)));
  END_CPP11
}
// centrality.cpp
SEXP edge_betweenness_subset_(const cpp11::external_pointer<IGraph> graph, const bool directed, const cpp11::integers& eids, const cpp11::doubles& weights, const cpp11::integers& sources, const cpp11::integers& targets);
extern "C" SEXP _igraphlite_edge_betweenness_subset_(SEXP graph, SEXP directed, SEXP eids, SEXP weights, SEXP sources, SEXP targets) {
  BEGIN_CPP11
    return cpp11::as_sexp(edge_betweenness_subset_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const bool>>(directed), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(eids), cpp11::as_cpp<cpp11::decay_t<const cpp11::doubles&>>(weights), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(sources), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(targets)));
  END_CPP11
}
// data.cpp
SEXP as_adjlist_(const cpp11::external_pointer<IGraph> graph, const int mode, const int loops, const int multiple);
extern "C" SEXP _igraphlite_as_adjlist_(SEXP graph, SEXP mode, SEXP loops, SEXP multiple) {
  BEGIN_CPP11
    return cpp11::as_sexp(as_adjlist_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const int>>(mode), cpp11::as_cpp<cpp11::decay_t<const int>>(loops), cpp11::as_cpp<cpp11::decay_t<const int>>(multiple)));
  END_CPP11
}
// data.cpp
SEXP as_inclist_(const cpp11::external_pointer<IGraph> graph, const int mode, const int loops);
extern "C" SEXP _igraphlite_as_inclist_(SEXP graph, SEXP mode, SEXP loops) {
  BEGIN_CPP11
    return cpp11::as_sexp(as_inclist_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const int>>(mode), cpp11::as_cpp<cpp11::decay_t<const int>>(loops)));
  END_CPP11
}
// data.cpp
SEXP as_edgelist_(const cpp11::external_pointer<IGraph> graph);
extern "C" SEXP _igraphlite_as_edgelist_(SEXP graph) {
  BEGIN_CPP11
    return cpp11::as_sexp(as_edgelist_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph)));
  END_CPP11
}
// data.cpp
SEXP as_data_frame_(const cpp11::external_pointer<IGraph> graph);
extern "C" SEXP _igraphlite_as_data_frame_(SEXP graph) {
  BEGIN_CPP11
    return cpp11::as_sexp(as_data_frame_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph)));
  END_CPP11
}
// generators.cpp
SEXP graph_create_(const cpp11::integers& edges, int n, bool directed);
extern "C" SEXP _igraphlite_graph_create_(SEXP edges, SEXP n, SEXP directed) {
  BEGIN_CPP11
    return cpp11::as_sexp(graph_create_(cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(edges), cpp11::as_cpp<cpp11::decay_t<int>>(n), cpp11::as_cpp<cpp11::decay_t<bool>>(directed)));
  END_CPP11
}
// generators.cpp
SEXP graph_star_(int n, int mode, int center);
extern "C" SEXP _igraphlite_graph_star_(SEXP n, SEXP mode, SEXP center) {
  BEGIN_CPP11
    return cpp11::as_sexp(graph_star_(cpp11::as_cpp<cpp11::decay_t<int>>(n), cpp11::as_cpp<cpp11::decay_t<int>>(mode), cpp11::as_cpp<cpp11::decay_t<int>>(center)));
  END_CPP11
}
// generators.cpp
SEXP graph_lattice_(const cpp11::integers& dim, int nei, bool directed, bool mutual, bool circular);
extern "C" SEXP _igraphlite_graph_lattice_(SEXP dim, SEXP nei, SEXP directed, SEXP mutual, SEXP circular) {
  BEGIN_CPP11
    return cpp11::as_sexp(graph_lattice_(cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(dim), cpp11::as_cpp<cpp11::decay_t<int>>(nei), cpp11::as_cpp<cpp11::decay_t<bool>>(directed), cpp11::as_cpp<cpp11::decay_t<bool>>(mutual), cpp11::as_cpp<cpp11::decay_t<bool>>(circular)));
  END_CPP11
}
// generators.cpp
SEXP graph_ring_(int n, bool directed, bool mutual, bool circular);
extern "C" SEXP _igraphlite_graph_ring_(SEXP n, SEXP directed, SEXP mutual, SEXP circular) {
  BEGIN_CPP11
    return cpp11::as_sexp(graph_ring_(cpp11::as_cpp<cpp11::decay_t<int>>(n), cpp11::as_cpp<cpp11::decay_t<bool>>(directed), cpp11::as_cpp<cpp11::decay_t<bool>>(mutual), cpp11::as_cpp<cpp11::decay_t<bool>>(circular)));
  END_CPP11
}
// generators.cpp
SEXP graph_tree_(int n, int children, int mode);
extern "C" SEXP _igraphlite_graph_tree_(SEXP n, SEXP children, SEXP mode) {
  BEGIN_CPP11
    return cpp11::as_sexp(graph_tree_(cpp11::as_cpp<cpp11::decay_t<int>>(n), cpp11::as_cpp<cpp11::decay_t<int>>(children), cpp11::as_cpp<cpp11::decay_t<int>>(mode)));
  END_CPP11
}
// generators.cpp
SEXP graph_full_(int n, bool directed, bool loops);
extern "C" SEXP _igraphlite_graph_full_(SEXP n, SEXP directed, SEXP loops) {
  BEGIN_CPP11
    return cpp11::as_sexp(graph_full_(cpp11::as_cpp<cpp11::decay_t<int>>(n), cpp11::as_cpp<cpp11::decay_t<bool>>(directed), cpp11::as_cpp<cpp11::decay_t<bool>>(loops)));
  END_CPP11
}
// generators.cpp
SEXP graph_famous_(const char* name);
extern "C" SEXP _igraphlite_graph_famous_(SEXP name) {
  BEGIN_CPP11
    return cpp11::as_sexp(graph_famous_(cpp11::as_cpp<cpp11::decay_t<const char*>>(name)));
  END_CPP11
}
// generators.cpp
SEXP induced_subgraph_(const cpp11::external_pointer<IGraph> other, const cpp11::integers& vids, int impl);
extern "C" SEXP _igraphlite_induced_subgraph_(SEXP other, SEXP vids, SEXP impl) {
  BEGIN_CPP11
    return cpp11::as_sexp(induced_subgraph_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(other), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(vids), cpp11::as_cpp<cpp11::decay_t<int>>(impl)));
  END_CPP11
}
// generators.cpp
SEXP graph_from_edgelist_(const cpp11::sexp edgelist, bool directed);
extern "C" SEXP _igraphlite_graph_from_edgelist_(SEXP edgelist, SEXP directed) {
  BEGIN_CPP11
    return cpp11::as_sexp(graph_from_edgelist_(cpp11::as_cpp<cpp11::decay_t<const cpp11::sexp>>(edgelist), cpp11::as_cpp<cpp11::decay_t<bool>>(directed)));
  END_CPP11
}
// generators.cpp
SEXP graph_from_data_frame_(const cpp11::data_frame& df, bool directed);
extern "C" SEXP _igraphlite_graph_from_data_frame_(SEXP df, SEXP directed) {
  BEGIN_CPP11
    return cpp11::as_sexp(graph_from_data_frame_(cpp11::as_cpp<cpp11::decay_t<const cpp11::data_frame&>>(df), cpp11::as_cpp<cpp11::decay_t<bool>>(directed)));
  END_CPP11
}
// generators.cpp
SEXP graph_from_symbolic_edgelist_(const cpp11::sexp edgelist, bool directed);
extern "C" SEXP _igraphlite_graph_from_symbolic_edgelist_(SEXP edgelist, SEXP directed) {
  BEGIN_CPP11
    return cpp11::as_sexp(graph_from_symbolic_edgelist_(cpp11::as_cpp<cpp11::decay_t<const cpp11::sexp>>(edgelist), cpp11::as_cpp<cpp11::decay_t<bool>>(directed)));
  END_CPP11
}
// init.cpp
cpp11::r_string igraph_version_();
extern "C" SEXP _igraphlite_igraph_version_() {
  BEGIN_CPP11
    return cpp11::as_sexp(igraph_version_());
  END_CPP11
}
// init.cpp
void rng_seed(long seed);
extern "C" SEXP _igraphlite_rng_seed(SEXP seed) {
  BEGIN_CPP11
    rng_seed(cpp11::as_cpp<cpp11::decay_t<long>>(seed));
    return R_NilValue;
  END_CPP11
}
// layout.cpp
SEXP layout_random_(const cpp11::external_pointer<IGraph> graph);
extern "C" SEXP _igraphlite_layout_random_(SEXP graph) {
  BEGIN_CPP11
    return cpp11::as_sexp(layout_random_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph)));
  END_CPP11
}
// layout.cpp
SEXP layout_drl_(const cpp11::external_pointer<IGraph> graph);
extern "C" SEXP _igraphlite_layout_drl_(SEXP graph) {
  BEGIN_CPP11
    return cpp11::as_sexp(layout_drl_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph)));
  END_CPP11
}
// layout.cpp
SEXP layout_fruchterman_reingold_(const cpp11::external_pointer<IGraph> graph, int grid);
extern "C" SEXP _igraphlite_layout_fruchterman_reingold_(SEXP graph, SEXP grid) {
  BEGIN_CPP11
    return cpp11::as_sexp(layout_fruchterman_reingold_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<int>>(grid)));
  END_CPP11
}
// layout.cpp
SEXP layout_mds_(const cpp11::external_pointer<IGraph> graph, SEXP dist);
extern "C" SEXP _igraphlite_layout_mds_(SEXP graph, SEXP dist) {
  BEGIN_CPP11
    return cpp11::as_sexp(layout_mds_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<SEXP>>(dist)));
  END_CPP11
}
// layout.cpp
SEXP layout_reingold_tilford_(const cpp11::external_pointer<IGraph> graph, int mode, const cpp11::integers& roots);
extern "C" SEXP _igraphlite_layout_reingold_tilford_(SEXP graph, SEXP mode, SEXP roots) {
  BEGIN_CPP11
    return cpp11::as_sexp(layout_reingold_tilford_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<int>>(mode), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(roots)));
  END_CPP11
}
// layout.cpp
SEXP layout_reingold_tilford_circular_(const cpp11::external_pointer<IGraph> graph, int mode, const cpp11::integers& roots);
extern "C" SEXP _igraphlite_layout_reingold_tilford_circular_(SEXP graph, SEXP mode, SEXP roots) {
  BEGIN_CPP11
    return cpp11::as_sexp(layout_reingold_tilford_circular_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<int>>(mode), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(roots)));
  END_CPP11
}
// paths.cpp
SEXP distances_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& from, const cpp11::integers& to, const cpp11::doubles& weights, int mode, const std::string& algorithm);
extern "C" SEXP _igraphlite_distances_(SEXP graph, SEXP from, SEXP to, SEXP weights, SEXP mode, SEXP algorithm) {
  BEGIN_CPP11
    return cpp11::as_sexp(distances_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(from), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(to), cpp11::as_cpp<cpp11::decay_t<const cpp11::doubles&>>(weights), cpp11::as_cpp<cpp11::decay_t<int>>(mode), cpp11::as_cpp<cpp11::decay_t<const std::string&>>(algorithm)));
  END_CPP11
}
// paths.cpp
double mean_distances_cpp_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& from, const cpp11::integers& to, const cpp11::doubles& weights, int mode, const std::string& algorithm);
extern "C" SEXP _igraphlite_mean_distances_cpp_(SEXP graph, SEXP from, SEXP to, SEXP weights, SEXP mode, SEXP algorithm) {
  BEGIN_CPP11
    return cpp11::as_sexp(mean_distances_cpp_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(from), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(to), cpp11::as_cpp<cpp11::decay_t<const cpp11::doubles&>>(weights), cpp11::as_cpp<cpp11::decay_t<int>>(mode), cpp11::as_cpp<cpp11::decay_t<const std::string&>>(algorithm)));
  END_CPP11
}
// paths.cpp
SEXP get_shortest_paths_(const cpp11::external_pointer<IGraph> graph, int from, const cpp11::integers& to, const cpp11::doubles& weights, int mode);
extern "C" SEXP _igraphlite_get_shortest_paths_(SEXP graph, SEXP from, SEXP to, SEXP weights, SEXP mode) {
  BEGIN_CPP11
    return cpp11::as_sexp(get_shortest_paths_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<int>>(from), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(to), cpp11::as_cpp<cpp11::decay_t<const cpp11::doubles&>>(weights), cpp11::as_cpp<cpp11::decay_t<int>>(mode)));
  END_CPP11
}
// paths.cpp
SEXP get_all_shortest_paths_(const cpp11::external_pointer<IGraph> graph, int from, const cpp11::integers& to, const cpp11::doubles& weights, int mode);
extern "C" SEXP _igraphlite_get_all_shortest_paths_(SEXP graph, SEXP from, SEXP to, SEXP weights, SEXP mode) {
  BEGIN_CPP11
    return cpp11::as_sexp(get_all_shortest_paths_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<int>>(from), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(to), cpp11::as_cpp<cpp11::decay_t<const cpp11::doubles&>>(weights), cpp11::as_cpp<cpp11::decay_t<int>>(mode)));
  END_CPP11
}
// paths.cpp
SEXP get_all_simple_paths_(const cpp11::external_pointer<IGraph> graph, int from, const cpp11::integers& to, int cutoff, int mode);
extern "C" SEXP _igraphlite_get_all_simple_paths_(SEXP graph, SEXP from, SEXP to, SEXP cutoff, SEXP mode) {
  BEGIN_CPP11
    return cpp11::as_sexp(get_all_simple_paths_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<int>>(from), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(to), cpp11::as_cpp<cpp11::decay_t<int>>(cutoff), cpp11::as_cpp<cpp11::decay_t<int>>(mode)));
  END_CPP11
}
// paths.cpp
double average_path_length_(const cpp11::external_pointer<IGraph> graph, const cpp11::doubles& weights, bool directed, bool unconn);
extern "C" SEXP _igraphlite_average_path_length_(SEXP graph, SEXP weights, SEXP directed, SEXP unconn) {
  BEGIN_CPP11
    return cpp11::as_sexp(average_path_length_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const cpp11::doubles&>>(weights), cpp11::as_cpp<cpp11::decay_t<bool>>(directed), cpp11::as_cpp<cpp11::decay_t<bool>>(unconn)));
  END_CPP11
}
// paths.cpp
SEXP path_length_hist_(const cpp11::external_pointer<IGraph> graph, bool directed);
extern "C" SEXP _igraphlite_path_length_hist_(SEXP graph, SEXP directed) {
  BEGIN_CPP11
    return cpp11::as_sexp(path_length_hist_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<bool>>(directed)));
  END_CPP11
}
// paths.cpp
SEXP path_length_count_within(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids, bool directed);
extern "C" SEXP _igraphlite_path_length_count_within(SEXP graph, SEXP vids, SEXP directed) {
  BEGIN_CPP11
    return cpp11::as_sexp(path_length_count_within(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(vids), cpp11::as_cpp<cpp11::decay_t<bool>>(directed)));
  END_CPP11
}
// paths.cpp
SEXP path_length_count_between(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& from, const cpp11::integers& to, bool directed);
extern "C" SEXP _igraphlite_path_length_count_between(SEXP graph, SEXP from, SEXP to, SEXP directed) {
  BEGIN_CPP11
    return cpp11::as_sexp(path_length_count_between(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(from), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(to), cpp11::as_cpp<cpp11::decay_t<bool>>(directed)));
  END_CPP11
}
// structural.cpp
bool are_adjacent_(const cpp11::external_pointer<IGraph> graph, int v1, int v2);
extern "C" SEXP _igraphlite_are_adjacent_(SEXP graph, SEXP v1, SEXP v2) {
  BEGIN_CPP11
    return cpp11::as_sexp(are_adjacent_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<int>>(v1), cpp11::as_cpp<cpp11::decay_t<int>>(v2)));
  END_CPP11
}
// structural.cpp
SEXP neighborhood_size_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids, const int order, const int mode, const int mindist);
extern "C" SEXP _igraphlite_neighborhood_size_(SEXP graph, SEXP vids, SEXP order, SEXP mode, SEXP mindist) {
  BEGIN_CPP11
    return cpp11::as_sexp(neighborhood_size_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(vids), cpp11::as_cpp<cpp11::decay_t<const int>>(order), cpp11::as_cpp<cpp11::decay_t<const int>>(mode), cpp11::as_cpp<cpp11::decay_t<const int>>(mindist)));
  END_CPP11
}
// structural.cpp
SEXP neighborhood_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids, const int order, const int mode, const int mindist);
extern "C" SEXP _igraphlite_neighborhood_(SEXP graph, SEXP vids, SEXP order, SEXP mode, SEXP mindist) {
  BEGIN_CPP11
    return cpp11::as_sexp(neighborhood_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(vids), cpp11::as_cpp<cpp11::decay_t<const int>>(order), cpp11::as_cpp<cpp11::decay_t<const int>>(mode), cpp11::as_cpp<cpp11::decay_t<const int>>(mindist)));
  END_CPP11
}
// structural.cpp
SEXP subcomponent_(const cpp11::external_pointer<IGraph> graph, const int v, const int mode);
extern "C" SEXP _igraphlite_subcomponent_(SEXP graph, SEXP v, SEXP mode) {
  BEGIN_CPP11
    return cpp11::as_sexp(subcomponent_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const int>>(v), cpp11::as_cpp<cpp11::decay_t<const int>>(mode)));
  END_CPP11
}
// structural.cpp
SEXP subcomponents_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& vids, const int mode);
extern "C" SEXP _igraphlite_subcomponents_(SEXP graph, SEXP vids, SEXP mode) {
  BEGIN_CPP11
    return cpp11::as_sexp(subcomponents_(cpp11::as_cpp<cpp11::decay_t<const cpp11::external_pointer<IGraph>>>(graph), cpp11::as_cpp<cpp11::decay_t<const cpp11::integers&>>(vids), cpp11::as_cpp<cpp11::decay_t<const int>>(mode)));
  END_CPP11
}

extern "C" {
static const R_CallMethodDef CallEntries[] = {
    {"_igraphlite_E_",                                (DL_FUNC) &_igraphlite_E_,                                1},
    {"_igraphlite_V_",                                (DL_FUNC) &_igraphlite_V_,                                1},
    {"_igraphlite_Vnames_",                           (DL_FUNC) &_igraphlite_Vnames_,                           1},
    {"_igraphlite_add_edges_",                        (DL_FUNC) &_igraphlite_add_edges_,                        2},
    {"_igraphlite_add_vertices_",                     (DL_FUNC) &_igraphlite_add_vertices_,                     2},
    {"_igraphlite_are_adjacent_",                     (DL_FUNC) &_igraphlite_are_adjacent_,                     3},
    {"_igraphlite_as_adjlist_",                       (DL_FUNC) &_igraphlite_as_adjlist_,                       4},
    {"_igraphlite_as_data_frame_",                    (DL_FUNC) &_igraphlite_as_data_frame_,                    1},
    {"_igraphlite_as_edgelist_",                      (DL_FUNC) &_igraphlite_as_edgelist_,                      1},
    {"_igraphlite_as_inclist_",                       (DL_FUNC) &_igraphlite_as_inclist_,                       3},
    {"_igraphlite_average_path_length_",              (DL_FUNC) &_igraphlite_average_path_length_,              4},
    {"_igraphlite_degree_",                           (DL_FUNC) &_igraphlite_degree_,                           4},
    {"_igraphlite_delete_edges_",                     (DL_FUNC) &_igraphlite_delete_edges_,                     2},
    {"_igraphlite_delete_vertices_",                  (DL_FUNC) &_igraphlite_delete_vertices_,                  2},
    {"_igraphlite_distances_",                        (DL_FUNC) &_igraphlite_distances_,                        6},
    {"_igraphlite_ecount_",                           (DL_FUNC) &_igraphlite_ecount_,                           1},
    {"_igraphlite_edge_",                             (DL_FUNC) &_igraphlite_edge_,                             2},
    {"_igraphlite_edge_betweenness_",                 (DL_FUNC) &_igraphlite_edge_betweenness_,                 3},
    {"_igraphlite_edge_betweenness_subset_",          (DL_FUNC) &_igraphlite_edge_betweenness_subset_,          6},
    {"_igraphlite_from_",                             (DL_FUNC) &_igraphlite_from_,                             1},
    {"_igraphlite_getEattr_",                         (DL_FUNC) &_igraphlite_getEattr_,                         1},
    {"_igraphlite_getVattr_",                         (DL_FUNC) &_igraphlite_getVattr_,                         1},
    {"_igraphlite_get_all_shortest_paths_",           (DL_FUNC) &_igraphlite_get_all_shortest_paths_,           5},
    {"_igraphlite_get_all_simple_paths_",             (DL_FUNC) &_igraphlite_get_all_simple_paths_,             5},
    {"_igraphlite_get_shortest_paths_",               (DL_FUNC) &_igraphlite_get_shortest_paths_,               5},
    {"_igraphlite_graph_create_",                     (DL_FUNC) &_igraphlite_graph_create_,                     3},
    {"_igraphlite_graph_famous_",                     (DL_FUNC) &_igraphlite_graph_famous_,                     1},
    {"_igraphlite_graph_from_data_frame_",            (DL_FUNC) &_igraphlite_graph_from_data_frame_,            2},
    {"_igraphlite_graph_from_edgelist_",              (DL_FUNC) &_igraphlite_graph_from_edgelist_,              2},
    {"_igraphlite_graph_from_symbolic_edgelist_",     (DL_FUNC) &_igraphlite_graph_from_symbolic_edgelist_,     2},
    {"_igraphlite_graph_full_",                       (DL_FUNC) &_igraphlite_graph_full_,                       3},
    {"_igraphlite_graph_lattice_",                    (DL_FUNC) &_igraphlite_graph_lattice_,                    5},
    {"_igraphlite_graph_ring_",                       (DL_FUNC) &_igraphlite_graph_ring_,                       4},
    {"_igraphlite_graph_star_",                       (DL_FUNC) &_igraphlite_graph_star_,                       3},
    {"_igraphlite_graph_tree_",                       (DL_FUNC) &_igraphlite_graph_tree_,                       3},
    {"_igraphlite_igraph_version_",                   (DL_FUNC) &_igraphlite_igraph_version_,                   0},
    {"_igraphlite_incident_",                         (DL_FUNC) &_igraphlite_incident_,                         3},
    {"_igraphlite_induced_subgraph_",                 (DL_FUNC) &_igraphlite_induced_subgraph_,                 3},
    {"_igraphlite_is_directed_",                      (DL_FUNC) &_igraphlite_is_directed_,                      1},
    {"_igraphlite_layout_drl_",                       (DL_FUNC) &_igraphlite_layout_drl_,                       1},
    {"_igraphlite_layout_fruchterman_reingold_",      (DL_FUNC) &_igraphlite_layout_fruchterman_reingold_,      2},
    {"_igraphlite_layout_mds_",                       (DL_FUNC) &_igraphlite_layout_mds_,                       2},
    {"_igraphlite_layout_random_",                    (DL_FUNC) &_igraphlite_layout_random_,                    1},
    {"_igraphlite_layout_reingold_tilford_",          (DL_FUNC) &_igraphlite_layout_reingold_tilford_,          3},
    {"_igraphlite_layout_reingold_tilford_circular_", (DL_FUNC) &_igraphlite_layout_reingold_tilford_circular_, 3},
    {"_igraphlite_mean_distances_cpp_",               (DL_FUNC) &_igraphlite_mean_distances_cpp_,               6},
    {"_igraphlite_neighborhood_",                     (DL_FUNC) &_igraphlite_neighborhood_,                     5},
    {"_igraphlite_neighborhood_size_",                (DL_FUNC) &_igraphlite_neighborhood_size_,                5},
    {"_igraphlite_neighbors_",                        (DL_FUNC) &_igraphlite_neighbors_,                        3},
    {"_igraphlite_path_length_count_between",         (DL_FUNC) &_igraphlite_path_length_count_between,         4},
    {"_igraphlite_path_length_count_within",          (DL_FUNC) &_igraphlite_path_length_count_within,          3},
    {"_igraphlite_path_length_hist_",                 (DL_FUNC) &_igraphlite_path_length_hist_,                 2},
    {"_igraphlite_rng_seed",                          (DL_FUNC) &_igraphlite_rng_seed,                          1},
    {"_igraphlite_setEattr_",                         (DL_FUNC) &_igraphlite_setEattr_,                         2},
    {"_igraphlite_setVattr_",                         (DL_FUNC) &_igraphlite_setVattr_,                         2},
    {"_igraphlite_subcomponent_",                     (DL_FUNC) &_igraphlite_subcomponent_,                     3},
    {"_igraphlite_subcomponents_",                    (DL_FUNC) &_igraphlite_subcomponents_,                    3},
    {"_igraphlite_to_",                               (DL_FUNC) &_igraphlite_to_,                               1},
    {"_igraphlite_vcount_",                           (DL_FUNC) &_igraphlite_vcount_,                           1},
    {NULL, NULL, 0}
};
}

void igraphlite_init(DllInfo * dll);

extern "C" attribute_visible void R_init_igraphlite(DllInfo* dll){
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  igraphlite_init(dll);
  R_forceSymbols(dll, TRUE);
}
