#pragma once
#ifndef IGRAPHLITE_VECTOR_HPP_
#define IGRAPHLITE_VECTOR_HPP_

#include <Rcpp.h>

#include <igraph/igraph_vector.h>
#include <igraph/igraph_vector_ptr.h>
#include <igraph/igraph_iterators.h>

#include "policy.hpp"

template <class WrapPolicy, class StoragePolicy = InitSize>
class IVector {
    using data_type = typename StoragePolicy::data_type;
  public:
    explicit IVector(const typename StoragePolicy::value_type& x) {
      StoragePolicy::init(data_.get(), x);
    }
    IVector(const IVector& other) = delete;
    IVector(IVector&& other) = delete;
    ~IVector() noexcept {
      StoragePolicy::destroy(data_.get());
    }
    igraph_es_t ess() const {return igraph_ess_vector(data_.get());}
    igraph_vs_t vss() const {return igraph_vss_vector(data_.get());}
    double at(long pos) const {
      return igraph_vector_e(data_.get(), pos);
    }
    long size() const {
      return igraph_vector_size(data_.get());
    }
    auto wrap() {// non-const for AsIndicesInPlace
      return WrapPolicy::wrap(data_.get());
    }
    data_type* data() {return data_.get();}
  private:
    std::unique_ptr<data_type> data_ = std::make_unique<data_type>();
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
    void init_elements(long n = 1) {
      const long len = size();
      for (long i = 0; i < len; ++i) {
        igraph_vector_t* elem = new igraph_vector_t;
        igraph_vector_init(elem, n);
        igraph_vector_ptr_set(data_.get(), i, elem);
      }
    }
    Rcpp::NumericVector at(long pos) {
      void* elem = igraph_vector_ptr_e(data_.get(), pos);
      return WrapPolicy::wrap(reinterpret_cast<igraph_vector_t*>(elem));
    }
    long size() const {
      return igraph_vector_ptr_size(data_.get());
    }
    Rcpp::List wrap() {
      const long len = size();
      Rcpp::List output(len);
      for (long i = 0; i < len; ++i) {
        output[i] = at(i);
      }
      return output;
    }
    igraph_vector_ptr_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_vector_ptr_t> data_ = std::make_unique<igraph_vector_ptr_t>();
};

#endif // IGRAPHLITE_VECTOR_HPP_
