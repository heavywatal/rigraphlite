#include "igraph.hpp"
#include "vector.hpp"

#include <igraph/igraph_interface.h>

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
