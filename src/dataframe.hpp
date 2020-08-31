#pragma once
#ifndef IGRAPHLITE_DATAFRAME_HPP_
#define IGRAPHLITE_DATAFRAME_HPP_

#include <unordered_set>
#include <numeric>

namespace impl {
  template <class T, class Fn>
  inline decltype(auto) transform(const cpp11::r_vector<T>& v, Fn&& fn) {
    cpp11::writable::r_vector<decltype(fn(v[0]))> res(v.size());
    std::transform(v.begin(), v.end(), res.begin(), fn);
    return res;
  }

  inline cpp11::logicals Rcpp_in(const cpp11::integers& x, const cpp11::integers& table) {
    std::unordered_set<int> set(table.begin(), table.end());
    return transform(x, [&set](int i) {return cpp11::r_bool(set.find(i) != set.end());});
  }

  inline int Rcpp_sum(const cpp11::logicals& v) {
    return std::accumulate(v.begin(), v.end(), 0, [](int s, cpp11::r_bool b) {
      return s + int(b);
    });
  }

  inline cpp11::strings tibble_class() {
    return cpp11::writable::strings{"tbl_df", "tbl", "data.frame"};
  }

  inline void set_rownames(cpp11::writable::data_frame& df, int n) {
    df.attr("row.names") = cpp11::writable::integers{NA_INTEGER, -n};
  }

  inline void mutate(cpp11::writable::data_frame& df, const cpp11::r_string& name, const cpp11::sexp& value) {
    cpp11::list attr_holder;
    cpp11::safe[Rf_copyMostAttrib](df, attr_holder);
    // SEXP new_p = value;
    // SEXP old_p = df[name];
    // old_p = new_p;
    cpp11::safe[Rf_copyMostAttrib](attr_holder, df);
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
  cpp11::r_vector<RTYPE> elongate(const cpp11::r_vector<RTYPE>& x, int n) {
    int len = x.size();
    cpp11::writable::r_vector<RTYPE> res(len + n);
    for (int i = 0; i < len; ++i) {
      res[i] = x[i];
    }
    for (int i = len; i < res.size(); ++i) {
      res[i] = na<T>();
    }
    return res;
  }

  inline cpp11::r_bool negate(const cpp11::r_bool x) {
    return x == TRUE ? FALSE : TRUE;
  }

  inline cpp11::logicals negate(const cpp11::logicals& x) {
    return transform(x, [](cpp11::r_bool b) {return negate(b);});
  }

  inline cpp11::logicals negate(const cpp11::integers& idx, int n) {
    std::unordered_set<int> set(idx.begin(), idx.end());
    cpp11::writable::logicals res;
    res.reserve(n);
    for (int i=0; i<n; ++i) {
      res.push_back(static_cast<Rboolean>(set.find(i) == set.end()));
    }
    return res;
  }

  template <class T> inline
  cpp11::r_vector<T> subset(const cpp11::r_vector<T>& x, const cpp11::logicals& idx) {
    cpp11::writable::r_vector<T> res;
    for (int i = 0; i < idx.size(); ++i) {
      if (idx[i]) res.push_back(x[i]);
    }
    return res;
  }

  inline void append_na_rows(cpp11::writable::data_frame& df, int n) {
    const cpp11::strings names(df.names());
    for (const cpp11::r_string& name: names) {
      switch (TYPEOF(df[name])) {
        case INTSXP:  mutate(df, name, elongate<int, int>(df[name], n)); break;
        case REALSXP: mutate(df, name, elongate<double, double>(df[name], n)); break;
        case STRSXP:  mutate(df, name, elongate<cpp11::r_string, SEXP>(df[name], n)); break;
        default: cpp11::stop("Invalid type for attributes: %d", TYPEOF(df[name]));
      }
    }
    impl::set_rownames(df, df.nrow() + n);
  }

  inline void filter(cpp11::writable::data_frame& df, const cpp11::logicals& idx) {
    const cpp11::strings names(df.names());
    for (const cpp11::r_string& name: names) {
      switch (TYPEOF(df[name])) {
        case INTSXP:  mutate(df, name, subset<int>(df[name], idx)); break;
        case REALSXP: mutate(df, name, subset<double>(df[name], idx)); break;
        case STRSXP:  mutate(df, name, subset<cpp11::r_string>(df[name], idx)); break;
        default: cpp11::stop("Invalid type for attributes: %d", TYPEOF(df[name]));
      }
    }
    impl::set_rownames(df, Rcpp_sum(idx));
  }
}

#endif // IGRAPHLITE_DATAFRAME_HPP_
