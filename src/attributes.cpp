#include "igraph.hpp"

#include <igraph/igraph_attributes.h>

// [[Rcpp::export]]
Rcpp::List attribute_list(const IGraph& graph) {
  IStrVector gnames, vnames, enames;
  IVector    gtypes, vtypes, etypes;
  igraph_cattribute_list(graph.data(),
    gnames.data(), gtypes.data(),
    vnames.data(), vtypes.data(),
    enames.data(), etypes.data()
  );
  auto gattr = Rcpp::NumericVector(gtypes);
  auto vattr = Rcpp::NumericVector(vtypes);
  auto eattr = Rcpp::NumericVector(etypes);
  gattr.names() = Rcpp::StringVector(gnames);
  vattr.names() = Rcpp::StringVector(vnames);
  eattr.names() = Rcpp::StringVector(enames);
  return Rcpp::List::create(
    Rcpp::Named("gattr") = gattr,
    Rcpp::Named("vattr") = vattr,
    Rcpp::Named("eattr") = eattr
  );
}

// [[Rcpp::export]]
double get_gan(const IGraph& graph, const char* name) {
  return igraph_cattribute_GAN(graph.data(), name);
}

// [[Rcpp::export]]
const char* get_gas(const IGraph& graph, const char* name) {
  return igraph_cattribute_GAS(graph.data(), name);
}

void set_gan(IGraph* graph, const char* name, const Rcpp::NumericVector& value) {
  igraph_cattribute_GAN_set(graph->data(), name, value[0]);
}

void set_gas(IGraph* graph, const char* name, const Rcpp::StringVector& value) {
  igraph_cattribute_GAS_set(graph->data(), name, value[0]);
}

// [[Rcpp::export]]
void set_gattr(IGraph* graph, const char* name, SEXP value) {
  if (Rf_isNumber(value)) {
    return set_gan(graph, name, value);
  } else {
    return set_gas(graph, name, value);
  }
}

// [[Rcpp::export]]
Rcpp::NumericVector get_van(const IGraph& graph, const char* name) {
  IVector res(graph.vcount());
  igraph_cattribute_VANV(graph.data(), name, igraph_vss_all(), res.data());
  return res;
}

// [[Rcpp::export]]
Rcpp::StringVector get_vas(const IGraph& graph, const char* name) {
  IStrVector res(graph.vcount());
  igraph_cattribute_VASV(graph.data(), name, igraph_vss_all(), res.data());
  return res;
}

void set_van(IGraph* graph, const char* name, const Rcpp::NumericVector& values) {
  igraph_cattribute_VAN_setv(graph->data(), name, IVectorView(values).data());
}

void set_vas(IGraph* graph, const char* name, const Rcpp::StringVector& values) {
  igraph_cattribute_VAS_setv(graph->data(), name, IStrVector(values).data());
}

// [[Rcpp::export]]
void set_vattr(IGraph* graph, const char* name, SEXP values) {
  if (Rf_isNumber(values)) {
    return set_van(graph, name, values);
  } else {
    return set_vas(graph, name, values);
  }
}
