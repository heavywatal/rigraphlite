#pragma once
#ifndef IGRAPHLITE_VECTOR_HPP_
#define IGRAPHLITE_VECTOR_HPP_

#include <Rcpp.h>

#include <igraph/igraph_vector.h>
#include <igraph/igraph_vector_ptr.h>
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

struct AsValues {
  Rcpp::NumericVector operator()(igraph_vector_t* x) const {
    return Rcpp::NumericVector(x->stor_begin, x->end);
  }
};

struct AsIndices {
  Rcpp::NumericVector operator()(igraph_vector_t* x) const {
    igraph_vector_add_constant(x, 1.0);
    return Rcpp::NumericVector(x->stor_begin, x->end);
  }
};

class IVector {
  public:
    IVector(long n = 0) {
      igraph_vector_init(data_.get(), n);
    }
    IVector(const IVector& other) = delete;
    IVector(IVector&& other) = delete;
    ~IVector() noexcept {
      igraph_vector_destroy(data_.get());
    }
    operator Rcpp::NumericVector() const {return as_rvector(*data_);}
    igraph_vector_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_vector_t> data_ = std::make_unique<igraph_vector_t>();
};

class IVectorView {
  public:
    IVectorView(const Rcpp::NumericVector& x) {
      igraph_vector_view(data_.get(), &(x[0]), x.size());
    }
    IVectorView(const IVector& other) = delete;
    IVectorView(IVector&& other) = delete;
    ~IVectorView() noexcept = default;
    igraph_vector_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_vector_t> data_ = std::make_unique<igraph_vector_t>();
};

template <class Converter>
class IVectorPtr {
  public:
    IVectorPtr(long n = 0) {
      igraph_vector_ptr_init(data_.get(), n);
    }
    IVectorPtr(const IVectorPtr&) = delete;
    IVectorPtr(IVectorPtr&&) = delete;
    ~IVectorPtr() noexcept {
      igraph_vector_ptr_destroy(data_.get());
    }
    operator Rcpp::List() const {
      const long n = igraph_vector_ptr_size(data_.get());
      Rcpp::List output(n);
      for (long i = 0; i < n; ++i) {
        auto elem = reinterpret_cast<igraph_vector_t*>(igraph_vector_ptr_e(data_.get(), i));
        output[i] = convert_(elem);
      }
      return output;
    }
    igraph_vector_ptr_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_vector_ptr_t> data_ = std::make_unique<igraph_vector_ptr_t>();
    Converter convert_;
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

class ISelector {
  public:
    template <int RTYPE>
    ISelector(const Rcpp::Vector<RTYPE>& x):
      robj_(x - 1.0) {
      // +1 to the copy; otherwise x in the parent environment is affected
      igraph_vector_view(data_.get(), &(robj_[0]), robj_.size());
    }
    ISelector(const ISelector&) = delete;
    ISelector(ISelector&&) = delete;
    ~ISelector() noexcept = default;
    operator igraph_es_t() const {return igraph_ess_vector(data_.get());}
    operator igraph_vs_t() const {return igraph_vss_vector(data_.get());}
    igraph_vector_t* data() {return data_.get();}
  private:
    const Rcpp::NumericVector robj_;
    std::unique_ptr<igraph_vector_t> data_ = std::make_unique<igraph_vector_t>();
};

#endif // IGRAPHLITE_VECTOR_HPP_
