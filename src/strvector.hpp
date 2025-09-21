#pragma once
#ifndef IGRAPHLITE_STRVECTOR_HPP_
#define IGRAPHLITE_STRVECTOR_HPP_

#include <igraph/igraph_strvector.h>
#include <cpp11/strings.hpp>

class IStrVector {
  public:
    IStrVector(igraph_int_t n = 0) {
      igraph_strvector_init(data_.get(), n);
    }
    IStrVector(const cpp11::strings& x) {
      const auto n = x.size();
      igraph_strvector_init(data_.get(), n);
      for (igraph_int_t i = 0; i < n; ++i) {
        igraph_strvector_set(data_.get(), i, std::string(x[i]).c_str());
      }
    }
    IStrVector(const IStrVector& other) noexcept {
      igraph_strvector_init_copy(data_.get(), other.data_.get());
    }
    IStrVector(IStrVector&& other) noexcept = default;
    ~IStrVector() noexcept {
      if (data_) igraph_strvector_destroy(data_.get());
    }
    const char* at(igraph_int_t pos) const {
      return igraph_strvector_get(data_.get(), pos);
    }
    igraph_int_t size() const {
      return igraph_strvector_size(data_.get());
    }
    SEXP wrap() const {
      const auto n = size();
      cpp11::writable::strings output(n);
      for (igraph_int_t i = 0; i < n; ++i) {
        output[i] = at(i);
      }
      return output;
    }
    igraph_strvector_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_strvector_t> data_ = std::make_unique<igraph_strvector_t>();
};

#endif // IGRAPHLITE_STRVECTOR_HPP_
