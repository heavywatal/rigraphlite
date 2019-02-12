#pragma once
#ifndef IGRAPHLITE_MATRIX_HPP_
#define IGRAPHLITE_MATRIX_HPP_

#include <Rcpp.h>

#include <igraph/igraph_matrix.h>

#include <memory>

class IMatrix {
  public:
    IMatrix(long nrow, long ncol): robj_(nrow, ncol) {
      igraph_vector_view(&data_->data, &(robj_[0]), nrow * ncol);
      data_->nrow = nrow;
      data_->ncol = ncol;
    }
    IMatrix(const IMatrix& other) noexcept = delete;
    IMatrix(IMatrix&& other) noexcept = delete;
    ~IMatrix() noexcept = default;
    operator Rcpp::NumericMatrix() {return robj_;}
    igraph_matrix_t* data() {return data_.get();}
  private:
    Rcpp::NumericMatrix robj_;
    std::unique_ptr<igraph_matrix_t> data_ = std::make_unique<igraph_matrix_t>();
};

#endif // IGRAPHLITE_MATRIX_HPP_
