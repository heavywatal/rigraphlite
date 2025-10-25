// <https://igraph.org/c/doc/igraph-Data-structures.html#igraph-Adjlists>
#pragma once
#ifndef IGRAPHLITE_ADJLIST_HPP_
#define IGRAPHLITE_ADJLIST_HPP_

#include "policy.hpp"

#include <igraph/igraph_adjlist.h>
#include <cpp11/list.hpp>

class IAdjList {
  public:
    IAdjList(const igraph_t* graph, int mode, int loops, bool multiple) {
      igraph_adjlist_init(graph, data_.get(), static_cast<igraph_neimode_t>(mode),
                          static_cast<igraph_loops_t>(loops), multiple);
    }
    IAdjList() = delete;
    IAdjList(const IAdjList&) = delete;
    IAdjList(IAdjList&&) = delete;
    ~IAdjList() noexcept {
      if (data_) igraph_adjlist_destroy(data_.get());
    }
    SEXP at(igraph_int_t pos) const {
      return AsIndices::wrap(&data_->adjs[pos]);
    }
    igraph_int_t size() const {
      return data_->length;
    }
    SEXP wrap() const {
      const auto len = size();
      cpp11::writable::list output(len);
      for (igraph_int_t i = 0; i < len; ++i) {
        output[i] = at(i);
      }
      return output;
    }
    igraph_adjlist_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_adjlist_t> data_ = std::make_unique<igraph_adjlist_t>();
};

class IIncList {
  public:
    IIncList(const igraph_t* graph, int mode, int loops) {
      igraph_inclist_init(graph, data_.get(),
                          static_cast<igraph_neimode_t>(mode),
                          static_cast<igraph_loops_t>(loops));
    }
    IIncList() = delete;
    IIncList(const IIncList&) = delete;
    IIncList(IIncList&&) = delete;
    ~IIncList() noexcept {
      if (data_) igraph_inclist_destroy(data_.get());
    }
    SEXP at(igraph_int_t pos) const {
      return AsIndices::wrap(&data_->incs[pos]);
    }
    igraph_int_t size() const {
      return data_->length;
    }
    SEXP wrap() const {
      const auto len = size();
      cpp11::writable::list output(len);
      for (igraph_int_t i = 0; i < len; ++i) {
        output[i] = at(i);
      }
      return output;
    }
    igraph_inclist_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_inclist_t> data_ = std::make_unique<igraph_inclist_t>();
};

#endif // IGRAPHLITE_ADJLIST_HPP_
