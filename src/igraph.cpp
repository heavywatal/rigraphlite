// [[Rcpp::plugins(cpp14)]]
#include "igraphlite_types.h"

#include <Rcpp.h>

#include <igraph/igraph_interface.h>
#include <igraph/igraph_constructors.h>
#include <igraph/igraph_attributes.h>

RCPP_MODULE(igraph) {
  Rcpp::class_<igraph_t>("igraph_t");

  Rcpp::function("igraph_vcount", &igraph_vcount);
  Rcpp::function("igraph_ecount", &igraph_ecount);
  Rcpp::function("igraph_is_directed", &igraph_is_directed);
}

Rcpp::NumericVector from(const igraph_t& graph) {
  return Rcpp::NumericVector(graph.from.stor_begin, graph.from.stor_end);
}

Rcpp::NumericVector to(const igraph_t& graph) {
  return Rcpp::NumericVector(graph.to.stor_begin, graph.to.stor_end);
}

// [[Rcpp::export]]
Rcpp::NumericMatrix edgelist(const igraph_t& graph) {
  return Rcpp::cbind(from(graph), to(graph));
}

// [[Rcpp::export]]
igraph_t make_empty_graph(int n, bool directed = true) {
  igraph_t g;
  igraph_empty(&g, n, directed);
  return g;
}

// [[Rcpp::export]]
igraph_t make_graph(const Rcpp::NumericVector& edges, int n = 0, bool directed = true) {
  igraph_t g;
  igraph_vector_t v;
  igraph_vector_view(&v, &(edges[0]), edges.size());
  igraph_create(&g, &v, n, directed);
  return g;
}

// [[Rcpp::export]]
igraph_t make_tree(int n, int children = 2, int mode = 0) {
  igraph_t g;
  igraph_tree(&g, n, children, static_cast<igraph_tree_mode_t>(mode));
  return g;
}

// [[Rcpp::export]]
Rcpp::NumericVector
impl_degree_all(const igraph_t& graph, int mode = 3, bool loops = true) {
  igraph_vector_t res;
  igraph_vector_init(&res, igraph_vcount(&graph));
  igraph_degree(&graph, &res, igraph_vss_all(), static_cast<igraph_neimode_t>(mode), loops);
  return Rcpp::NumericVector(res.stor_begin, res.stor_end);
}

// [[Rcpp::export]]
Rcpp::NumericVector
impl_degree(const igraph_t& graph, const Rcpp::NumericVector& vs, int mode = 3, bool loops = true) {
  igraph_vector_t res;
  igraph_vector_init(&res, vs.size());
  igraph_vector_t ivs;
  igraph_vector_view(&ivs, &(vs[0]), vs.size());
  igraph_degree(&graph, &res, igraph_vss_vector(&ivs), static_cast<igraph_neimode_t>(mode), loops);
  return Rcpp::NumericVector(res.stor_begin, res.stor_end);
}

// [[Rcpp::export]]
double get_gan(const igraph_t& graph, const char* name) {
  return igraph_cattribute_GAN(&graph, name);
}

// [[Rcpp::export]]
const char* get_gas(const igraph_t& graph, const char* name) {
  return igraph_cattribute_GAS(&graph, name);
}

void set_gan(igraph_t* graph, const char* name, const Rcpp::NumericVector& value) {
  igraph_cattribute_GAN_set(graph, name, value[0]);
}

void set_gas(igraph_t* graph, const char* name, const Rcpp::StringVector& value) {
  igraph_cattribute_GAS_set(graph, name, value[0]);
}

// [[Rcpp::export]]
void set_gattr(igraph_t* graph, const char* name, SEXP value) {
  if (Rf_isNumber(value)) {
    return set_gan(graph, name, value);
  } else {
    return set_gas(graph, name, value);
  }
}

// [[Rcpp::export]]
Rcpp::NumericVector get_van(const igraph_t& graph, const char* name) {
  const auto n = igraph_vcount(&graph);
  igraph_vector_t res;
  igraph_vector_init(&res, n);
  igraph_cattribute_VANV(&graph, name, igraph_vss_all(), &res);
  return Rcpp::NumericVector(res.stor_begin, res.stor_end);
}

// [[Rcpp::export]]
Rcpp::StringVector get_vas(const igraph_t& graph, const char* name) {
  const auto n = igraph_vcount(&graph);
  igraph_strvector_t res;
  igraph_strvector_init(&res, n);
  igraph_cattribute_VASV(&graph, name, igraph_vss_all(), &res);
  Rcpp::StringVector output(n);
  for (int i = 0; i < n; ++i) {
    output[i] = res.data[i];
  }
  return output;
}

void set_van(igraph_t* graph, const char* name, const Rcpp::NumericVector& values) {
  igraph_vector_t iv;
  igraph_vector_view(&iv, &(values[0]), values.size());
  igraph_cattribute_VAN_setv(graph, name, &iv);
}

void set_vas(igraph_t* graph, const char* name, const Rcpp::StringVector& values) {
  const auto n = static_cast<int>(values.size());
  igraph_strvector_t iv;
  igraph_strvector_init(&iv, n);
  for (int i = 0; i < n; ++i) {
    igraph_strvector_set(&iv, i, values[i]);
  }
  igraph_cattribute_VAS_setv(graph, name, &iv);
}

// [[Rcpp::export]]
void set_vattr(igraph_t* graph, const char* name, SEXP values) {
  if (Rf_isNumber(values)) {
    return set_van(graph, name, values);
  } else {
    return set_vas(graph, name, values);
  }
}

void error_handler(const char* reason, const char* file, int line, int igraph_errno) {
  igraph_error_handler_printignore(reason, file, line, igraph_errno);
  Rcpp::stop(reason);
}

// [[Rcpp::init]]
void igraphlite_init(DllInfo *dll) {
  igraph_set_error_handler(&error_handler);
  igraph_i_set_attribute_table(&igraph_cattribute_table);
}
