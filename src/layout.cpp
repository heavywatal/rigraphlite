#include "igraph.hpp"
#include "vector.hpp"
#include "matrix.hpp"

#include <igraph/igraph_layout.h>

inline Rcpp::DataFrame as_named_data_frame(const Rcpp::NumericMatrix& mat) {
  return Rcpp::DataFrame::create(
    Rcpp::_["x"] = Rcpp::NumericVector(mat.column(0)),
    Rcpp::_["y"] = Rcpp::NumericVector(mat.column(1))
  );
}

Rcpp::DataFrame IGraph::layout_random() const {
  IMatrix res(vcount(), 2);
  igraph_layout_random(data_.get(), res.data());
  return as_named_data_frame(res.wrap());
}

Rcpp::DataFrame IGraph::layout_drl() const {
  igraph_layout_drl_options_t options;
  igraph_layout_drl_options_init(&options, IGRAPH_LAYOUT_DRL_DEFAULT);
  IMatrix res(vcount(), 2);
  igraph_layout_drl(data_.get(), res.data(),
    false,    // use_seed
    &options,
    nullptr,  // weights
    nullptr   // fixed
  );
  return as_named_data_frame(res.wrap());
}

Rcpp::DataFrame IGraph::layout_fruchterman_reingold(int grid) const {
  IMatrix res(vcount(), 2);
  igraph_layout_fruchterman_reingold(
    data_.get(), res.data(),
    false,               // use_seed
    500,                 // niter
    std::sqrt(vcount()), // start_temp
    static_cast<igraph_layout_grid_t>(grid),
    nullptr,             // weight
    nullptr,             // minx
    nullptr,             // maxx
    nullptr,             // miny
    nullptr              // maxy
  );
  return as_named_data_frame(res.wrap());
}

Rcpp::DataFrame IGraph::layout_mds() const {
  Rcpp::NumericVector null(0);
  IMatrix dist(shortest_paths(null, null, null, 3, "unweighted"));
  IMatrix res(vcount(), 2);
  igraph_layout_mds(data_.get(), res.data(), dist.data(), 2, nullptr);
  return as_named_data_frame(res.wrap());
}

Rcpp::DataFrame IGraph::layout_reingold_tilford(int mode) const {
  IMatrix res(vcount(), 2);
  auto root = Rcpp::as<Rcpp::NumericVector>(source());
  igraph_layout_reingold_tilford(
    data_.get(), res.data(),
    static_cast<igraph_neimode_t>(mode), ISelectorInPlace(root).data(), nullptr);
  return as_named_data_frame(res.wrap());
}

Rcpp::DataFrame IGraph::layout_reingold_tilford_circular(int mode) const {
  IMatrix res(vcount(), 2);
  auto root = Rcpp::as<Rcpp::NumericVector>(source());
  igraph_layout_reingold_tilford_circular(
    data_.get(), res.data(),
    static_cast<igraph_neimode_t>(mode), ISelectorInPlace(root).data(), nullptr);
  return as_named_data_frame(res.wrap());
}
