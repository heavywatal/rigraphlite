#pragma once
#ifndef IGRAPHLITE_MATRIX_HPP_
#define IGRAPHLITE_MATRIX_HPP_

#include <Rcpp.h>

#include <igraph/igraph_matrix.h>

class IMatrix {
  public:
    IMatrix(long nrow, long ncol) {
      igraph_matrix_init(&data_, nrow, ncol);
    }
    ~IMatrix() {
      igraph_matrix_destroy(&data_);
    }
    operator Rcpp::NumericMatrix() const {
      return Rcpp::NumericMatrix(data_.nrow, data_.ncol, data_.data.stor_begin);
    }
    igraph_matrix_t* data() {return &data_;}
  private:
    igraph_matrix_t data_;
};

#endif // IGRAPHLITE_MATRIX_HPP_
