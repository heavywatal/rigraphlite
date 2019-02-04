// [[Rcpp::plugins(cpp14)]]
#include "igraphlite_types.h"

#include <Rcpp.h>

#include <igraph/igraph_datatype.h>
#include <igraph/igraph_interface.h>
#include <igraph/igraph_constructors.h>
#include <igraph/igraph_attributes.h>
#undef VECTOR
#undef MATRIX

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

class IGraph {
  public:
    ~IGraph() noexcept {
      igraph_destroy(&data_);
    }
    IGraph(const IGraph& other) noexcept {
      igraph_copy(&data_, &other.data_);
    }
    IGraph(IGraph&&) noexcept = default;
    IGraph(igraph_t&& data) noexcept: data_(std::move(data)) {}

    IGraph(int n, bool directed) {
      igraph_empty(&data_, n, directed);
    }
    IGraph(const Rcpp::NumericVector& edges, int n, bool directed) {
      igraph_create(&data_, IVectorView(edges).data(), n, directed);
    }

    // Workaround: Rcpp Module cannot expose constructors with default values
    static IGraph create(const Rcpp::NumericVector& edges, int n, bool directed) {
      return IGraph(edges, n, directed);
    }
    static IGraph tree(int n, int children, int mode) {
      IGraph g;
      igraph_tree(g.data(), n, children, static_cast<igraph_tree_mode_t>(mode));
      return g;
    }

    bool is_directed() const {return igraph_is_directed(&data_);}
    Rcpp::NumericVector from() const {return as_rvector(data_.from) + 1;}
    Rcpp::NumericVector to() const {return as_rvector(data_.to) + 1;}
    long vcount() const {return igraph_vcount(&data_);}
    long ecount() const {return igraph_ecount(&data_);}
    igraph_t* data() {return &data_;}
    const igraph_t* data() const {return &data_;}
  private:
    IGraph() = default;
    igraph_t data_;
};

RCPP_MODULE(igraph) {
  Rcpp::class_<IGraph>("IGraph")
    .const_method("is_directed", &IGraph::is_directed)
    .const_method("from", &IGraph::from)
    .const_method("to", &IGraph::to)
    .const_method("vcount", &IGraph::vcount)
    .const_method("ecount", &IGraph::ecount)
  ;

  // Workaround: free functions in RcppExport.cpp cannot return incomplete class
  Rcpp::function("igraph_create", &IGraph::create,
    Rcpp::List::create(Rcpp::_["edges"], Rcpp::_["n"] = 0, Rcpp::_["directed"] = true)
  );

  Rcpp::function("igraph_tree", &IGraph::tree,
    Rcpp::List::create(Rcpp::_["n"], Rcpp::_["children"] = 2, Rcpp::_["mode"] = 0)
  );
}

// [[Rcpp::export]]
Rcpp::NumericMatrix edgelist(const IGraph& graph) {
  return Rcpp::cbind(graph.from(), graph.to());
}

// [[Rcpp::export]]
Rcpp::NumericVector
impl_degree_all(const IGraph& graph, int mode = 3, bool loops = true) {
  IVector res(graph.vcount());
  igraph_degree(graph.data(), res.data(), igraph_vss_all(), static_cast<igraph_neimode_t>(mode), loops);
  return res;
}

// [[Rcpp::export]]
Rcpp::NumericVector
impl_degree(const IGraph& graph, const Rcpp::NumericVector& vs, int mode = 3, bool loops = true) {
  IVector res(vs.size());
  IVectorView ivs(vs);
  igraph_degree(graph.data(), res.data(), igraph_vss_vector(ivs.data()), static_cast<igraph_neimode_t>(mode), loops);
  return res;
}

// [[Rcpp::export]]
Rcpp::List attribute_list(const IGraph& graph) {
  IStrVector gnames, vnames, enames;
  IVector    gtypes, vtypes, etypes;
  igraph_cattribute_list(graph.data(),
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

void error_handler(const char* reason, const char* file, int line, int igraph_errno) {
  igraph_error_handler_printignore(reason, file, line, igraph_errno);
  Rcpp::stop(reason);
}

// [[Rcpp::init]]
void igraphlite_init(DllInfo *dll) {
  igraph_set_error_handler(&error_handler);
  igraph_i_set_attribute_table(&igraph_cattribute_table);
}
