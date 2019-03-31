#pragma once
#ifndef IGRAPHLITE_POLICY_HPP_
#define IGRAPHLITE_POLICY_HPP_

#include <Rcpp.h>

#include <igraph/igraph_vector.h>

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
// StoragePolicy

struct InitSize {
  using data_type = igraph_vector_t;
  using value_type = long;
  static void init(data_type* data, const value_type n) {
    igraph_vector_init(data, n);
  }
  static void destroy(data_type* data) {
    igraph_vector_destroy(data);
  }
};

struct InitSizeInt {
  using data_type = igraph_vector_int_t;
  using value_type = long;
  static void init(igraph_vector_int_t* data, const value_type n) {
    igraph_vector_int_init(data, n);
  }
  static void destroy(igraph_vector_int_t* data) {
    igraph_vector_int_destroy(data);
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
};

struct InitView {
  using data_type = igraph_vector_t;
  using value_type = Rcpp::NumericVector;
  static void init(data_type* data, const value_type& x) {
    igraph_vector_view(data, &(x[0]), x.size());
  }
  static void destroy(data_type*) {}
};

struct InitIndices {
  using data_type = igraph_vector_t;
  using value_type = Rcpp::NumericVector;
  static void init(data_type* data, const value_type& x) {
    igraph_vector_init_copy(data, &(x[0]), x.size());
    igraph_vector_add_constant(data, -1.0);
  }
  static void destroy(data_type* data) {
    igraph_vector_destroy(data);
  }
};

struct InitIndicesInPlace {
  using data_type = igraph_vector_t;
  using value_type = Rcpp::NumericVector;
  static void init(data_type* data, const value_type& x) {
    // x is const, but its data is modified
    igraph_vector_view(data, &(x[0]), x.size());
    igraph_vector_add_constant(data, -1.0);
  }
  static void destroy(data_type* data) {
    igraph_vector_add_constant(data, 1.0);
  }
};

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
// WrapPolicy

struct AsValues {
  static Rcpp::NumericVector wrap(const igraph_vector_t* x) {
    return Rcpp::NumericVector(x->stor_begin, x->end);
  }
  static Rcpp::IntegerVector wrap(const igraph_vector_int_t* x) {
    return Rcpp::IntegerVector(x->stor_begin, x->end);
  }
};

struct AsIndices {
  static Rcpp::NumericVector wrap(const igraph_vector_t* x) {
    return Rcpp::NumericVector(x->stor_begin, x->end) + 1.0;
  }
  static Rcpp::IntegerVector wrap(const igraph_vector_int_t* x) {
    return Rcpp::IntegerVector(x->stor_begin, x->end) + 1;
  }
};

struct AsIndicesInPlace {
  static Rcpp::NumericVector wrap(igraph_vector_t* x) {
    igraph_vector_add_constant(x, 1.0);
    return Rcpp::NumericVector(x->stor_begin, x->end);
  }
  static Rcpp::IntegerVector wrap(igraph_vector_int_t* x) {
    igraph_vector_int_add_constant(x, 1);
    return Rcpp::IntegerVector(x->stor_begin, x->end);
  }
};

#endif // IGRAPHLITE_POLICY_HPP_
