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

  inline R_xlen_t idx_size(const cpp11::r_vector<int>& idx) {
    return idx.size();
  }

  inline R_xlen_t idx_size(const cpp11::r_vector<cpp11::r_bool>& idx) {
    int n = 0;
    for (const auto x: idx) n += static_cast<int>(x);
    return n;
  }

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
  cpp11::r_vector<T> subset(const cpp11::r_vector<T>& x, const cpp11::logicals& idx, const bool negate = false) {
    cpp11::writable::r_vector<T> res;
    if (negate) {
      res.reserve(x.size() - idx_size(idx));
    } else {
      res.reserve(idx_size(idx));
    }
    for (int i = 0; i < idx.size(); ++i) {
      if (static_cast<bool>(idx[i]) xor negate) res.push_back(x[i]);
    }
    return res;
  }

  template <class T> inline
  cpp11::r_vector<T> subset(const cpp11::r_vector<T>& x, const cpp11::integers& idx, const bool negate = false) {
    cpp11::writable::r_vector<T> res;
    if (negate) {
      res.reserve(x.size() - idx.size());
      const int x_size1 = x.size() + 1;
      auto it = idx.begin();
      for (int i = 1; i < x_size1; ++i) {
        if (it != idx.end() && i == *it) {
          ++it;
        } else {
          res.push_back(x[i - 1]);
        }
      }
    } else {
      res.reserve(idx.size());
      for (int i: idx) {
        res.push_back(x[--i]);
      }
    }
    return res;
  }

  inline void append_na_rows(cpp11::writable::data_frame* df, int n) {
    const auto ncol = df->size();
    if (ncol == 0) {
      set_rownames(df, df->nrow() + n);
      return;
    }
    cpp11::writable::list newcols;
    newcols.reserve(ncol);
    for (const auto col: *df) {
      switch (TYPEOF(col)) {
        case INTSXP:  newcols.push_back(elongate<int, int>(col, n)); break;
        case REALSXP: newcols.push_back(elongate<double, double>(col, n)); break;
        case STRSXP:  newcols.push_back(elongate<cpp11::r_string, SEXP>(col, n)); break;
        default: cpp11::stop("Invalid type for attributes: %d", TYPEOF(col));
      }
    }
    const cpp11::strings names(df->names());
    *df = cpp11::writable::data_frame(std::move(newcols));
    df->names() = names;
    set_tbl_class(df);
  }

  template <class T>
  inline void filter(cpp11::writable::data_frame* df, const cpp11::r_vector<T>& idx, bool negate = false) {
    const auto ncol = df->size();
    if (ncol == 0) {
      if (negate) {
        set_rownames(df, df->nrow() - idx_size(idx));
      } else {
        set_rownames(df, idx_size(idx));
      }
      return;
    }
    cpp11::writable::list newcols;
    newcols.reserve(ncol);
    for (const auto col: *df) {
      switch (TYPEOF(col)) {
        case INTSXP:  newcols.push_back(subset<int>(col, idx, negate)); break;
        case REALSXP: newcols.push_back(subset<double>(col, idx, negate)); break;
        case STRSXP:  newcols.push_back(subset<cpp11::r_string>(col, idx, negate)); break;
        default: cpp11::stop("Invalid type for attributes: %d", TYPEOF(col));
      }
    }
    const cpp11::strings names(df->names());
    *df = cpp11::writable::data_frame(std::move(newcols));
    df->names() = names;
    set_tbl_class(df);
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

  template <class T>
  inline cpp11::logicals R_in(const cpp11::r_vector<T>& x, const cpp11::r_vector<T>& table) {
    std::unordered_set<T> set(table.begin(), table.end());
    return transform(x, [&set](T i) {return cpp11::r_bool(set.find(i) != set.end());});
  }

}

inline cpp11::logicals operator|(const cpp11::logicals& x, const cpp11::logicals& y) {
  return impl::transform(x, y, [](cpp11::r_bool l, cpp11::r_bool r) {return cpp11::r_bool(l || r);});
}

#endif // IGRAPHLITE_DATAFRAME_HPP_
