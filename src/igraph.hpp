#pragma once
#ifndef IGRAPHLITE_IGRAPH_HPP_
#define IGRAPHLITE_IGRAPH_HPP_

#include <Rcpp.h>

#include <memory>

typedef struct igraph_s igraph_t;

class IGraph {
  public:
    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
    // Graph generators

    ~IGraph() noexcept;
    IGraph(const IGraph& other) noexcept;
    IGraph(IGraph&& other) = default;

    IGraph(int n, bool directed);
    IGraph(const Rcpp::NumericVector& edges, int n, bool directed);

    // Workaround: Rcpp Module cannot expose constructors with default values
    static IGraph create(const Rcpp::NumericVector& edges, int n, bool directed);
    static IGraph tree(int n, int children, int mode);

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
    // Basic interface

    long vcount() const;
    long ecount() const;
    Rcpp::NumericVector neighbors(int node, int mode) const;
    bool is_directed() const;
    Rcpp::NumericVector degree(const Rcpp::NumericVector& vids, int mode, bool loops) const;

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
    // Structural properties

    Rcpp::LogicalVector are_connected(int v1, int v2) const;
    Rcpp::NumericMatrix shortest_paths(const Rcpp::NumericVector& from, const Rcpp::NumericVector& to, int mode) const;
    Rcpp::NumericMatrix shortest_paths_dijkstra(
      const Rcpp::NumericVector& from, const Rcpp::NumericVector& to,
      const Rcpp::NumericVector& weights, int mode) const;
    Rcpp::NumericVector neighborhood_size(const Rcpp::NumericVector& vids, int order, int mode) const;

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////

    void init_attr();

    Rcpp::NumericMatrix edgelist() const {return Rcpp::cbind(from(), to());}
    Rcpp::NumericVector from() const;
    Rcpp::NumericVector to() const;

    igraph_t* data() {return data_.get();}
    void setV(Rcpp::DataFrame other) {Vattr_ = other;}
    void setE(Rcpp::DataFrame other) {Eattr_ = other;}

    const igraph_t* data() const {return data_.get();}
    Rcpp::DataFrame getV() const {return Vattr_;}
    Rcpp::DataFrame getE() const {return Eattr_;}

  private:
    IGraph() = default;

    std::unique_ptr<igraph_t> data_ = std::make_unique<igraph_t>();
    Rcpp::DataFrame Vattr_;
    Rcpp::DataFrame Eattr_;
};

#endif // IGRAPHLITE_IGRAPH_HPP_
