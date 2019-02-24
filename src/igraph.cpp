#include "igraphlite_types.h"

#include "vector.hpp"

#include <igraph/igraph_interface.h>
#include <igraph/igraph_constructors.h>

RCPP_MODULE(igraph) {
  Rcpp::class_<IGraph>("IGraph")
    .constructor<int, bool>() // igraph_empty()
    .constructor<const IGraph&, Rcpp::NumericVector, int>()

    // Basic interface
    .property("vcount", &IGraph::vcount)
    .property("ecount", &IGraph::ecount)
    .property("is_directed", &IGraph::is_directed)
    .const_method("edge", &IGraph::edge)
    .const_method("neighbors", &IGraph::neighbors)
    .const_method("incident", &IGraph::incident)
    .const_method("degree", &IGraph::degree)
    .method("add_edges", &IGraph::add_edges)
    .method("add_vertices", &IGraph::add_vertices)
    .method("delete_edges", &IGraph::delete_edges)
    .method("delete_vertices", &IGraph::delete_vertices)

    // Structural properties
    .const_method("are_connected", &IGraph::are_connected)
    .const_method("shortest_paths", &IGraph::shortest_paths)
    .const_method("get_shortest_paths", &IGraph::get_shortest_paths)
    .const_method("average_path_length", &IGraph::average_path_length)
    .const_method("path_length_hist", &IGraph::path_length_hist)
    .const_method("neighborhood_size", &IGraph::neighborhood_size)
    .const_method("neighborhood", &IGraph::neighborhood)
    .const_method("subcomponent", &IGraph::subcomponent)
    .const_method("subcomponents", &IGraph::subcomponents)

    // Layout
    .method("layout_random", &IGraph::layout_random)
    .method("layout_drl", &IGraph::layout_drl)
    .method("layout_fruchterman_reingold", &IGraph::layout_fruchterman_reingold)
    .method("layout_mds", &IGraph::layout_mds)
    .method("layout_reingold_tilford", &IGraph::layout_reingold_tilford)
    .method("layout_reingold_tilford_circular", &IGraph::layout_reingold_tilford_circular)

    .const_method("as_adjlist", &IGraph::as_adjlist)
    .const_method("as_inclist", &IGraph::as_inclist)
    .const_method("as_edgelist", &IGraph::as_edgelist)
    .const_method("as_data_frame", &IGraph::as_data_frame)

    .property("is_sink", &IGraph::is_sink)
    .property("is_source", &IGraph::is_source)
    .property("sink", &IGraph::sink)
    .property("source", &IGraph::source)

    .property("Vattr", &IGraph::getVattr, &IGraph::setVattr)
    .property("Eattr", &IGraph::getEattr, &IGraph::setEattr)
    .property("V", &IGraph::V)
    .property("E", &IGraph::E)

    // igraph_t
    .property("from", &IGraph::from)
    .property("to", &IGraph::to)
    .property("oi", &IGraph::oi)
    .property("ii", &IGraph::ii)
    .property("os", &IGraph::os)
    .property("is", &IGraph::is)
  ;
}

IGraph::IGraph(): data_(std::make_unique<igraph_t>()) {}

IGraph::~IGraph() noexcept {
  if (data_) igraph_destroy(data_.get());
}

IGraph::IGraph(const IGraph& other) noexcept: IGraph::IGraph() {
  igraph_copy(data_.get(), other.data_.get());
  Vattr_ = other.Vattr_;
  Eattr_ = other.Eattr_;
}

IGraph::IGraph(IGraph&& other) = default;

IGraph::IGraph(int n, bool directed): IGraph::IGraph() {
  igraph_empty(data_.get(), n, directed);
  init_attr();
}

IGraph::IGraph(const Rcpp::NumericVector& edges, int n, bool directed): IGraph::IGraph() {
  igraph_create(data_.get(), ISelectorInPlace(edges).data(), n, directed);
  init_attr();
}

IGraph::IGraph(int n, int mode, double center): IGraph::IGraph() {
  // double center to distinguish overloaded contructors (vs tree).
  igraph_star(data_.get(), n, static_cast<igraph_star_mode_t>(mode), static_cast<int>(center));
  init_attr();
}

IGraph::IGraph(const Rcpp::NumericVector& dim, int nei, bool directed, bool mutual, bool circular): IGraph::IGraph() {
  igraph_lattice(data_.get(), ISelectorInPlace(dim).data(), nei, directed, mutual, circular);
  init_attr();
}

IGraph::IGraph(int n, bool directed, bool mutual, bool circular): IGraph::IGraph() {
  igraph_ring(data_.get(), n, directed, mutual, circular);
  init_attr();
}

IGraph::IGraph(int n, int children, int mode): IGraph::IGraph() {
  igraph_tree(data_.get(), n, children, static_cast<igraph_tree_mode_t>(mode));
  init_attr();
}

IGraph::IGraph(int n, bool directed, bool loops): IGraph::IGraph() {
  igraph_full(data_.get(), n, directed, loops);
  init_attr();
}

long IGraph::vcount() const {
  return igraph_vcount(data_.get());
}

long IGraph::ecount() const {
  return igraph_ecount(data_.get());
}

bool IGraph::is_directed() const {
  return igraph_is_directed(data_.get());
}

Rcpp::IntegerVector
IGraph::edge(int eid) const {
  Rcpp::IntegerVector res(2);
  igraph_edge(data_.get(), --eid, &res[0], &res[1]);
  return res + 1;
}

Rcpp::NumericVector
IGraph::neighbors(int node, const int mode) const {
  IVector<AsIndicesInPlace> res(1);
  igraph_neighbors(data_.get(), res.data(), --node, static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

Rcpp::NumericVector
IGraph::incident(int node, const int mode) const {
  IVector<AsIndicesInPlace> res(1);
  igraph_incident(data_.get(), res.data(), --node, static_cast<igraph_neimode_t>(mode));
  return res.wrap();
}

Rcpp::NumericVector
IGraph::degree(const Rcpp::NumericVector& vids, const int mode, const bool loops) const {
  const R_xlen_t n = vids.size();
  IVector<AsValues> res(n > 0 ? n : vcount());
  igraph_degree(
    data_.get(), res.data(),
    (n > 0) ? ISelectorInPlace(vids).vss() : igraph_vss_all(),
    static_cast<igraph_neimode_t>(mode), loops);
  return res.wrap();
}

Rcpp::LogicalVector IGraph::is_sink() const {
  return degree(Rcpp::NumericVector(0L), 1L, true) == 0;
}

Rcpp::LogicalVector IGraph::is_source() const {
  return degree(Rcpp::NumericVector(0L), 2L, true) == 0;
}

Rcpp::IntegerVector IGraph::sink() const {
  return Rcpp::IntegerVector(V())[is_sink()];
}

Rcpp::IntegerVector IGraph::source() const {
  return Rcpp::IntegerVector(V())[is_source()];
}

Rcpp::List IGraph::as_adjlist(const int mode) const {
  return IAdjList<AsIndicesInPlace>(data_.get(), mode).wrap();
}

Rcpp::List IGraph::as_inclist(const int mode) const {
  return IIncList<AsIndicesInPlace>(data_.get(), mode).wrap();
}

Rcpp::NumericVector IGraph::from() const {return AsIndices::wrap(&data_->from);}
Rcpp::NumericVector IGraph::to() const {return AsIndices::wrap(&data_->to);}
Rcpp::NumericVector IGraph::oi() const {return AsIndices::wrap(&data_->oi);}
Rcpp::NumericVector IGraph::ii() const {return AsIndices::wrap(&data_->ii);}
Rcpp::NumericVector IGraph::os() const {return AsIndices::wrap(&data_->os);}
Rcpp::NumericVector IGraph::is() const {return AsIndices::wrap(&data_->is);}

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
// Attributes

namespace impl {

  inline Rcpp::CharacterVector tibble_class() {
    return Rcpp::CharacterVector::create("tbl_df", "tbl", "data.frame");
  }

  inline void set_rownames(Rcpp::DataFrame& df, int n) {
    df.attr("row.names") = Rcpp::IntegerVector{Rcpp::IntegerVector::get_na(), -n};
  }

  inline void mutate(Rcpp::DataFrame& df, const char* name, const Rcpp::RObject& value) {
    Rcpp::List attr_holder;
    Rf_copyMostAttrib(df, attr_holder);
    df[name] = value;
    Rf_copyMostAttrib(attr_holder, df);
  }

  template <class T> inline
  T na() {return T{};}
  template <> inline
  int na<int>() {return R_NaInt;}
  template <> inline
  double na<double>() {return R_NaReal;}
  template <> inline
  SEXP na<SEXP>() {return R_NaString;}

  template <int RTYPE, class T> inline
  Rcpp::Vector<RTYPE> elongate(const Rcpp::Vector<RTYPE>& x, long n) {
    long len = x.size();
    Rcpp::Vector<RTYPE> res(len + n);
    for (long i = 0; i < len; ++i) {
      res[i] = x[i];
    }
    for (long i = len; i < res.size(); ++i) {
      res[i] = na<T>();
    }
    return res;
  }

  inline Rcpp::LogicalVector negate(const Rcpp::IntegerVector& idx, long n) {
    return !Rcpp::in(Rcpp::Range(0, n - 1), idx);
  }

  template <int RTYPE, class T> inline
  Rcpp::Vector<RTYPE> subset(const Rcpp::Vector<RTYPE>& x, const T& idx) {
    return x[idx];
  }

  inline void append_na_rows(Rcpp::DataFrame& df, long n) {
    Rcpp::List attr_holder;
    const Rcpp::StringVector names = df.attr("names");
    for (const char* name: names) {
      switch (TYPEOF(df[name])) {
        case INTSXP:  mutate(df, name, elongate<INTSXP, int>(df[name], n)); break;
        case REALSXP: mutate(df, name, elongate<REALSXP, double>(df[name], n)); break;
        case STRSXP:  mutate(df, name, elongate<STRSXP, SEXP>(df[name], n)); break;
        default: Rcpp::stop("Invalid type for attributes: %d", TYPEOF(df[name]));
      }
    }
    impl::set_rownames(df, df.nrow() + n);
  }

  template <class T>
  inline void filter(Rcpp::DataFrame& df, const T& idx) {
    Rcpp::List attr_holder;
    const Rcpp::StringVector names = df.attr("names");
    for (const char* name: names) {
      switch (TYPEOF(df[name])) {
        case INTSXP:  mutate(df, name, subset<INTSXP>(df[name], idx)); break;
        case REALSXP: mutate(df, name, subset<REALSXP>(df[name], idx)); break;
        case STRSXP:  mutate(df, name, subset<STRSXP>(df[name], idx)); break;
        default: Rcpp::stop("Invalid type for attributes: %d", TYPEOF(df[name]));
      }
    }
    impl::set_rownames(df, Rcpp::sum(idx));
  }
}

void IGraph::add_edges(const Rcpp::NumericVector& edges) {
  const long new_vs = static_cast<long>(Rcpp::max(edges)) - vcount();
  if (new_vs) add_vertices(new_vs);
  igraph_add_edges(data_.get(), ISelectorInPlace(edges).data(), nullptr);
  impl::append_na_rows(Eattr_, edges.size() / 2);
}

void IGraph::add_vertices(int n) {
  igraph_add_vertices(data_.get(), n, nullptr);
  impl::append_na_rows(Vattr_, n);
}

void IGraph::delete_edges(const Rcpp::NumericVector& eids) {
  ISelectorInPlace ceids(eids);
  auto idx = Rcpp::as<Rcpp::IntegerVector>(ceids.wrap());
  impl::filter(Eattr_, impl::negate(idx, ecount()));
  igraph_delete_edges(data_.get(), ceids.ess());
}

void IGraph::delete_vertices(const Rcpp::NumericVector& vids) {
  Rcpp::LogicalVector eidx = Rcpp::in(from(), vids) | Rcpp::in(to(), vids);
  impl::filter(Eattr_, !eidx);
  ISelectorInPlace cvids(vids);
  auto idx = Rcpp::as<Rcpp::IntegerVector>(cvids.wrap());
  impl::filter(Vattr_, impl::negate(idx, vcount()));
  igraph_delete_vertices(data_.get(), cvids.vss());
}

Rcpp::DataFrame IGraph::as_data_frame() const {
  auto df = Rcpp::DataFrame::create(
    Rcpp::_["from"] = from(),
    Rcpp::_["to"] = to()
  );
  const long n = Eattr_.ncol();
  const Rcpp::StringVector names = Eattr_.attr("names");
  for (long i = 0; i < n; ++i) {
    impl::mutate(df, names[i], Eattr_[i]);
  }
  df.attr("class") = impl::tibble_class();
  return df;
}

void IGraph::mutate_Vattr(const char* name, const Rcpp::RObject& value) {
  impl::mutate(Vattr_, name, value);
}

void IGraph::mutate_Eattr(const char* name, const Rcpp::RObject& value) {
  impl::mutate(Eattr_, name, value);
}

void IGraph::mutate_Vattr_layout(const Rcpp::NumericMatrix& mat) {
  mutate_Vattr("x", Rcpp::NumericVector(mat.column(0)));
  mutate_Vattr("y", Rcpp::NumericVector(mat.column(1)));
}

void IGraph::init_attr() {
  Vattr_.attr("class") = impl::tibble_class();
  Eattr_.attr("class") = impl::tibble_class();
  impl::set_rownames(Vattr_, vcount());
  impl::set_rownames(Eattr_, ecount());
}
