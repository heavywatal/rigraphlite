#include "igraph.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "dataframe.hpp"

#include <igraph/igraph_layout.h>

inline Rcpp::DataFrame as_named_data_frame(const Rcpp::NumericMatrix& mat) {
  auto df = Rcpp::DataFrame::create(
    Rcpp::_["x"] = Rcpp::NumericVector(mat.column(0)),
    Rcpp::_["y"] = Rcpp::NumericVector(mat.column(1))
  );
  df.attr("class") = impl::tibble_class();
  return df;
}

// [[Rcpp::export]]
Rcpp::DataFrame layout_random_(const IGraph& graph) {
  IMatrix res(graph.vcount(), 2);
  igraph_layout_random(graph.data(), res.data());
  return as_named_data_frame(res.wrap());
}

// [[Rcpp::export]]
Rcpp::DataFrame layout_drl_(const IGraph& graph) {
  igraph_layout_drl_options_t options;
  igraph_layout_drl_options_init(&options, IGRAPH_LAYOUT_DRL_DEFAULT);
  IMatrix res(graph.vcount(), 2);
  igraph_layout_drl(graph.data(), res.data(),
    false,    // use_seed
    &options,
    nullptr  // weights
  );
  return as_named_data_frame(res.wrap());
}

// [[Rcpp::export]]
Rcpp::DataFrame layout_fruchterman_reingold_(const IGraph& graph, int grid) {
  IMatrix res(graph.vcount(), 2);
  igraph_layout_fruchterman_reingold(
    graph.data(), res.data(),
    false,               // use_seed
    500,                 // niter
    std::sqrt(graph.vcount()), // start_temp
    static_cast<igraph_layout_grid_t>(grid),
    nullptr,             // weight
    nullptr,             // minx
    nullptr,             // maxx
    nullptr,             // miny
    nullptr              // maxy
  );
  return as_named_data_frame(res.wrap());
}

// [[Rcpp::export]]
Rcpp::DataFrame layout_mds_(const IGraph& graph) {
  Rcpp::NumericVector null(0);
  Rcpp::IntegerVector nulli(0);
  IMatrix dist(distances_(graph, nulli, nulli, null, 3, "unweighted"));
  IMatrix res(graph.vcount(), 2);
  igraph_layout_mds(graph.data(), res.data(), dist.data(), 2);
  return as_named_data_frame(res.wrap());
}

// [[Rcpp::export]]
Rcpp::DataFrame layout_reingold_tilford_(const IGraph& graph, int mode, const Rcpp::IntegerVector& roots) {
  IMatrix res(graph.vcount(), 2);
  igraph_layout_reingold_tilford(
    graph.data(), res.data(),
    static_cast<igraph_neimode_t>(mode),
    roots.size() ? ISelectorInPlace(roots).data() : nullptr, nullptr);
  return as_named_data_frame(res.wrap());
}

// [[Rcpp::export]]
Rcpp::DataFrame layout_reingold_tilford_circular_(const IGraph& graph, int mode, const Rcpp::IntegerVector& roots) {
  IMatrix res(graph.vcount(), 2);
  igraph_layout_reingold_tilford_circular(
    graph.data(), res.data(),
    static_cast<igraph_neimode_t>(mode),
    roots.size() ? ISelectorInPlace(roots).data() : nullptr, nullptr);
  return as_named_data_frame(res.wrap());
}
