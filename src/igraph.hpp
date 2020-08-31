#pragma once
#ifndef IGRAPHLITE_IGRAPH_HPP_
#define IGRAPHLITE_IGRAPH_HPP_

#include "cpp11.hpp"

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
    IGraph(const cpp11::integers& edges, int n, bool directed); // create
    IGraph(int n, int mode, double center); // star
    IGraph(const cpp11::integers& dim, int nei, bool directed, bool mutual, bool circular); // lattice
    IGraph(int n, bool directed, bool mutual, bool circular); // ring
    IGraph(int n, int children, int mode); // tree
    IGraph(int n, bool directed, bool loops); // full
    IGraph(const char* name); // famous
    IGraph(const IGraph& other, const cpp11::integers& vids, int impl); // induced_subgraph

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
    // Basic interface

    SEXP V() const;
    SEXP E() const;
    int vcount() const;
    int ecount() const;

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
    // Original methods

    SEXP Vnames() const;

    // igraph_t getter
    cpp11::integers from() const;
    cpp11::integers to() const;
    cpp11::integers oi() const;
    cpp11::integers ii() const;
    cpp11::integers os() const;
    cpp11::integers is() const;

    igraph_t* data() {return data_.get();}
    const igraph_t* data() const {return data_.get();}

  private:
    IGraph();
    void init_attr();

    std::unique_ptr<igraph_t> data_;

  public:
    cpp11::writable::data_frame Vattr_;
    cpp11::writable::data_frame Eattr_;
};

extern cpp11::doubles_matrix<> distances_(
  const cpp11::external_pointer<IGraph> graph, const cpp11::integers& from, const cpp11::integers& to,
  const cpp11::doubles& weights, int mode, const std::string& algorithm);

#endif // IGRAPHLITE_IGRAPH_HPP_
