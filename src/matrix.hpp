#pragma once
#ifndef IGRAPHLITE_MATRIX_HPP_
#define IGRAPHLITE_MATRIX_HPP_

#include "cpp11.hpp"

#include <igraph/igraph_matrix.h>

#include <memory>

class IMatrix {
  public:
    IMatrix(int nrow, int ncol): robj_(cpp11::writable::doubles_matrix<>(nrow, ncol)) {
      igraph_vector_view(&data_->data, REAL(robj_.data()), nrow * ncol);
      data_->nrow = nrow;
      data_->ncol = ncol;
    }
    IMatrix(SEXP obj): robj_(obj) {
      igraph_vector_view(&data_->data, REAL(robj_.data()), robj_.nrow() * robj_.ncol());
      data_->nrow = robj_.nrow();
      data_->ncol = robj_.ncol();
    }
    IMatrix(const IMatrix& other) noexcept = delete;
    IMatrix(IMatrix&& other) noexcept = delete;
    ~IMatrix() noexcept = default;
    double at(int i, int j) const {return MATRIX(*data_, i, j);}
    SEXP wrap() const {return robj_;}
    igraph_matrix_t* data() {return data_.get();}
  private:
    const cpp11::doubles_matrix<> robj_;
    std::unique_ptr<igraph_matrix_t> data_ = std::make_unique<igraph_matrix_t>();
};

#endif // IGRAPHLITE_MATRIX_HPP_
