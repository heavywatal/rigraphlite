#pragma once
#ifndef IGRAPHLITE_POLICY_HPP_
#define IGRAPHLITE_POLICY_HPP_

#include "cpp11.hpp"

#include <igraph/igraph_vector.h>

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
// StoragePolicy

struct InitSize {
  using data_type = igraph_vector_t;
  using value_type = int;
  static void init(data_type* data, const value_type n) {
    igraph_vector_init(data, n);
  }
  static void destroy(data_type* data) {
    igraph_vector_destroy(data);
  }
  static auto get(data_type* data, const int pos) {
    return igraph_vector_get(data, pos);
  }
};

struct InitSizeInt {
  using data_type = igraph_vector_int_t;
  using value_type = int;
  static void init(igraph_vector_int_t* data, const value_type n) {
    igraph_vector_int_init(data, n);
  }
  static void destroy(igraph_vector_int_t* data) {
    igraph_vector_int_destroy(data);
  }
  static auto get(data_type* data, const int pos) {
    return igraph_vector_int_get(data, pos);
  }
};

struct InitValue {
  using data_type = igraph_vector_t;
  using value_type = double;
  static void init(data_type* data, value_type x) {
    igraph_vector_init(data, 1);
    igraph_vector_set(data, 0, x);
  }
  static void destroy(data_type* data) {
    igraph_vector_destroy(data);
  }
  static auto get(data_type* data, const int pos) {
    return igraph_vector_get(data, pos);
  }
};

struct InitView {
  using data_type = igraph_vector_t;
  using value_type = cpp11::doubles;
  static void init(data_type* data, const value_type& x) {
    igraph_vector_view(data, REAL(x.data()), x.size());
  }
  static void destroy(data_type*) {}
  static auto get(data_type* data, const int pos) {
    return igraph_vector_get(data, pos);
  }
};

struct InitViewInt {
  using data_type = igraph_vector_int_t;
  using value_type = cpp11::integers;
  static void init(data_type* data, const value_type& x) {
    igraph_vector_int_view(data, INTEGER(x.data()), x.size());
  }
  static void destroy(data_type*) {}
  static auto get(data_type* data, const int pos) {
    return igraph_vector_int_get(data, pos);
  }
};

struct InitIndices {
  using data_type = igraph_vector_int_t;
  using value_type = cpp11::integers;
  static void init(data_type* data, const value_type& x) {
    igraph_vector_int_init_array(data, INTEGER(x.data()), x.size());
    igraph_vector_int_add_constant(data, -1);
  }
  static void destroy(data_type* data) {
    igraph_vector_int_destroy(data);
  }
  static auto get(data_type* data, const int pos) {
    return igraph_vector_int_get(data, pos);
  }
};

struct InitIndicesInPlace {
  using data_type = igraph_vector_int_t;
  using value_type = cpp11::integers;
  static void init(data_type* data, const value_type& x) {
    // x is const, but its data is modified
    igraph_vector_int_view(data, INTEGER(x.data()), x.size());
    igraph_vector_int_add_constant(data, -1);
  }
  static void destroy(data_type* data) {
    igraph_vector_int_add_constant(data, 1);
  }
  static auto get(data_type* data, const int pos) {
    return igraph_vector_int_get(data, pos);
  }
};

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
// WrapPolicy

struct AsValues {
  static cpp11::writable::doubles wrap(const igraph_vector_t* x) {
    return {x->stor_begin, x->end};
  }
  static cpp11::writable::integers wrap(const igraph_vector_int_t* x) {
    return {x->stor_begin, x->end};
  }
};

struct AsIndices {
  static cpp11::writable::integers wrap(const igraph_vector_int_t* x) {
    auto first = x->stor_begin;
    const auto last = x->end;
    cpp11::writable::integers v;
    v.reserve(last - first);
    while (first != last) {
      v.push_back(*first + 1);
      ++first;
    }
    return v;
  }
};

#endif // IGRAPHLITE_POLICY_HPP_
