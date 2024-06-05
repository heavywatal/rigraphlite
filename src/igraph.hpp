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
    IGraph(const Rcpp::IntegerVector& edges, int n, bool directed); // create
    IGraph(int n, int mode, double center); // star
    IGraph(const Rcpp::IntegerVector& dim, int nei, bool directed, bool mutual, bool circular); // lattice
    IGraph(int n, bool directed, bool mutual, bool circular); // ring
    IGraph(int n, int children, int mode); // tree
    IGraph(int n, bool directed, bool loops); // full
    IGraph(const char* name); // famous
    IGraph(const IGraph& other, const Rcpp::IntegerVector& vids, int impl); // induced_subgraph

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
    // Basic interface

    int vcount() const;
    int ecount() const;

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
    // Original methods

    // igraph_t getter
    Rcpp::IntegerVector from() const;
    Rcpp::IntegerVector to() const;
    Rcpp::IntegerVector oi() const;
    Rcpp::IntegerVector ii() const;
    Rcpp::IntegerVector os() const;
    Rcpp::IntegerVector is() const;

    void mutate_Vattr(const char* name, const Rcpp::RObject& value);
    void mutate_Eattr(const char* name, const Rcpp::RObject& value);
    Rcpp::DataFrame Vattr_;
    Rcpp::DataFrame Eattr_;

    igraph_t* data() {return data_.get();}
    const igraph_t* data() const {return data_.get();}

  private:
    IGraph();
    void init_attr();

    std::unique_ptr<igraph_t> data_;
};

extern int vcount_(const IGraph& graph);
extern Rcpp::NumericMatrix distances_(
  const IGraph& graph, const Rcpp::IntegerVector& from, const Rcpp::IntegerVector& to,
  const Rcpp::NumericVector& weights, int mode, const std::string& algorithm);

#endif // IGRAPHLITE_IGRAPH_HPP_
