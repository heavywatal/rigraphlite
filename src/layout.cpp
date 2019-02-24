#include "igraph.hpp"

#include "matrix.hpp"

#include <igraph/igraph_layout.h>

void IGraph::layout_random() {
  IMatrix res(vcount(), 2);
  igraph_layout_random(data_.get(), res.data());
  mutate_Vattr_layout(res.wrap());
}

void IGraph::layout_drl() {
  igraph_layout_drl_options_t options;
  igraph_layout_drl_options_init(&options, IGRAPH_LAYOUT_DRL_DEFAULT);
  IMatrix res(vcount(), 2);
  igraph_layout_drl(data_.get(), res.data(),
    false,    // use_seed
    &options,
    nullptr,  // weights
    nullptr   // fixed
  );
  mutate_Vattr_layout(res.wrap());
}

void IGraph::layout_fruchterman_reingold(int grid) {
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
  mutate_Vattr_layout(res.wrap());
}

void IGraph::layout_mds() {
  Rcpp::NumericVector null(0);
  IMatrix dist(shortest_paths(null, null, null, 3, "unweighted"));
  IMatrix res(vcount(), 2);
  igraph_layout_mds(data_.get(), res.data(), dist.data(), 2, nullptr);
  mutate_Vattr_layout(res.wrap());
}

void IGraph::layout_reingold_tilford(int mode) {
  IMatrix res(vcount(), 2);
  igraph_layout_reingold_tilford(
    data_.get(), res.data(),
    static_cast<igraph_neimode_t>(mode), nullptr, nullptr);
  mutate_Vattr_layout(res.wrap());
}

void IGraph::layout_reingold_tilford_circular(int mode) {
  IMatrix res(vcount(), 2);
  igraph_layout_reingold_tilford_circular(
    data_.get(), res.data(),
    static_cast<igraph_neimode_t>(mode), nullptr, nullptr);
  mutate_Vattr_layout(res.wrap());
}
