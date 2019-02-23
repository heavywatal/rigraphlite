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
    bool is_directed() const;
    Rcpp::IntegerVector edge(int eid) const;
    Rcpp::NumericVector neighbors(int node, int mode) const;
    Rcpp::NumericVector incident(int node, int mode) const;
    Rcpp::NumericVector degree(const Rcpp::NumericVector& vids, int mode, bool loops) const;

    void add_edges(const Rcpp::NumericVector& edges);
    void add_vertices(int n);
    void delete_edges(const Rcpp::NumericVector& eids);
    void delete_vertices(const Rcpp::NumericVector& vids);

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
    // Structural properties

    Rcpp::LogicalVector are_connected(int v1, int v2) const;
    Rcpp::NumericMatrix shortest_paths(
      const Rcpp::NumericVector& from, const Rcpp::NumericVector& to,
      const Rcpp::NumericVector& weights, int mode, const std::string& algorithm) const;
    Rcpp::List get_shortest_paths(
      int from, const Rcpp::NumericVector& to,
      const Rcpp::NumericVector& weights, int mode) const;
    double average_path_length(bool directed) const;
    Rcpp::NumericVector path_length_hist(bool directed) const;
    Rcpp::NumericVector neighborhood_size(const Rcpp::NumericVector& vids, int order, int mode, int mindist) const;
    Rcpp::List neighborhood(const Rcpp::NumericVector& vids, int order, int mode, int mindist) const;
    Rcpp::NumericVector subcomponent(double v, int mode) const;
    Rcpp::List subcomponents(const Rcpp::NumericVector& vids, int mode) const;

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////

    Rcpp::List as_adjlist(int mode) const;
    Rcpp::List as_inclist(int mode) const;
    Rcpp::NumericMatrix as_edgelist() const {return Rcpp::cbind(from(), to());}
    Rcpp::DataFrame as_data_frame() const;

    Rcpp::LogicalVector is_sink() const;
    Rcpp::LogicalVector is_source() const;
    Rcpp::IntegerVector sink() const;
    Rcpp::IntegerVector source() const;

    // igraph_t getter
    Rcpp::NumericVector from() const;
    Rcpp::NumericVector to() const;
    Rcpp::NumericVector oi() const;
    Rcpp::NumericVector ii() const;
    Rcpp::NumericVector os() const;
    Rcpp::NumericVector is() const;

    igraph_t* data() {return data_.get();}
    void setV(const char* name, const Rcpp::RObject& value);
    void setE(const char* name, const Rcpp::RObject& value);
    void setV(Rcpp::DataFrame other) {Vattr_ = other;}
    void setE(Rcpp::DataFrame other) {Eattr_ = other;}

    const igraph_t* data() const {return data_.get();}
    Rcpp::DataFrame getV() const {return Vattr_;}
    Rcpp::DataFrame getE() const {return Eattr_;}

    Rcpp::sugar::SeqLen V() const {return Rcpp::seq_len(vcount());}
    Rcpp::sugar::SeqLen E() const {return Rcpp::seq_len(ecount());}

  private:
    IGraph();
    void init_attr();

    std::unique_ptr<igraph_t> data_;
    Rcpp::DataFrame Vattr_;
    Rcpp::DataFrame Eattr_;
};

#endif // IGRAPHLITE_IGRAPH_HPP_
