// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "igraphlite_types.h"
#include <Rcpp.h>

using namespace Rcpp;

// attribute_list
Rcpp::List attribute_list(const IGraph& graph);
RcppExport SEXP _igraphlite_attribute_list(SEXP graphSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    rcpp_result_gen = Rcpp::wrap(attribute_list(graph));
    return rcpp_result_gen;
END_RCPP
}
// get_gan
double get_gan(const IGraph& graph, const char* name);
RcppExport SEXP _igraphlite_get_gan(SEXP graphSEXP, SEXP nameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const char* >::type name(nameSEXP);
    rcpp_result_gen = Rcpp::wrap(get_gan(graph, name));
    return rcpp_result_gen;
END_RCPP
}
// get_gas
const char* get_gas(const IGraph& graph, const char* name);
RcppExport SEXP _igraphlite_get_gas(SEXP graphSEXP, SEXP nameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const char* >::type name(nameSEXP);
    rcpp_result_gen = Rcpp::wrap(get_gas(graph, name));
    return rcpp_result_gen;
END_RCPP
}
// set_gattr
void set_gattr(IGraph* graph, const char* name, SEXP value);
RcppExport SEXP _igraphlite_set_gattr(SEXP graphSEXP, SEXP nameSEXP, SEXP valueSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IGraph* >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const char* >::type name(nameSEXP);
    Rcpp::traits::input_parameter< SEXP >::type value(valueSEXP);
    set_gattr(graph, name, value);
    return R_NilValue;
END_RCPP
}
// get_van
Rcpp::NumericVector get_van(const IGraph& graph, const char* name);
RcppExport SEXP _igraphlite_get_van(SEXP graphSEXP, SEXP nameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const char* >::type name(nameSEXP);
    rcpp_result_gen = Rcpp::wrap(get_van(graph, name));
    return rcpp_result_gen;
END_RCPP
}
// get_vas
Rcpp::StringVector get_vas(const IGraph& graph, const char* name);
RcppExport SEXP _igraphlite_get_vas(SEXP graphSEXP, SEXP nameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const char* >::type name(nameSEXP);
    rcpp_result_gen = Rcpp::wrap(get_vas(graph, name));
    return rcpp_result_gen;
END_RCPP
}
// set_vattr
void set_vattr(IGraph* graph, const char* name, SEXP values);
RcppExport SEXP _igraphlite_set_vattr(SEXP graphSEXP, SEXP nameSEXP, SEXP valuesSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IGraph* >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const char* >::type name(nameSEXP);
    Rcpp::traits::input_parameter< SEXP >::type values(valuesSEXP);
    set_vattr(graph, name, values);
    return R_NilValue;
END_RCPP
}
// edgelist
Rcpp::NumericMatrix edgelist(const IGraph& graph);
RcppExport SEXP _igraphlite_edgelist(SEXP graphSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    rcpp_result_gen = Rcpp::wrap(edgelist(graph));
    return rcpp_result_gen;
END_RCPP
}
// impl_degree_all
Rcpp::NumericVector impl_degree_all(const IGraph& graph, int mode, bool loops);
RcppExport SEXP _igraphlite_impl_degree_all(SEXP graphSEXP, SEXP modeSEXP, SEXP loopsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< int >::type mode(modeSEXP);
    Rcpp::traits::input_parameter< bool >::type loops(loopsSEXP);
    rcpp_result_gen = Rcpp::wrap(impl_degree_all(graph, mode, loops));
    return rcpp_result_gen;
END_RCPP
}
// impl_degree
Rcpp::NumericVector impl_degree(const IGraph& graph, const Rcpp::NumericVector& vs, int mode, bool loops);
RcppExport SEXP _igraphlite_impl_degree(SEXP graphSEXP, SEXP vsSEXP, SEXP modeSEXP, SEXP loopsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const IGraph& >::type graph(graphSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector& >::type vs(vsSEXP);
    Rcpp::traits::input_parameter< int >::type mode(modeSEXP);
    Rcpp::traits::input_parameter< bool >::type loops(loopsSEXP);
    rcpp_result_gen = Rcpp::wrap(impl_degree(graph, vs, mode, loops));
    return rcpp_result_gen;
END_RCPP
}
// len
int len(const std::vector<std::string>& args);
RcppExport SEXP _igraphlite_len(SEXP argsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<std::string>& >::type args(argsSEXP);
    rcpp_result_gen = Rcpp::wrap(len(args));
    return rcpp_result_gen;
END_RCPP
}

RcppExport SEXP _rcpp_module_boot_igraph();
RcppExport SEXP _rcpp_module_boot_test();

static const R_CallMethodDef CallEntries[] = {
    {"_igraphlite_attribute_list", (DL_FUNC) &_igraphlite_attribute_list, 1},
    {"_igraphlite_get_gan", (DL_FUNC) &_igraphlite_get_gan, 2},
    {"_igraphlite_get_gas", (DL_FUNC) &_igraphlite_get_gas, 2},
    {"_igraphlite_set_gattr", (DL_FUNC) &_igraphlite_set_gattr, 3},
    {"_igraphlite_get_van", (DL_FUNC) &_igraphlite_get_van, 2},
    {"_igraphlite_get_vas", (DL_FUNC) &_igraphlite_get_vas, 2},
    {"_igraphlite_set_vattr", (DL_FUNC) &_igraphlite_set_vattr, 3},
    {"_igraphlite_edgelist", (DL_FUNC) &_igraphlite_edgelist, 1},
    {"_igraphlite_impl_degree_all", (DL_FUNC) &_igraphlite_impl_degree_all, 3},
    {"_igraphlite_impl_degree", (DL_FUNC) &_igraphlite_impl_degree, 4},
    {"_igraphlite_len", (DL_FUNC) &_igraphlite_len, 1},
    {"_rcpp_module_boot_igraph", (DL_FUNC) &_rcpp_module_boot_igraph, 0},
    {"_rcpp_module_boot_test", (DL_FUNC) &_rcpp_module_boot_test, 0},
    {NULL, NULL, 0}
};

void igraphlite_init(DllInfo *dll);
RcppExport void R_init_igraphlite(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
    igraphlite_init(dll);
}
