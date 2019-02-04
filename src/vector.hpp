#pragma once
#ifndef IGRAPHLITE_VECTOR_HPP_
#define IGRAPHLITE_VECTOR_HPP_

#include <Rcpp.h>

#include <igraph/igraph_vector.h>
#include <igraph/igraph_strvector.h>

inline Rcpp::StringVector as_rvector(const igraph_strvector_t& x) {
  const int n = igraph_strvector_size(&x);
  Rcpp::StringVector output(n);
  for (int i = 0; i < n; ++i) {
    output[i] = x.data[i];
  }
  return output;
}

inline Rcpp::NumericVector as_rvector(const igraph_vector_t& x) {
  return Rcpp::NumericVector(x.stor_begin, x.end);
}

class IVector {
  public:
    IVector(int n = 0) {
      igraph_vector_init(&data_, n);
    }
    ~IVector() {
      igraph_vector_destroy(&data_);
    }
    igraph_vector_t* data() {return &data_;}
    operator Rcpp::NumericVector() {return as_rvector(data_);}
  private:
    igraph_vector_t data_;
};

class IVectorView {
  public:
    IVectorView(const Rcpp::NumericVector& x) {
      igraph_vector_view(&data_, &(x[0]), x.size());
    }
    ~IVectorView() = default;
    igraph_vector_t* data() {return &data_;}
    operator Rcpp::NumericVector() {return as_rvector(data_);}
  private:
    igraph_vector_t data_;
};

class IStrVector {
  public:
    IStrVector(int n = 0) {
      igraph_strvector_init(&data_, n);
    }
    IStrVector(const Rcpp::StringVector& x) {
      int n = x.size();
      igraph_strvector_init(&data_, n);
      for (int i = 0; i < n; ++i) {
        igraph_strvector_set(&data_, i, x[i]);
      }
    }
    ~IStrVector() {
      igraph_strvector_destroy(&data_);
    }
    igraph_strvector_t* data() {return &data_;}
    operator Rcpp::StringVector() {return as_rvector(data_);}
  private:
    igraph_strvector_t data_;
};

#endif // IGRAPHLITE_VECTOR_HPP_
