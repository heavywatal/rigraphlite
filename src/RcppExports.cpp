// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "igraphlite_types.h"
#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// is_directed_
bool is_directed_(const IGraph& graph);
RcppExport SEXP _igraphlite_is_directed_(SEXP graphSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    rcpp_result_gen = Rcpp::wrap(is_directed_(graph));
    return rcpp_result_gen;
END_RCPP
}
// vcount_
int vcount_(const IGraph& graph);
RcppExport SEXP _igraphlite_vcount_(SEXP graphSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    rcpp_result_gen = Rcpp::wrap(vcount_(graph));
    return rcpp_result_gen;
END_RCPP
}
// ecount_
int ecount_(const IGraph& graph);
RcppExport SEXP _igraphlite_ecount_(SEXP graphSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    rcpp_result_gen = Rcpp::wrap(ecount_(graph));
    return rcpp_result_gen;
END_RCPP
}
// edge_
Rcpp::IntegerVector edge_(const IGraph& graph, int eid);
RcppExport SEXP _igraphlite_edge_(SEXP graphSEXP, SEXP eidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< int >::type eid(eidSEXP);
    rcpp_result_gen = Rcpp::wrap(edge_(graph, eid));
    return rcpp_result_gen;
END_RCPP
}
// neighbors_
Rcpp::IntegerVector neighbors_(const IGraph& graph, int node, const int mode);
RcppExport SEXP _igraphlite_neighbors_(SEXP graphSEXP, SEXP nodeSEXP, SEXP modeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< int >::type node(nodeSEXP);
    Rcpp::traits::input_parameter< const int >::type mode(modeSEXP);
    rcpp_result_gen = Rcpp::wrap(neighbors_(graph, node, mode));
    return rcpp_result_gen;
END_RCPP
}
// incident_
Rcpp::IntegerVector incident_(const IGraph& graph, int node, const int mode);
RcppExport SEXP _igraphlite_incident_(SEXP graphSEXP, SEXP nodeSEXP, SEXP modeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< int >::type node(nodeSEXP);
    Rcpp::traits::input_parameter< const int >::type mode(modeSEXP);
    rcpp_result_gen = Rcpp::wrap(incident_(graph, node, mode));
    return rcpp_result_gen;
END_RCPP
}
// degree_
Rcpp::IntegerVector degree_(const IGraph& graph, const Rcpp::IntegerVector& vids, const int mode, const bool loops);
RcppExport SEXP _igraphlite_degree_(SEXP graphSEXP, SEXP vidsSEXP, SEXP modeSEXP, SEXP loopsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type vids(vidsSEXP);
    Rcpp::traits::input_parameter< const int >::type mode(modeSEXP);
    Rcpp::traits::input_parameter< const bool >::type loops(loopsSEXP);
    rcpp_result_gen = Rcpp::wrap(degree_(graph, vids, mode, loops));
    return rcpp_result_gen;
END_RCPP
}
// add_vertices_
void add_vertices_(IGraph* graph, int n);
RcppExport SEXP _igraphlite_add_vertices_(SEXP graphSEXP, SEXP nSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IGraph* >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    add_vertices_(graph, n);
    return R_NilValue;
END_RCPP
}
// add_edges_
void add_edges_(IGraph* graph, const Rcpp::IntegerVector& eids);
RcppExport SEXP _igraphlite_add_edges_(SEXP graphSEXP, SEXP eidsSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IGraph* >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type eids(eidsSEXP);
    add_edges_(graph, eids);
    return R_NilValue;
END_RCPP
}
// delete_edges_
void delete_edges_(IGraph* graph, const Rcpp::IntegerVector& eids);
RcppExport SEXP _igraphlite_delete_edges_(SEXP graphSEXP, SEXP eidsSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IGraph* >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type eids(eidsSEXP);
    delete_edges_(graph, eids);
    return R_NilValue;
END_RCPP
}
// delete_vertices_
void delete_vertices_(IGraph* graph, const Rcpp::IntegerVector& vids);
RcppExport SEXP _igraphlite_delete_vertices_(SEXP graphSEXP, SEXP vidsSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IGraph* >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type vids(vidsSEXP);
    delete_vertices_(graph, vids);
    return R_NilValue;
END_RCPP
}
// edge_betweenness_
Rcpp::NumericVector edge_betweenness_(const IGraph& graph, const bool directed, const Rcpp::NumericVector& weights);
RcppExport SEXP _igraphlite_edge_betweenness_(SEXP graphSEXP, SEXP directedSEXP, SEXP weightsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const bool >::type directed(directedSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type weights(weightsSEXP);
    rcpp_result_gen = Rcpp::wrap(edge_betweenness_(graph, directed, weights));
    return rcpp_result_gen;
END_RCPP
}
// edge_betweenness_subset_
Rcpp::NumericVector edge_betweenness_subset_(const IGraph& graph, const bool directed, const Rcpp::IntegerVector& eids, const Rcpp::NumericVector& weights, const Rcpp::IntegerVector& sources, const Rcpp::IntegerVector& targets);
RcppExport SEXP _igraphlite_edge_betweenness_subset_(SEXP graphSEXP, SEXP directedSEXP, SEXP eidsSEXP, SEXP weightsSEXP, SEXP sourcesSEXP, SEXP targetsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const bool >::type directed(directedSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type eids(eidsSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type weights(weightsSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type sources(sourcesSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type targets(targetsSEXP);
    rcpp_result_gen = Rcpp::wrap(edge_betweenness_subset_(graph, directed, eids, weights, sources, targets));
    return rcpp_result_gen;
END_RCPP
}
// graph_from_data_frame
IGraph graph_from_data_frame(const Rcpp::DataFrame& df, bool directed);
RcppExport SEXP _igraphlite_graph_from_data_frame(SEXP dfSEXP, SEXP directedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::DataFrame& >::type df(dfSEXP);
    Rcpp::traits::input_parameter< bool >::type directed(directedSEXP);
    rcpp_result_gen = Rcpp::wrap(graph_from_data_frame(df, directed));
    return rcpp_result_gen;
END_RCPP
}
// graph_from_symbolic_edgelist
IGraph graph_from_symbolic_edgelist(const Rcpp::RObject& edgelist, bool directed);
RcppExport SEXP _igraphlite_graph_from_symbolic_edgelist(SEXP edgelistSEXP, SEXP directedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::RObject& >::type edgelist(edgelistSEXP);
    Rcpp::traits::input_parameter< bool >::type directed(directedSEXP);
    rcpp_result_gen = Rcpp::wrap(graph_from_symbolic_edgelist(edgelist, directed));
    return rcpp_result_gen;
END_RCPP
}
// graph_from_edgelist
IGraph graph_from_edgelist(const Rcpp::IntegerMatrix& edgelist, bool directed);
RcppExport SEXP _igraphlite_graph_from_edgelist(SEXP edgelistSEXP, SEXP directedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::IntegerMatrix& >::type edgelist(edgelistSEXP);
    Rcpp::traits::input_parameter< bool >::type directed(directedSEXP);
    rcpp_result_gen = Rcpp::wrap(graph_from_edgelist(edgelist, directed));
    return rcpp_result_gen;
END_RCPP
}
// graph_create
IGraph graph_create(const Rcpp::IntegerVector& edges, int n, bool directed);
RcppExport SEXP _igraphlite_graph_create(SEXP edgesSEXP, SEXP nSEXP, SEXP directedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type edges(edgesSEXP);
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< bool >::type directed(directedSEXP);
    rcpp_result_gen = Rcpp::wrap(graph_create(edges, n, directed));
    return rcpp_result_gen;
END_RCPP
}
// graph_star
IGraph graph_star(int n, int mode, int center);
RcppExport SEXP _igraphlite_graph_star(SEXP nSEXP, SEXP modeSEXP, SEXP centerSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< int >::type mode(modeSEXP);
    Rcpp::traits::input_parameter< int >::type center(centerSEXP);
    rcpp_result_gen = Rcpp::wrap(graph_star(n, mode, center));
    return rcpp_result_gen;
END_RCPP
}
// graph_lattice
IGraph graph_lattice(const Rcpp::IntegerVector& dim, int nei, bool directed, bool mutual, bool circular);
RcppExport SEXP _igraphlite_graph_lattice(SEXP dimSEXP, SEXP neiSEXP, SEXP directedSEXP, SEXP mutualSEXP, SEXP circularSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type dim(dimSEXP);
    Rcpp::traits::input_parameter< int >::type nei(neiSEXP);
    Rcpp::traits::input_parameter< bool >::type directed(directedSEXP);
    Rcpp::traits::input_parameter< bool >::type mutual(mutualSEXP);
    Rcpp::traits::input_parameter< bool >::type circular(circularSEXP);
    rcpp_result_gen = Rcpp::wrap(graph_lattice(dim, nei, directed, mutual, circular));
    return rcpp_result_gen;
END_RCPP
}
// graph_ring
IGraph graph_ring(int n, bool directed, bool mutual, bool circular);
RcppExport SEXP _igraphlite_graph_ring(SEXP nSEXP, SEXP directedSEXP, SEXP mutualSEXP, SEXP circularSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< bool >::type directed(directedSEXP);
    Rcpp::traits::input_parameter< bool >::type mutual(mutualSEXP);
    Rcpp::traits::input_parameter< bool >::type circular(circularSEXP);
    rcpp_result_gen = Rcpp::wrap(graph_ring(n, directed, mutual, circular));
    return rcpp_result_gen;
END_RCPP
}
// graph_tree
IGraph graph_tree(int n, int children, int mode);
RcppExport SEXP _igraphlite_graph_tree(SEXP nSEXP, SEXP childrenSEXP, SEXP modeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< int >::type children(childrenSEXP);
    Rcpp::traits::input_parameter< int >::type mode(modeSEXP);
    rcpp_result_gen = Rcpp::wrap(graph_tree(n, children, mode));
    return rcpp_result_gen;
END_RCPP
}
// graph_full
IGraph graph_full(int n, bool directed, bool mutual);
RcppExport SEXP _igraphlite_graph_full(SEXP nSEXP, SEXP directedSEXP, SEXP mutualSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< bool >::type directed(directedSEXP);
    Rcpp::traits::input_parameter< bool >::type mutual(mutualSEXP);
    rcpp_result_gen = Rcpp::wrap(graph_full(n, directed, mutual));
    return rcpp_result_gen;
END_RCPP
}
// graph_famous
IGraph graph_famous(const char* name);
RcppExport SEXP _igraphlite_graph_famous(SEXP nameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const char* >::type name(nameSEXP);
    rcpp_result_gen = Rcpp::wrap(graph_famous(name));
    return rcpp_result_gen;
END_RCPP
}
// igraph_version
Rcpp::StringVector igraph_version();
RcppExport SEXP _igraphlite_igraph_version() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(igraph_version());
    return rcpp_result_gen;
END_RCPP
}
// rng_seed
void rng_seed(long seed);
RcppExport SEXP _igraphlite_rng_seed(SEXP seedSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< long >::type seed(seedSEXP);
    rng_seed(seed);
    return R_NilValue;
END_RCPP
}
// layout_random_
Rcpp::DataFrame layout_random_(const IGraph& graph);
RcppExport SEXP _igraphlite_layout_random_(SEXP graphSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    rcpp_result_gen = Rcpp::wrap(layout_random_(graph));
    return rcpp_result_gen;
END_RCPP
}
// layout_drl_
Rcpp::DataFrame layout_drl_(const IGraph& graph);
RcppExport SEXP _igraphlite_layout_drl_(SEXP graphSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    rcpp_result_gen = Rcpp::wrap(layout_drl_(graph));
    return rcpp_result_gen;
END_RCPP
}
// layout_fruchterman_reingold_
Rcpp::DataFrame layout_fruchterman_reingold_(const IGraph& graph, int grid);
RcppExport SEXP _igraphlite_layout_fruchterman_reingold_(SEXP graphSEXP, SEXP gridSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< int >::type grid(gridSEXP);
    rcpp_result_gen = Rcpp::wrap(layout_fruchterman_reingold_(graph, grid));
    return rcpp_result_gen;
END_RCPP
}
// layout_mds_
Rcpp::DataFrame layout_mds_(const IGraph& graph);
RcppExport SEXP _igraphlite_layout_mds_(SEXP graphSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    rcpp_result_gen = Rcpp::wrap(layout_mds_(graph));
    return rcpp_result_gen;
END_RCPP
}
// layout_reingold_tilford_
Rcpp::DataFrame layout_reingold_tilford_(const IGraph& graph, int mode, const Rcpp::IntegerVector& roots);
RcppExport SEXP _igraphlite_layout_reingold_tilford_(SEXP graphSEXP, SEXP modeSEXP, SEXP rootsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< int >::type mode(modeSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type roots(rootsSEXP);
    rcpp_result_gen = Rcpp::wrap(layout_reingold_tilford_(graph, mode, roots));
    return rcpp_result_gen;
END_RCPP
}
// layout_reingold_tilford_circular_
Rcpp::DataFrame layout_reingold_tilford_circular_(const IGraph& graph, int mode, const Rcpp::IntegerVector& roots);
RcppExport SEXP _igraphlite_layout_reingold_tilford_circular_(SEXP graphSEXP, SEXP modeSEXP, SEXP rootsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< int >::type mode(modeSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type roots(rootsSEXP);
    rcpp_result_gen = Rcpp::wrap(layout_reingold_tilford_circular_(graph, mode, roots));
    return rcpp_result_gen;
END_RCPP
}
// as_adjlist_
Rcpp::List as_adjlist_(const IGraph& graph, const int mode, const int loops, const int multiple);
RcppExport SEXP _igraphlite_as_adjlist_(SEXP graphSEXP, SEXP modeSEXP, SEXP loopsSEXP, SEXP multipleSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const int >::type mode(modeSEXP);
    Rcpp::traits::input_parameter< const int >::type loops(loopsSEXP);
    Rcpp::traits::input_parameter< const int >::type multiple(multipleSEXP);
    rcpp_result_gen = Rcpp::wrap(as_adjlist_(graph, mode, loops, multiple));
    return rcpp_result_gen;
END_RCPP
}
// as_inclist_
Rcpp::List as_inclist_(const IGraph& graph, const int mode, const int loops);
RcppExport SEXP _igraphlite_as_inclist_(SEXP graphSEXP, SEXP modeSEXP, SEXP loopsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const int >::type mode(modeSEXP);
    Rcpp::traits::input_parameter< const int >::type loops(loopsSEXP);
    rcpp_result_gen = Rcpp::wrap(as_inclist_(graph, mode, loops));
    return rcpp_result_gen;
END_RCPP
}
// as_edgelist_
Rcpp::IntegerMatrix as_edgelist_(const IGraph& graph);
RcppExport SEXP _igraphlite_as_edgelist_(SEXP graphSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    rcpp_result_gen = Rcpp::wrap(as_edgelist_(graph));
    return rcpp_result_gen;
END_RCPP
}
// from_
Rcpp::IntegerVector from_(const IGraph& graph);
RcppExport SEXP _igraphlite_from_(SEXP graphSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    rcpp_result_gen = Rcpp::wrap(from_(graph));
    return rcpp_result_gen;
END_RCPP
}
// to_
Rcpp::IntegerVector to_(const IGraph& graph);
RcppExport SEXP _igraphlite_to_(SEXP graphSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    rcpp_result_gen = Rcpp::wrap(to_(graph));
    return rcpp_result_gen;
END_RCPP
}
// setVattr_
void setVattr_(IGraph* graph, Rcpp::DataFrame other);
RcppExport SEXP _igraphlite_setVattr_(SEXP graphSEXP, SEXP otherSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IGraph* >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type other(otherSEXP);
    setVattr_(graph, other);
    return R_NilValue;
END_RCPP
}
// setEattr_
void setEattr_(IGraph* graph, Rcpp::DataFrame other);
RcppExport SEXP _igraphlite_setEattr_(SEXP graphSEXP, SEXP otherSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IGraph* >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type other(otherSEXP);
    setEattr_(graph, other);
    return R_NilValue;
END_RCPP
}
// getVattr_
Rcpp::DataFrame getVattr_(const IGraph& graph);
RcppExport SEXP _igraphlite_getVattr_(SEXP graphSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    rcpp_result_gen = Rcpp::wrap(getVattr_(graph));
    return rcpp_result_gen;
END_RCPP
}
// getEattr_
Rcpp::DataFrame getEattr_(const IGraph& graph);
RcppExport SEXP _igraphlite_getEattr_(SEXP graphSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    rcpp_result_gen = Rcpp::wrap(getEattr_(graph));
    return rcpp_result_gen;
END_RCPP
}
// are_adjacent_
Rcpp::LogicalVector are_adjacent_(const IGraph& graph, int v1, int v2);
RcppExport SEXP _igraphlite_are_adjacent_(SEXP graphSEXP, SEXP v1SEXP, SEXP v2SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< int >::type v1(v1SEXP);
    Rcpp::traits::input_parameter< int >::type v2(v2SEXP);
    rcpp_result_gen = Rcpp::wrap(are_adjacent_(graph, v1, v2));
    return rcpp_result_gen;
END_RCPP
}
// distances_
Rcpp::NumericMatrix distances_(const IGraph& graph, const Rcpp::IntegerVector& from, const Rcpp::IntegerVector& to, const Rcpp::NumericVector& weights, int mode, const std::string& algorithm);
RcppExport SEXP _igraphlite_distances_(SEXP graphSEXP, SEXP fromSEXP, SEXP toSEXP, SEXP weightsSEXP, SEXP modeSEXP, SEXP algorithmSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type from(fromSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type to(toSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type weights(weightsSEXP);
    Rcpp::traits::input_parameter< int >::type mode(modeSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type algorithm(algorithmSEXP);
    rcpp_result_gen = Rcpp::wrap(distances_(graph, from, to, weights, mode, algorithm));
    return rcpp_result_gen;
END_RCPP
}
// mean_distances_cpp_
Rcpp::NumericVector mean_distances_cpp_(const IGraph& graph, const Rcpp::IntegerVector& from, const Rcpp::IntegerVector& to, const Rcpp::NumericVector& weights, int mode, const std::string& algorithm);
RcppExport SEXP _igraphlite_mean_distances_cpp_(SEXP graphSEXP, SEXP fromSEXP, SEXP toSEXP, SEXP weightsSEXP, SEXP modeSEXP, SEXP algorithmSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type from(fromSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type to(toSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type weights(weightsSEXP);
    Rcpp::traits::input_parameter< int >::type mode(modeSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type algorithm(algorithmSEXP);
    rcpp_result_gen = Rcpp::wrap(mean_distances_cpp_(graph, from, to, weights, mode, algorithm));
    return rcpp_result_gen;
END_RCPP
}
// get_shortest_paths_
Rcpp::List get_shortest_paths_(const IGraph& graph, int from, const Rcpp::IntegerVector& to, const Rcpp::NumericVector& weights, int mode);
RcppExport SEXP _igraphlite_get_shortest_paths_(SEXP graphSEXP, SEXP fromSEXP, SEXP toSEXP, SEXP weightsSEXP, SEXP modeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< int >::type from(fromSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type to(toSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type weights(weightsSEXP);
    Rcpp::traits::input_parameter< int >::type mode(modeSEXP);
    rcpp_result_gen = Rcpp::wrap(get_shortest_paths_(graph, from, to, weights, mode));
    return rcpp_result_gen;
END_RCPP
}
// get_all_shortest_paths_
Rcpp::List get_all_shortest_paths_(const IGraph& graph, int from, const Rcpp::IntegerVector& to, const Rcpp::NumericVector& weights, int mode);
RcppExport SEXP _igraphlite_get_all_shortest_paths_(SEXP graphSEXP, SEXP fromSEXP, SEXP toSEXP, SEXP weightsSEXP, SEXP modeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< int >::type from(fromSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type to(toSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type weights(weightsSEXP);
    Rcpp::traits::input_parameter< int >::type mode(modeSEXP);
    rcpp_result_gen = Rcpp::wrap(get_all_shortest_paths_(graph, from, to, weights, mode));
    return rcpp_result_gen;
END_RCPP
}
// get_all_simple_paths_
Rcpp::IntegerVector get_all_simple_paths_(const IGraph& graph, int from, const Rcpp::IntegerVector& to, int cutoff, int mode);
RcppExport SEXP _igraphlite_get_all_simple_paths_(SEXP graphSEXP, SEXP fromSEXP, SEXP toSEXP, SEXP cutoffSEXP, SEXP modeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< int >::type from(fromSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type to(toSEXP);
    Rcpp::traits::input_parameter< int >::type cutoff(cutoffSEXP);
    Rcpp::traits::input_parameter< int >::type mode(modeSEXP);
    rcpp_result_gen = Rcpp::wrap(get_all_simple_paths_(graph, from, to, cutoff, mode));
    return rcpp_result_gen;
END_RCPP
}
// average_path_length_
double average_path_length_(const IGraph& graph, bool directed);
RcppExport SEXP _igraphlite_average_path_length_(SEXP graphSEXP, SEXP directedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< bool >::type directed(directedSEXP);
    rcpp_result_gen = Rcpp::wrap(average_path_length_(graph, directed));
    return rcpp_result_gen;
END_RCPP
}
// path_length_hist_
Rcpp::NumericVector path_length_hist_(const IGraph& graph, bool directed);
RcppExport SEXP _igraphlite_path_length_hist_(SEXP graphSEXP, SEXP directedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< bool >::type directed(directedSEXP);
    rcpp_result_gen = Rcpp::wrap(path_length_hist_(graph, directed));
    return rcpp_result_gen;
END_RCPP
}
// path_length_count_within
Rcpp::IntegerVector path_length_count_within(const IGraph& graph, const Rcpp::IntegerVector& vids, bool directed);
RcppExport SEXP _igraphlite_path_length_count_within(SEXP graphSEXP, SEXP vidsSEXP, SEXP directedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type vids(vidsSEXP);
    Rcpp::traits::input_parameter< bool >::type directed(directedSEXP);
    rcpp_result_gen = Rcpp::wrap(path_length_count_within(graph, vids, directed));
    return rcpp_result_gen;
END_RCPP
}
// path_length_count_between
Rcpp::IntegerVector path_length_count_between(const IGraph& graph, const Rcpp::IntegerVector& from, const Rcpp::IntegerVector& to, bool directed);
RcppExport SEXP _igraphlite_path_length_count_between(SEXP graphSEXP, SEXP fromSEXP, SEXP toSEXP, SEXP directedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type from(fromSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type to(toSEXP);
    Rcpp::traits::input_parameter< bool >::type directed(directedSEXP);
    rcpp_result_gen = Rcpp::wrap(path_length_count_between(graph, from, to, directed));
    return rcpp_result_gen;
END_RCPP
}
// neighborhood_size_
Rcpp::IntegerVector neighborhood_size_(const IGraph& graph, const Rcpp::IntegerVector& vids, const int order, const int mode, const int mindist);
RcppExport SEXP _igraphlite_neighborhood_size_(SEXP graphSEXP, SEXP vidsSEXP, SEXP orderSEXP, SEXP modeSEXP, SEXP mindistSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type vids(vidsSEXP);
    Rcpp::traits::input_parameter< const int >::type order(orderSEXP);
    Rcpp::traits::input_parameter< const int >::type mode(modeSEXP);
    Rcpp::traits::input_parameter< const int >::type mindist(mindistSEXP);
    rcpp_result_gen = Rcpp::wrap(neighborhood_size_(graph, vids, order, mode, mindist));
    return rcpp_result_gen;
END_RCPP
}
// neighborhood_
Rcpp::List neighborhood_(const IGraph& graph, const Rcpp::IntegerVector& vids, const int order, const int mode, const int mindist);
RcppExport SEXP _igraphlite_neighborhood_(SEXP graphSEXP, SEXP vidsSEXP, SEXP orderSEXP, SEXP modeSEXP, SEXP mindistSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type vids(vidsSEXP);
    Rcpp::traits::input_parameter< const int >::type order(orderSEXP);
    Rcpp::traits::input_parameter< const int >::type mode(modeSEXP);
    Rcpp::traits::input_parameter< const int >::type mindist(mindistSEXP);
    rcpp_result_gen = Rcpp::wrap(neighborhood_(graph, vids, order, mode, mindist));
    return rcpp_result_gen;
END_RCPP
}
// subcomponent_
Rcpp::IntegerVector subcomponent_(const IGraph& graph, const int v, const int mode);
RcppExport SEXP _igraphlite_subcomponent_(SEXP graphSEXP, SEXP vSEXP, SEXP modeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const int >::type v(vSEXP);
    Rcpp::traits::input_parameter< const int >::type mode(modeSEXP);
    rcpp_result_gen = Rcpp::wrap(subcomponent_(graph, v, mode));
    return rcpp_result_gen;
END_RCPP
}
// subcomponents_
Rcpp::List subcomponents_(const IGraph& graph, const Rcpp::IntegerVector& vids, const int mode);
RcppExport SEXP _igraphlite_subcomponents_(SEXP graphSEXP, SEXP vidsSEXP, SEXP modeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type vids(vidsSEXP);
    Rcpp::traits::input_parameter< const int >::type mode(modeSEXP);
    rcpp_result_gen = Rcpp::wrap(subcomponents_(graph, vids, mode));
    return rcpp_result_gen;
END_RCPP
}
// induced_subgraph_
IGraph induced_subgraph_(const IGraph& other, const Rcpp::IntegerVector& vids, int impl);
RcppExport SEXP _igraphlite_induced_subgraph_(SEXP otherSEXP, SEXP vidsSEXP, SEXP implSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type other(otherSEXP);
    Rcpp::traits::input_parameter< const Rcpp::IntegerVector& >::type vids(vidsSEXP);
    Rcpp::traits::input_parameter< int >::type impl(implSEXP);
    rcpp_result_gen = Rcpp::wrap(induced_subgraph_(other, vids, impl));
    return rcpp_result_gen;
END_RCPP
}

RcppExport SEXP _rcpp_module_boot_igraph();

static const R_CallMethodDef CallEntries[] = {
    {"_igraphlite_is_directed_", (DL_FUNC) &_igraphlite_is_directed_, 1},
    {"_igraphlite_vcount_", (DL_FUNC) &_igraphlite_vcount_, 1},
    {"_igraphlite_ecount_", (DL_FUNC) &_igraphlite_ecount_, 1},
    {"_igraphlite_edge_", (DL_FUNC) &_igraphlite_edge_, 2},
    {"_igraphlite_neighbors_", (DL_FUNC) &_igraphlite_neighbors_, 3},
    {"_igraphlite_incident_", (DL_FUNC) &_igraphlite_incident_, 3},
    {"_igraphlite_degree_", (DL_FUNC) &_igraphlite_degree_, 4},
    {"_igraphlite_add_vertices_", (DL_FUNC) &_igraphlite_add_vertices_, 2},
    {"_igraphlite_add_edges_", (DL_FUNC) &_igraphlite_add_edges_, 2},
    {"_igraphlite_delete_edges_", (DL_FUNC) &_igraphlite_delete_edges_, 2},
    {"_igraphlite_delete_vertices_", (DL_FUNC) &_igraphlite_delete_vertices_, 2},
    {"_igraphlite_edge_betweenness_", (DL_FUNC) &_igraphlite_edge_betweenness_, 3},
    {"_igraphlite_edge_betweenness_subset_", (DL_FUNC) &_igraphlite_edge_betweenness_subset_, 6},
    {"_igraphlite_graph_from_data_frame", (DL_FUNC) &_igraphlite_graph_from_data_frame, 2},
    {"_igraphlite_graph_from_symbolic_edgelist", (DL_FUNC) &_igraphlite_graph_from_symbolic_edgelist, 2},
    {"_igraphlite_graph_from_edgelist", (DL_FUNC) &_igraphlite_graph_from_edgelist, 2},
    {"_igraphlite_graph_create", (DL_FUNC) &_igraphlite_graph_create, 3},
    {"_igraphlite_graph_star", (DL_FUNC) &_igraphlite_graph_star, 3},
    {"_igraphlite_graph_lattice", (DL_FUNC) &_igraphlite_graph_lattice, 5},
    {"_igraphlite_graph_ring", (DL_FUNC) &_igraphlite_graph_ring, 4},
    {"_igraphlite_graph_tree", (DL_FUNC) &_igraphlite_graph_tree, 3},
    {"_igraphlite_graph_full", (DL_FUNC) &_igraphlite_graph_full, 3},
    {"_igraphlite_graph_famous", (DL_FUNC) &_igraphlite_graph_famous, 1},
    {"_igraphlite_igraph_version", (DL_FUNC) &_igraphlite_igraph_version, 0},
    {"_igraphlite_rng_seed", (DL_FUNC) &_igraphlite_rng_seed, 1},
    {"_igraphlite_layout_random_", (DL_FUNC) &_igraphlite_layout_random_, 1},
    {"_igraphlite_layout_drl_", (DL_FUNC) &_igraphlite_layout_drl_, 1},
    {"_igraphlite_layout_fruchterman_reingold_", (DL_FUNC) &_igraphlite_layout_fruchterman_reingold_, 2},
    {"_igraphlite_layout_mds_", (DL_FUNC) &_igraphlite_layout_mds_, 1},
    {"_igraphlite_layout_reingold_tilford_", (DL_FUNC) &_igraphlite_layout_reingold_tilford_, 3},
    {"_igraphlite_layout_reingold_tilford_circular_", (DL_FUNC) &_igraphlite_layout_reingold_tilford_circular_, 3},
    {"_igraphlite_as_adjlist_", (DL_FUNC) &_igraphlite_as_adjlist_, 4},
    {"_igraphlite_as_inclist_", (DL_FUNC) &_igraphlite_as_inclist_, 3},
    {"_igraphlite_as_edgelist_", (DL_FUNC) &_igraphlite_as_edgelist_, 1},
    {"_igraphlite_from_", (DL_FUNC) &_igraphlite_from_, 1},
    {"_igraphlite_to_", (DL_FUNC) &_igraphlite_to_, 1},
    {"_igraphlite_setVattr_", (DL_FUNC) &_igraphlite_setVattr_, 2},
    {"_igraphlite_setEattr_", (DL_FUNC) &_igraphlite_setEattr_, 2},
    {"_igraphlite_getVattr_", (DL_FUNC) &_igraphlite_getVattr_, 1},
    {"_igraphlite_getEattr_", (DL_FUNC) &_igraphlite_getEattr_, 1},
    {"_igraphlite_are_adjacent_", (DL_FUNC) &_igraphlite_are_adjacent_, 3},
    {"_igraphlite_distances_", (DL_FUNC) &_igraphlite_distances_, 6},
    {"_igraphlite_mean_distances_cpp_", (DL_FUNC) &_igraphlite_mean_distances_cpp_, 6},
    {"_igraphlite_get_shortest_paths_", (DL_FUNC) &_igraphlite_get_shortest_paths_, 5},
    {"_igraphlite_get_all_shortest_paths_", (DL_FUNC) &_igraphlite_get_all_shortest_paths_, 5},
    {"_igraphlite_get_all_simple_paths_", (DL_FUNC) &_igraphlite_get_all_simple_paths_, 5},
    {"_igraphlite_average_path_length_", (DL_FUNC) &_igraphlite_average_path_length_, 2},
    {"_igraphlite_path_length_hist_", (DL_FUNC) &_igraphlite_path_length_hist_, 2},
    {"_igraphlite_path_length_count_within", (DL_FUNC) &_igraphlite_path_length_count_within, 3},
    {"_igraphlite_path_length_count_between", (DL_FUNC) &_igraphlite_path_length_count_between, 4},
    {"_igraphlite_neighborhood_size_", (DL_FUNC) &_igraphlite_neighborhood_size_, 5},
    {"_igraphlite_neighborhood_", (DL_FUNC) &_igraphlite_neighborhood_, 5},
    {"_igraphlite_subcomponent_", (DL_FUNC) &_igraphlite_subcomponent_, 3},
    {"_igraphlite_subcomponents_", (DL_FUNC) &_igraphlite_subcomponents_, 3},
    {"_igraphlite_induced_subgraph_", (DL_FUNC) &_igraphlite_induced_subgraph_, 3},
    {"_rcpp_module_boot_igraph", (DL_FUNC) &_rcpp_module_boot_igraph, 0},
    {NULL, NULL, 0}
};

void igraphlite_init(DllInfo *dll);
RcppExport void R_init_igraphlite(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
    igraphlite_init(dll);
}
