#pragma once
#ifndef IGRAPHLITE_VECTOR_HPP_
#define IGRAPHLITE_VECTOR_HPP_

#include <Rcpp.h>

#include <igraph/igraph_vector.h>
#include <igraph/igraph_vector_ptr.h>
#include <igraph/igraph_iterators.h>

struct InitSize {
  using value_type = long;
  static void init(igraph_vector_t* data, const value_type n) {
    igraph_vector_init(data, n);
  }
  static void destroy(igraph_vector_t* data) {
    igraph_vector_destroy(data);
  }
};

struct InitView {
  using value_type = Rcpp::NumericVector;
  static void init(igraph_vector_t* data, const value_type& x) {
    igraph_vector_view(data, &(x[0]), x.size());
  }
  static void destroy(igraph_vector_t*) {}
};

struct InitIndices {
  using value_type = Rcpp::NumericVector;
  static void init(igraph_vector_t* data, const value_type& x) {
    igraph_vector_init_copy(data, &(x[0]), x.size());
    igraph_vector_add_constant(data, -1.0);
  }
  static void destroy(igraph_vector_t* data) {
    igraph_vector_destroy(data);
  }
};

struct InitIndicesInPlace {
  using value_type = Rcpp::NumericVector;
  static void init(igraph_vector_t* data, const value_type& x) {
    // x is const, but its data is modified
    igraph_vector_view(data, &(x[0]), x.size());
    igraph_vector_add_constant(data, -1.0);
  }
  static void destroy(igraph_vector_t* data) {
    igraph_vector_add_constant(data, 1.0);
  }
};


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


template <class WrapPolicy, class StoragePolicy = InitSize>
class IVector {
  public:
    explicit IVector(const typename StoragePolicy::value_type& x) {
      StoragePolicy::init(data_.get(), x);
    }
    IVector(const IVector& other) = delete;
    IVector(IVector&& other) = delete;
    ~IVector() noexcept {
      StoragePolicy::destroy(data_.get());
    }
    operator Rcpp::NumericVector() {// non-const for AsIndicesInPlace
      return WrapPolicy::wrap(data_.get());
    }
    operator igraph_es_t() const {return igraph_ess_vector(data_.get());}
    operator igraph_vs_t() const {return igraph_vss_vector(data_.get());}
    igraph_vector_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_vector_t> data_ = std::make_unique<igraph_vector_t>();
};

using IVectorView = IVector<AsValues, InitView>;
using ISelector = IVector<AsIndices, InitIndices>;
using ISelectorInPlace = IVector<AsIndices, InitIndicesInPlace>;


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

#endif // IGRAPHLITE_VECTOR_HPP_
