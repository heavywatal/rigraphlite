#pragma once
#ifndef IGRAPHLITE_IGRAPH_HPP_
#define IGRAPHLITE_IGRAPH_HPP_

#include <Rcpp.h>

#include "vector.hpp"

#include <igraph/igraph_interface.h>
#include <igraph/igraph_constructors.h>

class IGraph {
  public:
    ~IGraph() noexcept {
      igraph_destroy(&data_);
    }
    IGraph(const IGraph& other) {
      igraph_copy(&data_, &other.data_);
      Vattr_ = other.Vattr_;
      Eattr_ = other.Eattr_;
    }
    IGraph(IGraph&& other) {
      data_ = std::move(other.data_);
      Vattr_ = std::move(other.Vattr_);
      Eattr_ = std::move(other.Eattr_);
    }

    IGraph(int n, bool directed) {
      igraph_empty(&data_, n, directed);
      init_attr();
    }

    IGraph(const Rcpp::NumericVector& edges, int n, bool directed) {
      igraph_create(&data_, IVectorView(edges).data(), n, directed);
      init_attr();
    }

    // Workaround: Rcpp Module cannot expose constructors with default values
    static IGraph create(const Rcpp::NumericVector& edges, int n, bool directed) {
      return IGraph(edges, n, directed);
    }
    static IGraph tree(int n, int children, int mode) {
      IGraph g;
      igraph_tree(g.data(), n, children, static_cast<igraph_tree_mode_t>(mode));
      g.init_attr();
      return g;
    }

    void init_attr() {
      Rcpp::StringVector cls{"tbl_df", "tbl", "data.frame"};
      Vattr_.attr("class") = cls;
      Eattr_.attr("class") = cls;
      Vattr_.attr("row.names") = Rcpp::seq_len(vcount());
      Eattr_.attr("row.names") = Rcpp::seq_len(ecount());
    }

    void setV(Rcpp::DataFrame other) {Vattr_ = other;}
    void setE(Rcpp::DataFrame other) {Eattr_ = other;}
    igraph_t* data() {return &data_;}

    bool is_directed() const {return igraph_is_directed(&data_);}
    Rcpp::NumericVector from() const {return as_rvector(data_.from) + 1;}
    Rcpp::NumericVector to() const {return as_rvector(data_.to) + 1;}
    long vcount() const {return igraph_vcount(&data_);}
    long ecount() const {return igraph_ecount(&data_);}

    const igraph_t* data() const {return &data_;}
    Rcpp::DataFrame getV() const {return Vattr_;}
    Rcpp::DataFrame getE() const {return Eattr_;}

  private:
    IGraph() = default;

    igraph_t data_;
    Rcpp::DataFrame Vattr_;
    Rcpp::DataFrame Eattr_;
};

#endif // IGRAPHLITE_IGRAPH_HPP_
