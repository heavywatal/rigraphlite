#pragma once
#ifndef IGRAPHLITE_DATAFRAME_HPP_
#define IGRAPHLITE_DATAFRAME_HPP_

#include <unordered_set>

namespace impl {

  inline cpp11::integers RcppRange(const int start, const int end) {
    return R_compact_intrange(start, end);
  }

  inline cpp11::logicals Rcpp_in(const cpp11::integers& x, const cpp11::integers& table) {
    std::unordered_set<int> set(table.begin(), table.end());
    cpp11::writable::logicals res;
    res.reserve(x.size());
    for (const auto& elem: x) {
      res.push_back(static_cast<Rboolean>(set.find(elem) != set.end()));
    }
    return res;
  }

  inline cpp11::strings tibble_class() {
    return cpp11::writable::strings{"tbl_df", "tbl", "data.frame"};
  }

  inline void set_rownames(cpp11::data_frame& df, int n) {
    df.attr("row.names") = cpp11::writable::integers{NA_INTEGER, -n};
  }

  inline void mutate(cpp11::writable::data_frame& df, const char* name, const cpp11::sexp& value) {
    cpp11::list attr_holder;
    Rf_copyMostAttrib(df, attr_holder);
    df[cpp11::r_string(name)] = value;
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

  template <class RTYPE, class T> inline
  cpp11::r_vector<RTYPE> elongate(const cpp11::r_vector<RTYPE>& x, long n) {
    long len = x.size();
    cpp11::writable::r_vector<RTYPE> res(len + n);
    for (long i = 0; i < len; ++i) {
      res[i] = x[i];
    }
    for (long i = len; i < res.size(); ++i) {
      res[i] = na<T>();
    }
    return res;
  }

  inline cpp11::logicals negate(const cpp11::logicals& x) {
    cpp11::writable::logicals y;
    y.reserve(x.size());
    for (const auto elem: x) {
      y.push_back(static_cast<Rboolean>(!elem));
    }
    return y;
  }

  inline cpp11::logicals negate(const cpp11::integers& idx, long n) {
    return negate(Rcpp_in(RcppRange(0, n - 1), idx));
  }

  // template <class RTYPE, class T> inline
  // cpp11::r_vector<RTYPE> subset(const cpp11::r_vector<RTYPE>& x, const T& idx) {
  //   return x[idx];
  // }

  template <class T> inline
  cpp11::r_vector<T> subset(const cpp11::r_vector<T>& x, const cpp11::logicals& idx) {
    cpp11::writable::r_vector<T> res;
    for (int i = 0; i < idx.size(); ++i) {
      if (idx[i]) res.push_back(x[i]);
    }
    return res;
  }

  inline void append_na_rows(cpp11::writable::data_frame& df, long n) {
    const cpp11::strings names(df.names());
    for (const cpp11::r_string& name: names) {
      const char* cname = static_cast<std::string>(name).c_str();
      switch (TYPEOF(df[name])) {
        case INTSXP:  mutate(df, cname, elongate<int, int>(df[name], n)); break;
        case REALSXP: mutate(df, cname, elongate<double, double>(df[name], n)); break;
        case STRSXP:  mutate(df, cname, elongate<cpp11::r_string, SEXP>(df[name], n)); break;
        default: cpp11::stop("Invalid type for attributes: %d", TYPEOF(df[name]));
      }
    }
    impl::set_rownames(df, df.nrow() + n);
  }

  inline int Rcpp_sum(const cpp11::logicals& v) {
    int res;
    for (const auto x: v) {
      res += x;
    }
    return res;
  }

  inline void filter(cpp11::writable::data_frame& df, const cpp11::logicals& idx) {
    const cpp11::strings names(df.names());
    for (const cpp11::r_string& name: names) {
      const char* cname = static_cast<std::string>(name).c_str();
      switch (TYPEOF(df[name])) {
        case INTSXP:  mutate(df, cname, subset<int>(df[name], idx)); break;
        case REALSXP: mutate(df, cname, subset<double>(df[name], idx)); break;
        case STRSXP:  mutate(df, cname, subset<cpp11::r_string>(df[name], idx)); break;
        default: cpp11::stop("Invalid type for attributes: %d", TYPEOF(df[name]));
      }
    }
    impl::set_rownames(df, Rcpp_sum(idx));
  }
}

#endif // IGRAPHLITE_DATAFRAME_HPP_
