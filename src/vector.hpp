#pragma once
#ifndef IGRAPHLITE_VECTOR_HPP_
#define IGRAPHLITE_VECTOR_HPP_

#include <Rcpp.h>

#include <igraph/igraph_vector.h>
#include <igraph/igraph_vector_ptr.h>
#include <igraph/igraph_iterators.h>

struct AsValues {
  static Rcpp::NumericVector wrap(const igraph_vector_t* x) {
    return Rcpp::NumericVector(x->stor_begin, x->end);
  }
};

struct AsIndices {
  static Rcpp::NumericVector wrap(const igraph_vector_t* x) {
    return Rcpp::NumericVector(x->stor_begin, x->end) + 1.0;
  }
};

struct AsIndicesInPlace {
  static Rcpp::NumericVector wrap(igraph_vector_t* x) {
    igraph_vector_add_constant(x, 1.0);
    return Rcpp::NumericVector(x->stor_begin, x->end);
  }
};

template <class WrapPolicy>
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
    operator Rcpp::NumericVector() {// non-const for AsIndicesInPlace
      return WrapPolicy::wrap(data_.get());
    }
    igraph_vector_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_vector_t> data_ = std::make_unique<igraph_vector_t>();
};

class IVectorView {
  public:
    IVectorView(const Rcpp::NumericVector& x) {
      igraph_vector_view(data_.get(), &(x[0]), x.size());
    }
    IVectorView(const IVectorView& other) = delete;
    IVectorView(IVectorView&& other) = delete;
    ~IVectorView() noexcept = default;
    igraph_vector_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_vector_t> data_ = std::make_unique<igraph_vector_t>();
};

template <class WrapPolicy>
class IVectorPtr {
  public:
    IVectorPtr(long n = 0) {
      igraph_vector_ptr_init(data_.get(), n);
      igraph_vector_ptr_set_item_destructor(data_.get(),
        reinterpret_cast<igraph_finally_func_t*>(igraph_vector_destroy));
    }
    IVectorPtr(const IVectorPtr&) = delete;
    IVectorPtr(IVectorPtr&&) = delete;
    ~IVectorPtr() noexcept {
      igraph_vector_ptr_destroy_all(data_.get());
    }
    operator Rcpp::List() const {
      const long n = igraph_vector_ptr_size(data_.get());
      Rcpp::List output(n);
      for (long i = 0; i < n; ++i) {
        auto elem = reinterpret_cast<igraph_vector_t*>(igraph_vector_ptr_e(data_.get(), i));
        output[i] = WrapPolicy::wrap(elem);
      }
      return output;
    }
    igraph_vector_ptr_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_vector_ptr_t> data_ = std::make_unique<igraph_vector_ptr_t>();
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
