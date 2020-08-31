#pragma once
#ifndef IGRAPHLITE_IGRAPH_HPP_
#define IGRAPHLITE_IGRAPH_HPP_

#include "cpp11.hpp"

#include <memory>

typedef struct igraph_s igraph_t;

namespace sugar {
  inline cpp11::integers seq_len(const int n) {
    return R_compact_intrange(1, n);
  }
}

class IGraph {
  public:
    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
    // Graph generators

    ~IGraph() noexcept;
    IGraph(const IGraph& other) noexcept;
    IGraph(IGraph&& other);

    IGraph(int n, bool directed); // empty
    IGraph(const cpp11::doubles& edges, int n, bool directed); // create
    IGraph(int n, int mode, double center); // star
    IGraph(const cpp11::doubles& dim, int nei, bool directed, bool mutual, bool circular); // lattice
    IGraph(int n, bool directed, bool mutual, bool circular); // ring
    IGraph(int n, int children, int mode); // tree
    IGraph(int n, bool directed, bool loops); // full
    IGraph(const char* name); // famous
    IGraph(const IGraph& other, const cpp11::doubles& vids, int impl); // induced_subgraph

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
    // Basic interface

    long vcount() const;
    long ecount() const;
    bool is_directed() const;
    cpp11::integers edge(int eid) const;
    cpp11::doubles neighbors(int node, int mode) const;
    cpp11::doubles incident(int node, int mode) const;
    cpp11::doubles degree(const cpp11::doubles& vids, int mode, bool loops) const;

    void add_edges(const cpp11::doubles& edges);
    void add_vertices(int n);
    void delete_edges(const cpp11::doubles& eids);
    void delete_vertices(const cpp11::doubles& vids);

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
    // Structural properties

    cpp11::logicals are_connected(int v1, int v2) const;
    cpp11::doubles_matrix shortest_paths(
      const cpp11::doubles& from, const cpp11::doubles& to,
      const cpp11::doubles& weights, int mode, const std::string& algorithm) const;
    cpp11::list get_shortest_paths(
      int from, const cpp11::doubles& to,
      const cpp11::doubles& weights, int mode) const;
    cpp11::list get_all_shortest_paths(
      int from, const cpp11::doubles& to,
      const cpp11::doubles& weights, int mode) const;
    cpp11::integers get_all_simple_paths(
      int from, const cpp11::doubles& to, int cutoff, int mode) const;
    double average_path_length(bool directed) const;
    cpp11::doubles path_length_hist(bool directed) const;
    cpp11::doubles neighborhood_size(const cpp11::doubles& vids, int order, int mode, int mindist) const;
    cpp11::list neighborhood(const cpp11::doubles& vids, int order, int mode, int mindist) const;
    cpp11::doubles subcomponent(double v, int mode) const;
    cpp11::list subcomponents(const cpp11::doubles& vids, int mode) const;

    cpp11::doubles mean_distances(
      const cpp11::doubles& from, const cpp11::doubles& to,
      const cpp11::doubles& weights, int mode, const std::string& algorithm) const;

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
    // Layout

    cpp11::data_frame layout_random() const;
    cpp11::data_frame layout_drl() const;
    cpp11::data_frame layout_fruchterman_reingold(int grid) const;
    cpp11::data_frame layout_mds() const;
    cpp11::data_frame layout_reingold_tilford(int mode, const cpp11::doubles& roots) const;
    cpp11::data_frame layout_reingold_tilford_circular(int mode, const cpp11::doubles& roots) const;

    /////1/////////2/////////3/////////4/////////5/////////6/////////7/////////
    // Original methods

    cpp11::list as_adjlist(int mode) const;
    cpp11::list as_inclist(int mode) const;
    cpp11::doubles_matrix as_edgelist() const;
    cpp11::data_frame as_data_frame() const;

    cpp11::logicals is_sink() const;
    cpp11::logicals is_source() const;
    cpp11::integers sink() const;
    cpp11::integers source() const;

    cpp11::integers V() const {return sugar::seq_len(vcount());}
    cpp11::integers E() const {return sugar::seq_len(ecount());}

    // igraph_t getter
    cpp11::doubles from() const;
    cpp11::doubles to() const;
    cpp11::doubles oi() const;
    cpp11::doubles ii() const;
    cpp11::doubles os() const;
    cpp11::doubles is() const;

    void mutate_Vattr(const char* name, const cpp11::sexp& value);
    void mutate_Eattr(const char* name, const cpp11::sexp& value);
    void setVattr(cpp11::writable::data_frame other) {Vattr_ = other;}
    void setEattr(cpp11::writable::data_frame other) {Eattr_ = other;}
    cpp11::data_frame getVattr() const {return Vattr_;}
    cpp11::data_frame getEattr() const {return Eattr_;}

    igraph_t* data() {return data_.get();}
    const igraph_t* data() const {return data_.get();}

  private:
    IGraph();
    void init_attr();

    std::unique_ptr<igraph_t> data_;
    cpp11::writable::data_frame Vattr_;
    cpp11::writable::data_frame Eattr_;
};

#endif // IGRAPHLITE_IGRAPH_HPP_
