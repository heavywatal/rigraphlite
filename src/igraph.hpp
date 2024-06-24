#pragma once
#ifndef IGRAPHLITE_IGRAPH_HPP_
#define IGRAPHLITE_IGRAPH_HPP_

#include "cpp11.hpp"

#include <memory>

typedef struct igraph_s igraph_t;

class IGraph {
  public:
    IGraph() noexcept;
    ~IGraph() noexcept;
    IGraph(const IGraph& other) noexcept;
    IGraph(IGraph&& other) = default;

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
    std::unique_ptr<igraph_t> data_;

  public:
    void init_attr();
    cpp11::writable::data_frame Vattr_;
    cpp11::writable::data_frame Eattr_;
};

#endif // IGRAPHLITE_IGRAPH_HPP_
