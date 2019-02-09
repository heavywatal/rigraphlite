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
    IGraph(IGraph&& other);

    IGraph(int n, bool directed); // empty
    IGraph(const Rcpp::NumericVector& edges, int n, bool directed); // create
    IGraph(int n, int children, int mode); // tree
    IGraph(const IGraph& other, const Rcpp::NumericVector& vids, int impl); // induced_subgraph

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
    Rcpp::NumericMatrix shortest_paths(
      const Rcpp::NumericVector& from, const Rcpp::NumericVector& to,
      const Rcpp::NumericVector& weights, int mode, const std::string& algorithm) const;
    Rcpp::NumericVector path_length_hist(bool directed) const;
    Rcpp::NumericVector neighborhood_size(const Rcpp::NumericVector& vids, int order, int mode) const;

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////

    Rcpp::NumericMatrix edgelist() const {return Rcpp::cbind(from(), to());}
    Rcpp::NumericVector from() const;
    Rcpp::NumericVector to() const;

    igraph_t* data() {return data_.get();}
    void setV(const char* name, Rcpp::RObject value);
    void setE(const char* name, Rcpp::RObject value);
    void setV(Rcpp::DataFrame other) {Vattr_ = other;}
    void setE(Rcpp::DataFrame other) {Eattr_ = other;}

    const igraph_t* data() const {return data_.get();}
    Rcpp::DataFrame getV() const {return Vattr_;}
    Rcpp::DataFrame getE() const {return Eattr_;}

  private:
    IGraph();
    void init_attr();

    std::unique_ptr<igraph_t> data_;
    Rcpp::DataFrame Vattr_;
    Rcpp::DataFrame Eattr_;
};

#endif // IGRAPHLITE_IGRAPH_HPP_
