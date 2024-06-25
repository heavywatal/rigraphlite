#pragma once
#ifndef IGRAPHLITE_DATAFRAME_HPP_
#define IGRAPHLITE_DATAFRAME_HPP_

#include "cpp11.hpp"

#include <unordered_set>
#include <numeric>

namespace cpp11 {
  template <> inline
  uint8_t na<uint8_t>() {return 0;}
  template <> inline
  SEXP na<SEXP>() {return NA_STRING;}
}

namespace impl {

  inline void set_colnames(cpp11::writable::data_frame* df) {
    df->attr(R_NamesSymbol) = cpp11::writable::strings{};
  }

  inline void set_rownames(cpp11::writable::data_frame* df, int n) {
    df->attr(R_RowNamesSymbol) = cpp11::writable::integers{NA_INTEGER, -n};
  }

  inline void set_data_frame_attributes(cpp11::writable::data_frame* df, const int n) {
    set_colnames(df);
    set_rownames(df, n);
  }

  inline auto set_tbl_class(cpp11::writable::data_frame&& df) {
    df.attr(R_ClassSymbol) = {"tbl_df", "tbl", "data.frame"};
    return std::move(df);
  }

  inline auto tibble(SEXP x) {
    return set_tbl_class(cpp11::writable::data_frame(std::move(x)));
  }

  inline auto tibble(std::initializer_list<cpp11::named_arg> il) {
    return set_tbl_class(cpp11::writable::data_frame(il));
  }

  inline R_xlen_t idx_size(const cpp11::r_vector<int>& idx) {
    return idx.size();
  }

  inline R_xlen_t idx_size(const cpp11::r_vector<cpp11::r_bool>& idx) {
    R_xlen_t n = 0;
    for (const auto x: idx) n += static_cast<int>(x);
    return n;
  }

  template <class T> inline
  cpp11::r_vector<T>
  elongate_vector(const cpp11::r_vector<T>& x, const int n) {
    R_xlen_t len = x.size();
    cpp11::writable::r_vector<T> res(len + n);
    for (R_xlen_t i = 0; i < len; ++i) {
      res[i] = x[i];
    }
    for (R_xlen_t i = len; i < res.size(); ++i) {
      res[i] = cpp11::na<T>();
    }
    return res;
  }

  inline SEXP elongate(SEXP x, const int n) {
    switch (TYPEOF(x)) {
      case RAWSXP:  return elongate_vector<uint8_t>(x, n);
      case LGLSXP:  return elongate_vector<cpp11::r_bool>(x, n);
      case INTSXP:  return elongate_vector<int>(x, n);
      case REALSXP: return elongate_vector<double>(x, n);
      case STRSXP:  return elongate_vector<cpp11::r_string>(x, n);
      case VECSXP:  return elongate_vector<SEXP>(x, n);
      default: cpp11::stop("Invalid type for attributes: %d", TYPEOF(x));
    }
  }

  template <class T> inline
  cpp11::r_vector<T>
  subset_vector(const cpp11::r_vector<T>& x, const cpp11::logicals& idx, const bool negate = false) {
    cpp11::writable::r_vector<T> res;
    if (negate) {
      res.reserve(x.size() - idx_size(idx));
    } else {
      res.reserve(idx_size(idx));
    }
    const R_xlen_t n = idx.size();
    for (R_xlen_t i = 0; i < n; ++i) {
      if (static_cast<bool>(idx[i]) xor negate) res.push_back(x[i]);
    }
    return res;
  }

  template <class T> inline
  cpp11::r_vector<T>
  subset_vector(const cpp11::r_vector<T>& x, const cpp11::integers& idx, const bool negate = false) {
    cpp11::writable::r_vector<T> res;
    if (negate) {
      res.reserve(x.size() - idx.size());
      const R_xlen_t x_size1 = x.size() + 1;
      auto it = idx.begin();
      for (R_xlen_t i = 1; i < x_size1; ++i) {
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

  template <class T> inline
  SEXP subset(SEXP x, const cpp11::r_vector<T>& idx, const bool negate = false) {
    switch (TYPEOF(x)) {
      case RAWSXP:  return subset_vector<uint8_t>(x, idx, negate);
      case LGLSXP:  return subset_vector<cpp11::r_bool>(x, idx, negate);
      case INTSXP:  return subset_vector<int>(x, idx, negate);
      case REALSXP: return subset_vector<double>(x, idx, negate);
      case STRSXP:  return subset_vector<cpp11::r_string>(x, idx, negate);
      case VECSXP:  return subset_vector<SEXP>(x, idx, negate);
      default: cpp11::stop("Invalid type for attributes: %d", TYPEOF(x));
    }
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
      newcols.push_back(elongate(col, n));
    }
    const cpp11::strings names(df->names());
    *df = tibble(std::move(newcols));
    df->names() = names;
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
      newcols.push_back(subset(col, idx, negate));
    }
    const cpp11::strings names(df->names());
    *df = tibble(std::move(newcols));
    df->names() = names;
  }

  inline void mutate(cpp11::writable::list* x, const char* key, SEXP value) {
    SEXP names = PROTECT(x->names());
    R_xlen_t size = Rf_xlength(names);
    for (R_xlen_t pos = 0; pos < size; ++pos) {
      if (Rf_translateCharUTF8(STRING_ELT(names, pos)) == key) {
        UNPROTECT(1);
        (*x)[pos] = value;
        return;
      }
    }
    UNPROTECT(1);
    x->push_back({cpp11::named_arg(static_cast<std::string>(key).c_str()) = value});
  }

  inline void mutate(cpp11::writable::data_frame* x, const char* key, SEXP value) {
    cpp11::writable::list ls(std::move(*x));
    mutate(&ls, key, value);
    *x = tibble(std::move(ls));
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
