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

    // empty
    IGraph(int n, bool directed);

    // create
    IGraph(const cpp11::integers& edges, int n, bool directed);

    // star
    IGraph(int n, int mode, double center);

    // lattice
    IGraph(const cpp11::integers& dim, int nei, bool directed, bool mutual, bool circular);

    // ring
    IGraph(int n, bool directed, bool mutual, bool circular);

    // tree
    IGraph(int n, int children, int mode);

    // full
    IGraph(int n, bool directed, bool loops);

    // famous
    IGraph(const char* name);

    // induced_subgraph
    IGraph(const IGraph& other, const cpp11::integers& vids, int impl);

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
    // Basic interface

    int vcount() const;
    int ecount() const;

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
    // Original methods

    SEXP V() const;
    SEXP E() const;
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

#endif // IGRAPHLITE_IGRAPH_HPP_
