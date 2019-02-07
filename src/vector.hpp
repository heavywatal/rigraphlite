#pragma once
#ifndef IGRAPHLITE_VECTOR_HPP_
#define IGRAPHLITE_VECTOR_HPP_

#include <Rcpp.h>

#include <igraph/igraph_vector.h>
#include <igraph/igraph_strvector.h>
#include <igraph/igraph_iterators.h>

#include <memory>

inline Rcpp::StringVector as_rvector(const igraph_strvector_t& x) {
  const long n = igraph_strvector_size(&x);
  Rcpp::StringVector output(n);
  for (long i = 0; i < n; ++i) {
    output[i] = x.data[i];
  }
  return output;
}

inline Rcpp::NumericVector as_rvector(const igraph_vector_t& x) {
  return Rcpp::NumericVector(x.stor_begin, x.end);
}

class IVector {
  public:
    IVector(long n = 0) {
      igraph_vector_init(data_.get(), n);
    }
    IVector(const IVector& other) noexcept {
      igraph_vector_copy(data_.get(), other.data_.get());
    }
    IVector(IVector&& other) noexcept = default;
    ~IVector() noexcept {
      if (data_) igraph_vector_destroy(data_.get());
    }
    igraph_vs_t vss() const {return igraph_vss_vector(data_.get());}
    igraph_vector_t* data() {return data_.get();}
    operator Rcpp::NumericVector() const {return as_rvector(*data_);}
  private:
    std::unique_ptr<igraph_vector_t> data_ = std::make_unique<igraph_vector_t>();
};

class IVectorView {
  public:
    IVectorView(const Rcpp::NumericVector& x) {
      igraph_vector_view(&data_, &(x[0]), x.size());
    }
    IVectorView(const IVectorView&) noexcept = default;
    IVectorView(IVectorView&&) noexcept = default;
    ~IVectorView() noexcept = default;
    igraph_vs_t vss() const {return igraph_vss_vector(&data_);}
    igraph_vector_t* data() {return &data_;}
    operator Rcpp::NumericVector() const {return as_rvector(data_);}
  private:
    igraph_vector_t data_;
};

class IStrVector {
  public:
    IStrVector(long n = 0) {
      igraph_strvector_init(data_.get(), n);
    }
    IStrVector(const Rcpp::StringVector& x) {
      long n = x.size();
      igraph_strvector_init(data_.get(), n);
      for (long i = 0; i < n; ++i) {
        igraph_strvector_set(data_.get(), i, x[i]);
      }
    }
    IStrVector(const IStrVector& other) noexcept {
      igraph_strvector_copy(data_.get(), other.data_.get());
    }
    IStrVector(IStrVector&& other) noexcept = default;
    ~IStrVector() noexcept {
      if (data_) igraph_strvector_destroy(data_.get());
    }
    igraph_strvector_t* data() {return data_.get();}
    operator Rcpp::StringVector() const {return as_rvector(*data_);}
  private:
    std::unique_ptr<igraph_strvector_t> data_ = std::make_unique<igraph_strvector_t>();
};

#endif // IGRAPHLITE_VECTOR_HPP_
