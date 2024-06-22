#pragma once
#ifndef IGRAPHLITE_DATAFRAME_HPP_
#define IGRAPHLITE_DATAFRAME_HPP_

#include <unordered_set>
#include <numeric>

namespace impl {

  inline void set_colnames(cpp11::writable::data_frame* df) {
    df->attr(R_NamesSymbol) = cpp11::writable::strings{};
  }

  inline void set_rownames(cpp11::writable::data_frame* df, int n) {
    df->attr(R_RowNamesSymbol) = cpp11::writable::integers{NA_INTEGER, -n};
  }

  inline void set_tbl_class(cpp11::writable::data_frame* df) {
    df->attr(R_ClassSymbol) = {"tbl_df", "tbl", "data.frame"};
  }

  inline void set_data_frame_attributes(cpp11::writable::data_frame* df, const int n) {
    set_colnames(df);
    set_rownames(df, n);
    set_tbl_class(df);
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

  template <class T> inline
  cpp11::r_vector<T> subset(const cpp11::r_vector<T>& x, const cpp11::logicals& idx) {
    cpp11::writable::r_vector<T> res;
    for (int i = 0; i < idx.size(); ++i) {
      if (idx[i]) res.push_back(x[i]);
    }
    return res;
  }

  template <class T> inline
  cpp11::r_vector<T> subset(const cpp11::r_vector<T>& x, const cpp11::integers& idx) {
    cpp11::writable::r_vector<T> res;
    res.reserve(idx.size());
    for (int i: idx) {
      res.push_back(x[--i]);
    }
    return res;
  }

  inline void append_na_rows(cpp11::writable::data_frame& df, int n) {
    cpp11::writable::list newcols;
    newcols.reserve(df.size());
    for (const auto col: df) {
      switch (TYPEOF(col)) {
        case INTSXP:  newcols.push_back(elongate<int, int>(col, n)); break;
        case REALSXP: newcols.push_back(elongate<double, double>(col, n)); break;
        case STRSXP:  newcols.push_back(elongate<cpp11::r_string, SEXP>(col, n)); break;
        default: cpp11::stop("Invalid type for attributes: %d", TYPEOF(col));
      }
    }
    const cpp11::strings names(df.names());
    df = cpp11::writable::data_frame(std::move(newcols));
    df.names() = names;
  }

  inline void filter(cpp11::writable::data_frame& df, const cpp11::logicals& idx) {
    cpp11::writable::list newcols;
    newcols.reserve(df.size());
    for (const auto col: df) {
      switch (TYPEOF(col)) {
        case INTSXP:  newcols.push_back(subset<int>(col, idx)); break;
        case REALSXP: newcols.push_back(subset<double>(col, idx)); break;
        case STRSXP:  newcols.push_back(subset<cpp11::r_string>(col, idx)); break;
        default: cpp11::stop("Invalid type for attributes: %d", TYPEOF(col));
      }
    }
    const cpp11::strings names(df.names());
    df = cpp11::writable::data_frame(std::move(newcols));
    df.names() = names;
  }

  template <class T, class Fn>
  inline decltype(auto) transform(const cpp11::r_vector<T>& v, Fn&& fn) {
    cpp11::writable::r_vector<decltype(fn(v[0]))> res(v.size());
    std::transform(v.begin(), v.end(), res.begin(), fn);
    return res;
  }

  template <class T, class Fn>
  inline decltype(auto) transform(const cpp11::r_vector<T>& x, const cpp11::r_vector<T>& y, Fn&& fn) {
    cpp11::writable::r_vector<decltype(fn(x[0], y[0]))> res(x.size());
    std::transform(x.begin(), x.end(), y.begin(), res.begin(), fn);
    return res;
  }

  inline cpp11::logicals negate(const cpp11::logicals& x) {
    return transform(x, [](cpp11::r_bool b) {return cpp11::r_bool(b ? FALSE : TRUE);});
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

  inline cpp11::logicals R_in(const cpp11::integers& x, const cpp11::integers& table) {
    std::unordered_set<int> set(table.begin(), table.end());
    return transform(x, [&set](int i) {return cpp11::r_bool(set.find(i) != set.end());});
  }

}

inline cpp11::logicals operator|(const cpp11::logicals& x, const cpp11::logicals& y) {
  return impl::transform(x, y, [](cpp11::r_bool l, cpp11::r_bool r) {return cpp11::r_bool(l || r);});
}

#endif // IGRAPHLITE_DATAFRAME_HPP_
