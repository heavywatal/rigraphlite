#pragma once
#ifndef IGRAPHLITE_MATRIX_HPP_
#define IGRAPHLITE_MATRIX_HPP_

#include "cpp11.hpp"

#include <igraph/igraph_matrix.h>

#include <memory>

class IMatrix {
  public:
    IMatrix(long nrow, long ncol): robj_(nrow, ncol) {
      igraph_vector_view(&data_->data, &(robj_[0]), nrow * ncol);
      data_->nrow = nrow;
      data_->ncol = ncol;
    }
    IMatrix(cpp11::doubles_matrix&& obj): robj_(std::move(obj)) {
      igraph_vector_view(&data_->data, &(robj_[0]), robj_.nrow() * robj_.ncol());
      data_->nrow = robj_.nrow();
      data_->ncol = robj_.ncol();
    }
    IMatrix(const IMatrix& other) noexcept = delete;
    IMatrix(IMatrix&& other) noexcept = delete;
    ~IMatrix() noexcept = default;
    void rownames(const cpp11::strings& x) {Rcpp::rownames(robj_) = x;}
    void colnames(const cpp11::strings& x) {Rcpp::colnames(robj_) = x;}
    double at(long i, long j) const {return MATRIX(*data_, i, j);}
    cpp11::doubles_matrix wrap() const {return robj_;}
    igraph_matrix_t* data() {return data_.get();}
  private:
    cpp11::doubles_matrix robj_;
    std::unique_ptr<igraph_matrix_t> data_ = std::make_unique<igraph_matrix_t>();
};

#endif // IGRAPHLITE_MATRIX_HPP_
