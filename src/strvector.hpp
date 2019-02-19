#pragma once
#ifndef IGRAPHLITE_STRVECTOR_HPP_
#define IGRAPHLITE_STRVECTOR_HPP_

#include <Rcpp.h>

#include <igraph/igraph_strvector.h>

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
    const char* at(long pos) const {
      return data_->data[pos];
    }
    long size() const {
      return igraph_strvector_size(data_.get());
    }
    Rcpp::StringVector wrap() const {
      const long n = size();
      Rcpp::StringVector output(n);
      for (long i = 0; i < n; ++i) {
        output[i] = at(i);
      }
      return output;
    }
    igraph_strvector_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_strvector_t> data_ = std::make_unique<igraph_strvector_t>();
};

#endif // IGRAPHLITE_STRVECTOR_HPP_
