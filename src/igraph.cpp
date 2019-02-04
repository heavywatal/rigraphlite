// [[Rcpp::plugins(cpp14)]]
#include "igraphlite_types.h"

#include <Rcpp.h>

#include <igraph/igraph_interface.h>
#include <igraph/igraph_constructors.h>
#include <igraph/igraph_attributes.h>

Rcpp::StringVector as_rvector(const igraph_strvector_t& x) {
  const int n = igraph_strvector_size(&x);
  Rcpp::StringVector output(n);
  for (int i = 0; i < n; ++i) {
    output[i] = x.data[i];
  }
  return output;
}

Rcpp::NumericVector as_rvector(const igraph_vector_t& x) {
  return Rcpp::NumericVector(x.stor_begin, x.stor_end);
}

class IVector {
  public:
    IVector(int n = 0) {
      igraph_vector_init(&data_, n);
    }
    ~IVector() {
      igraph_vector_destroy(&data_);
    }
    igraph_vector_t* data() {return &data_;}
    operator Rcpp::NumericVector() {return as_rvector(data_);}
  private:
    igraph_vector_t data_;
};

class IVectorView {
  public:
    IVectorView(const Rcpp::NumericVector& x) {
      igraph_vector_view(&data_, &(x[0]), x.size());
    }
    ~IVectorView() = default;
    igraph_vector_t* data() {return &data_;}
    operator Rcpp::NumericVector() {return as_rvector(data_);}
  private:
    igraph_vector_t data_;
};

class IStrVector {
  public:
    IStrVector(int n = 0) {
      igraph_strvector_init(&data_, n);
    }
    IStrVector(const Rcpp::StringVector& x) {
      int n = x.size();
      igraph_strvector_init(&data_, n);
      for (int i = 0; i < n; ++i) {
        igraph_strvector_set(&data_, i, x[i]);
      }
    }
    ~IStrVector() {
      igraph_strvector_destroy(&data_);
    }
    igraph_strvector_t* data() {return &data_;}
    operator Rcpp::StringVector() {return as_rvector(data_);}
  private:
    igraph_strvector_t data_;
};

RCPP_MODULE(igraph) {
  Rcpp::class_<igraph_t>("igraph_t");

  Rcpp::function("igraph_vcount", &igraph_vcount);
  Rcpp::function("igraph_ecount", &igraph_ecount);
  Rcpp::function("igraph_is_directed", &igraph_is_directed);
}

Rcpp::NumericVector from(const igraph_t& graph) {
  return as_rvector(graph.from);
}

Rcpp::NumericVector to(const igraph_t& graph) {
  return as_rvector(graph.to);
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
  igraph_create(&g, IVectorView(edges).data(), n, directed);
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
  IVector res(igraph_vcount(&graph));
  igraph_degree(&graph, res.data(), igraph_vss_all(), static_cast<igraph_neimode_t>(mode), loops);
  return res;
}

// [[Rcpp::export]]
Rcpp::NumericVector
impl_degree(const igraph_t& graph, const Rcpp::NumericVector& vs, int mode = 3, bool loops = true) {
  IVector res(vs.size());
  IVectorView ivs(vs);
  igraph_degree(&graph, res.data(), igraph_vss_vector(ivs.data()), static_cast<igraph_neimode_t>(mode), loops);
  return res;
}

// [[Rcpp::export]]
Rcpp::List attribute_list(const igraph_t& graph) {
  IStrVector gnames, vnames, enames;
  IVector    gtypes, vtypes, etypes;
  igraph_cattribute_list(&graph,
    gnames.data(), gtypes.data(),
    vnames.data(), vtypes.data(),
    enames.data(), etypes.data()
  );
  return Rcpp::List::create(
    Rcpp::Named("gnames") = Rcpp::StringVector(gnames),
    Rcpp::Named("gtypes") = Rcpp::NumericVector(gtypes),
    Rcpp::Named("vnames") = Rcpp::StringVector(vnames),
    Rcpp::Named("vtypes") = Rcpp::NumericVector(vtypes),
    Rcpp::Named("enames") = Rcpp::StringVector(enames),
    Rcpp::Named("etypes") = Rcpp::NumericVector(etypes)
  );
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
  IVector res(igraph_vcount(&graph));
  igraph_cattribute_VANV(&graph, name, igraph_vss_all(), res.data());
  return res;
}

// [[Rcpp::export]]
Rcpp::StringVector get_vas(const igraph_t& graph, const char* name) {
  IStrVector res(igraph_vcount(&graph));
  igraph_cattribute_VASV(&graph, name, igraph_vss_all(), res.data());
  return res;
}

void set_van(igraph_t* graph, const char* name, const Rcpp::NumericVector& values) {
  igraph_cattribute_VAN_setv(graph, name, IVectorView(values).data());
}

void set_vas(igraph_t* graph, const char* name, const Rcpp::StringVector& values) {
  igraph_cattribute_VAS_setv(graph, name, IStrVector(values).data());
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
