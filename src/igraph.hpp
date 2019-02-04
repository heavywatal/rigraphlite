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
    IGraph(const IGraph& other) noexcept {
      igraph_copy(&data_, &other.data_);
    }
    IGraph(IGraph&&) noexcept = default;

    IGraph(igraph_t&& data) noexcept: data_(std::move(data)) {}

    IGraph(int n, bool directed) {
      igraph_empty(&data_, n, directed);
    }

    IGraph(const Rcpp::NumericVector& edges, int n, bool directed) {
      igraph_create(&data_, IVectorView(edges).data(), n, directed);
    }

    // Workaround: Rcpp Module cannot expose constructors with default values
    static IGraph create(const Rcpp::NumericVector& edges, int n, bool directed) {
      return IGraph(edges, n, directed);
    }
    static IGraph tree(int n, int children, int mode) {
      IGraph g;
      igraph_tree(g.data(), n, children, static_cast<igraph_tree_mode_t>(mode));
      return g;
    }

    bool is_directed() const {return igraph_is_directed(&data_);}
    Rcpp::NumericVector from() const {return as_rvector(data_.from) + 1;}
    Rcpp::NumericVector to() const {return as_rvector(data_.to) + 1;}
    long vcount() const {return igraph_vcount(&data_);}
    long ecount() const {return igraph_ecount(&data_);}
    igraph_t* data() {return &data_;}
    const igraph_t* data() const {return &data_;}
  private:
    IGraph() = default;
    igraph_t data_;
};

#endif // IGRAPHLITE_IGRAPH_HPP_
