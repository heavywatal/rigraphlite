// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "igraphlite_types.h"
#include <Rcpp.h>

using namespace Rcpp;

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
IGraph graph_from_edgelist(const Rcpp::NumericMatrix& edgelist, bool directed);
RcppExport SEXP _igraphlite_graph_from_edgelist(SEXP edgelistSEXP, SEXP directedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::NumericMatrix& >::type edgelist(edgelistSEXP);
    Rcpp::traits::input_parameter< bool >::type directed(directedSEXP);
    rcpp_result_gen = Rcpp::wrap(graph_from_edgelist(edgelist, directed));
    return rcpp_result_gen;
END_RCPP
}
// graph_create
IGraph graph_create(const Rcpp::NumericVector& edges, int n, bool directed);
RcppExport SEXP _igraphlite_graph_create(SEXP edgesSEXP, SEXP nSEXP, SEXP directedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type edges(edgesSEXP);
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< bool >::type directed(directedSEXP);
    rcpp_result_gen = Rcpp::wrap(graph_create(edges, n, directed));
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

RcppExport SEXP _rcpp_module_boot_igraph();

static const R_CallMethodDef CallEntries[] = {
    {"_igraphlite_graph_from_data_frame", (DL_FUNC) &_igraphlite_graph_from_data_frame, 2},
    {"_igraphlite_graph_from_symbolic_edgelist", (DL_FUNC) &_igraphlite_graph_from_symbolic_edgelist, 2},
    {"_igraphlite_graph_from_edgelist", (DL_FUNC) &_igraphlite_graph_from_edgelist, 2},
    {"_igraphlite_graph_create", (DL_FUNC) &_igraphlite_graph_create, 3},
    {"_igraphlite_graph_tree", (DL_FUNC) &_igraphlite_graph_tree, 3},
    {"_igraphlite_igraph_version", (DL_FUNC) &_igraphlite_igraph_version, 0},
    {"_rcpp_module_boot_igraph", (DL_FUNC) &_rcpp_module_boot_igraph, 0},
    {NULL, NULL, 0}
};

void igraphlite_init(DllInfo *dll);
RcppExport void R_init_igraphlite(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
    igraphlite_init(dll);
}
