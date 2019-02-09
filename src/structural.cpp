#include "igraph.hpp"

#include "vector.hpp"
#include "matrix.hpp"

#include <igraph/igraph_structural.h>
#include <igraph/igraph_paths.h>
#include <igraph/igraph_neighborhood.h>

Rcpp::LogicalVector
IGraph::are_connected(int v1, int v2) const {
  igraph_bool_t res;
  igraph_are_connected(data_.get(), v1, v2, &res);
  return static_cast<bool>(res);
}

Rcpp::NumericMatrix
IGraph::shortest_paths(const Rcpp::NumericVector& from, const Rcpp::NumericVector& to, int mode) const {
  IMatrix res(from.size(), to.size());
  igraph_shortest_paths(
    data_.get(), res.data(), ISelector(from), ISelector(to),
    static_cast<igraph_neimode_t>(mode));
  return res;
}

Rcpp::NumericMatrix
IGraph::shortest_paths_dijkstra(const Rcpp::NumericVector& from, const Rcpp::NumericVector& to, const Rcpp::NumericVector& weights, int mode) const {
  IMatrix res(from.size(), to.size());
  igraph_shortest_paths_dijkstra(
    data_.get(), res.data(), ISelector(from), ISelector(to),
    IVector(weights).data(),
    static_cast<igraph_neimode_t>(mode));
  return res;
}

Rcpp::NumericVector
IGraph::path_length_hist(bool directed) const {
  IVector res(vcount()); // rough estimate; resized as needed
  double unconnected;
  igraph_path_length_hist(data_.get(), res.data(), &unconnected, directed);
  return res;
}

Rcpp::NumericVector
IGraph::neighborhood_size(const Rcpp::NumericVector& vids, const int order, const int mode) const {
  IVector res(vids.size());
  igraph_neighborhood_size(
    data_.get(), res.data(), ISelector(vids), order,
    static_cast<igraph_neimode_t>(mode));
  return res;
}
