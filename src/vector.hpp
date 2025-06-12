#pragma once
#ifndef IGRAPHLITE_VECTOR_HPP_
#define IGRAPHLITE_VECTOR_HPP_

#include "policy.hpp"

#include <igraph/igraph_vector.h>
#include <igraph/igraph_vector_list.h>
#include <igraph/igraph_iterators.h>
#include <cpp11/list.hpp>

template <class WrapPolicy, class StoragePolicy = InitSizeInt>
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
    auto at(const int pos) const {
      return StoragePolicy::get(data_.get(), pos);
    }
    int size() const {
      return igraph_vector_size(data_.get());
    }
    auto wrap() const {
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
class IVectorIntList {
  public:
    IVectorIntList(int n = 0) {
      igraph_vector_int_list_init(data_.get(), n);
    }
    IVectorIntList(const IVectorIntList&) = delete;
    IVectorIntList(IVectorIntList&&) = delete;
    ~IVectorIntList() noexcept {
      igraph_vector_int_list_destroy(data_.get());
    }
    void reserve(int n) {
      igraph_vector_int_list_reserve(data_.get(), n);
    }
    auto at(int pos) const {
      return WrapPolicy::wrap(igraph_vector_int_list_get_ptr(data_.get(), pos));
    }
    int size() const {
      return igraph_vector_int_list_size(data_.get());
    }
    SEXP wrap() const {
      const int len = size();
      cpp11::writable::list output;
      output.reserve(len);
      for (int i = 0; i < len; ++i) {
        output.push_back(at(i));
      }
      return output;
    }
    igraph_vector_int_list_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_vector_int_list_t> data_ = std::make_unique<igraph_vector_int_list_t>();
};

#endif // IGRAPHLITE_VECTOR_HPP_
