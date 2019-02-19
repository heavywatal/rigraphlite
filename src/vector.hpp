#pragma once
#ifndef IGRAPHLITE_VECTOR_HPP_
#define IGRAPHLITE_VECTOR_HPP_

#include <Rcpp.h>

#include <igraph/igraph_vector.h>
#include <igraph/igraph_vector_ptr.h>
#include <igraph/igraph_iterators.h>
#include <igraph/igraph_adjlist.h>

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
    igraph_es_t ess() const {return igraph_ess_vector(data_.get());}
    igraph_vs_t vss() const {return igraph_vss_vector(data_.get());}
    double at(long pos) const {
      return igraph_vector_e(data_.get(), pos);
    }
    long size() const {
      return igraph_vector_size(data_.get());
    }
    Rcpp::NumericVector wrap() {// non-const for AsIndicesInPlace
      return WrapPolicy::wrap(data_.get());
    }
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

template <class WrapPolicy>
class IAdjList {
  public:
    IAdjList(const igraph_t* graph, int mode) {
      igraph_adjlist_init(graph, data_.get(), static_cast<igraph_neimode_t>(mode));
    }
    IAdjList() = delete;
    IAdjList(const IAdjList&) = delete;
    IAdjList(IAdjList&&) = delete;
    ~IAdjList() noexcept {
      if (data_) igraph_adjlist_destroy(data_.get());
    }
    Rcpp::IntegerVector at(int pos) {
      return WrapPolicy::wrap(&data_->adjs[pos]);
    }
    int size() const {
      return data_->length;
    }
    Rcpp::List wrap() {
      const int len = size();
      Rcpp::List output(len);
      for (int i = 0; i < len; ++i) {
        output[i] = at(i);
      }
      return output;
    }
    igraph_adjlist_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_adjlist_t> data_ = std::make_unique<igraph_adjlist_t>();
};

template <class WrapPolicy>
class IIncList {
  public:
    IIncList(const igraph_t* graph, int mode) {
      igraph_inclist_init(graph, data_.get(), static_cast<igraph_neimode_t>(mode));
    }
    IIncList() = delete;
    IIncList(const IIncList&) = delete;
    IIncList(IIncList&&) = delete;
    ~IIncList() noexcept {
      if (data_) igraph_inclist_destroy(data_.get());
    }
    Rcpp::IntegerVector at(int pos) {
      return WrapPolicy::wrap(&data_->incs[pos]);
    }
    int size() const {
      return data_->length;
    }
    Rcpp::List wrap() {
      const int len = size();
      Rcpp::List output(len);
      for (int i = 0; i < len; ++i) {
        output[i] = at(i);
      }
      return output;
    }
    igraph_inclist_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_inclist_t> data_ = std::make_unique<igraph_inclist_t>();
};

#endif // IGRAPHLITE_VECTOR_HPP_
