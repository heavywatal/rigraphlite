// <https://igraph.org/c/doc/igraph-Layout.html>
#include "igraph.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "dataframe.hpp"

#include <igraph/igraph_layout.h>

inline SEXP col(const cpp11::doubles_matrix<>& mat, const int i) {
  auto slice = mat[i];
  const auto n = slice.size();
  cpp11::writable::doubles res(n);
  for (R_xlen_t j = 0; j < n; ++j) {
    res[j] = slice[j];
  }
  return res;
}

inline void mutate_vattr_xy(cpp11::writable::data_frame* vattr, const cpp11::doubles_matrix<>& mat) {
  impl::mutate(vattr, "x", col(mat, 0));
  impl::mutate(vattr, "y", col(mat, 1));
}

[[cpp11::register]] void
layout_random_(const cpp11::external_pointer<IGraph> graph) {
  IMatrix res(graph->vcount(), 2);
  igraph_layout_random(graph->data(), res.data());
  mutate_vattr_xy(&graph->Vattr_, res.wrap());
}

[[cpp11::register]] void
layout_circle_(const cpp11::external_pointer<IGraph> graph, const cpp11::integers& order) {
  IMatrix res(graph->vcount(), 2);
  igraph_layout_circle(graph->data(), res.data(),
    order.empty() ? igraph_vss_all() : ISelectorInPlace(order).vss());
  mutate_vattr_xy(&graph->Vattr_, res.wrap());
}

[[cpp11::register]] void
layout_star_(const cpp11::external_pointer<IGraph> graph,
    int center, const cpp11::integers& order) {
  IMatrix res(graph->vcount(), 2);
  igraph_layout_star(graph->data(), res.data(), --center,
    order.empty() ? nullptr : ISelectorInPlace(order).data());
  mutate_vattr_xy(&graph->Vattr_, res.wrap());
}

[[cpp11::register]] void
layout_grid_(const cpp11::external_pointer<IGraph> graph, const int width) {
  IMatrix res(graph->vcount(), 2);
  igraph_layout_grid(graph->data(), res.data(), width);
  mutate_vattr_xy(&graph->Vattr_, res.wrap());
}

[[cpp11::register]] void
layout_drl_(const cpp11::external_pointer<IGraph> graph) {
  igraph_layout_drl_options_t options;
  igraph_layout_drl_options_init(&options, IGRAPH_LAYOUT_DRL_DEFAULT);
  IMatrix res(graph->vcount(), 2);
  igraph_layout_drl(graph->data(), res.data(),
    false,    // use_seed
    &options,
    nullptr  // weights
  );
  mutate_vattr_xy(&graph->Vattr_, res.wrap());
}

[[cpp11::register]] void
layout_fruchterman_reingold_(const cpp11::external_pointer<IGraph> graph, int grid) {
  IMatrix res(graph->vcount(), 2);
  igraph_layout_fruchterman_reingold(
    graph->data(), res.data(),
    false,               // use_seed
    500,                 // niter
    std::sqrt(graph->vcount()), // start_temp
    static_cast<igraph_layout_grid_t>(grid),
    nullptr,             // weight
    nullptr,             // minx
    nullptr,             // maxx
    nullptr,             // miny
    nullptr              // maxy
  );
  mutate_vattr_xy(&graph->Vattr_, res.wrap());
}

[[cpp11::register]] void
layout_mds_(const cpp11::external_pointer<IGraph> graph, SEXP dist) {
  IMatrix res(graph->vcount(), 2);
  igraph_layout_mds(graph->data(), res.data(), IMatrix(dist).data(), 2);
  mutate_vattr_xy(&graph->Vattr_, res.wrap());
}

[[cpp11::register]] void
layout_reingold_tilford_(const cpp11::external_pointer<IGraph> graph, int mode, const cpp11::integers& roots) {
  IMatrix res(graph->vcount(), 2);
  igraph_layout_reingold_tilford(
    graph->data(), res.data(),
    static_cast<igraph_neimode_t>(mode),
    roots.size() ? ISelectorInPlace(roots).data() : nullptr, nullptr);
  mutate_vattr_xy(&graph->Vattr_, res.wrap());
}

[[cpp11::register]] void
layout_reingold_tilford_circular_(const cpp11::external_pointer<IGraph> graph, int mode, const cpp11::integers& roots) {
  IMatrix res(graph->vcount(), 2);
  igraph_layout_reingold_tilford_circular(
    graph->data(), res.data(),
    static_cast<igraph_neimode_t>(mode),
    roots.size() ? ISelectorInPlace(roots).data() : nullptr, nullptr);
  mutate_vattr_xy(&graph->Vattr_, res.wrap());
}
