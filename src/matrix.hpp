#pragma once
#ifndef IGRAPHLITE_MATRIX_HPP_
#define IGRAPHLITE_MATRIX_HPP_

#include <Rcpp.h>

#include <igraph/igraph_matrix.h>

#include <memory>

class IMatrix {
  public:
    IMatrix(long nrow, long ncol)
    : data_(std::make_unique<igraph_matrix_t>()) {
      igraph_matrix_init(data_.get(), nrow, ncol);
    }
    IMatrix(const IMatrix& other) noexcept
    : data_(std::make_unique<igraph_matrix_t>()) {
      igraph_matrix_copy(data_.get(), other.data_.get());
    }
    IMatrix(IMatrix&& other) noexcept
    : data_(std::move<>(other.data_)) {}
    ~IMatrix() noexcept {
      if (data_) igraph_matrix_destroy(data_.get());
    }
    operator Rcpp::NumericMatrix() const {
      return Rcpp::NumericMatrix(data_->nrow, data_->ncol, data_->data.stor_begin);
    }
    igraph_matrix_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_matrix_t> data_;
};

#endif // IGRAPHLITE_MATRIX_HPP_
