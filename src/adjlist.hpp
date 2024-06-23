// <https://igraph.org/c/doc/igraph-Data-structures.html#igraph-Adjlists>
#pragma once
#ifndef IGRAPHLITE_ADJLIST_HPP_
#define IGRAPHLITE_ADJLIST_HPP_

#include "cpp11.hpp"

#include <igraph/igraph_adjlist.h>

#include "policy.hpp"

template <class WrapPolicy>
class IAdjList {
  public:
    IAdjList(const igraph_t* graph, int mode, int loops, int multiple) {
      igraph_adjlist_init(graph, data_.get(), static_cast<igraph_neimode_t>(mode),
                          static_cast<igraph_loops_t>(loops),
                          static_cast<igraph_multiple_t>(multiple));
    }
    IAdjList() = delete;
    IAdjList(const IAdjList&) = delete;
    IAdjList(IAdjList&&) = delete;
    ~IAdjList() noexcept {
      if (data_) igraph_adjlist_destroy(data_.get());
    }
    SEXP at(int pos) {
      return WrapPolicy::wrap(&data_->adjs[pos]);
    }
    int size() const {
      return data_->length;
    }
    SEXP wrap() {
      const int len = size();
      cpp11::writable::list output;
      output.reserve(len);
      for (int i = 0; i < len; ++i) {
        output.push_back(at(i));
      }
      return output;
    }
    igraph_adjlist_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_adjlist_t> data_ = std::make_unique<igraph_adjlist_t>();
};

template <class WrapPolicy>
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
    SEXP at(int pos) {
      return WrapPolicy::wrap(&data_->incs[pos]);
    }
    int size() const {
      return data_->length;
    }
    SEXP wrap() {
      const int len = size();
      cpp11::writable::list output;
      output.reserve(len);
      for (int i = 0; i < len; ++i) {
        output.push_back(at(i));
      }
      return output;
    }
    igraph_inclist_t* data() {return data_.get();}
  private:
    std::unique_ptr<igraph_inclist_t> data_ = std::make_unique<igraph_inclist_t>();
};

#endif // IGRAPHLITE_ADJLIST_HPP_
