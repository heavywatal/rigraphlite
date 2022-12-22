#pragma once
#ifndef IGRAPHLITE_DATAFRAME_HPP_
#define IGRAPHLITE_DATAFRAME_HPP_

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
  Rcpp::Vector<RTYPE> elongate(const Rcpp::Vector<RTYPE>& x, int n) {
    int len = x.size();
    Rcpp::Vector<RTYPE> res(len + n);
    for (int i = 0; i < len; ++i) {
      res[i] = x[i];
    }
    for (int i = len; i < res.size(); ++i) {
      res[i] = na<T>();
    }
    return res;
  }

  inline Rcpp::LogicalVector negate(const Rcpp::IntegerVector& idx, int n) {
    return !Rcpp::in(Rcpp::Range(0, n - 1), idx);
  }

  template <int RTYPE, class T> inline
  Rcpp::Vector<RTYPE> subset(const Rcpp::Vector<RTYPE>& x, const T& idx) {
    return x[idx];
  }

  inline void append_na_rows(Rcpp::DataFrame& df, int n) {
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

#endif // IGRAPHLITE_DATAFRAME_HPP_
