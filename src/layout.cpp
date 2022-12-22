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
    nullptr  // weights
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
  Rcpp::IntegerVector nulli(0);
  IMatrix dist(distances(nulli, nulli, null, 3, "unweighted"));
  IMatrix res(vcount(), 2);
  igraph_layout_mds(data_.get(), res.data(), dist.data(), 2);
  return as_named_data_frame(res.wrap());
}

Rcpp::DataFrame IGraph::layout_reingold_tilford(int mode, const Rcpp::IntegerVector& roots) const {
  IMatrix res(vcount(), 2);
  igraph_layout_reingold_tilford(
    data_.get(), res.data(),
    static_cast<igraph_neimode_t>(mode),
    roots.size() ? ISelectorInPlace(roots).data() : nullptr, nullptr);
  return as_named_data_frame(res.wrap());
}

Rcpp::DataFrame IGraph::layout_reingold_tilford_circular(int mode, const Rcpp::IntegerVector& roots) const {
  IMatrix res(vcount(), 2);
  igraph_layout_reingold_tilford_circular(
    data_.get(), res.data(),
    static_cast<igraph_neimode_t>(mode),
    roots.size() ? ISelectorInPlace(roots).data() : nullptr, nullptr);
  return as_named_data_frame(res.wrap());
}
