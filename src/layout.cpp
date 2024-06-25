// <https://igraph.org/c/doc/igraph-Layout.html>
#include "igraph.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "dataframe.hpp"

#include <igraph/igraph_layout.h>

inline SEXP col(const cpp11::doubles_matrix<>& mat, const int i) {
  auto slice = mat[i];
  cpp11::writable::doubles res;
  res.reserve(slice.size());
  for (auto d: slice) {
    res.push_back(d);
  }
  return res;
}

inline SEXP as_named_data_frame(const cpp11::doubles_matrix<>& mat) {
  using namespace cpp11::literals;
  return impl::tibble({
    "x"_nm = col(mat, 0),
    "y"_nm = col(mat, 1)
  });
}

[[cpp11::register]] SEXP
layout_random_(const cpp11::external_pointer<IGraph> graph) {
  IMatrix res(graph->vcount(), 2);
  igraph_layout_random(graph->data(), res.data());
  return as_named_data_frame(res.wrap());
}

[[cpp11::register]] SEXP
layout_drl_(const cpp11::external_pointer<IGraph> graph) {
  igraph_layout_drl_options_t options;
  igraph_layout_drl_options_init(&options, IGRAPH_LAYOUT_DRL_DEFAULT);
  IMatrix res(graph->vcount(), 2);
  igraph_layout_drl(graph->data(), res.data(),
    false,    // use_seed
    &options,
    nullptr  // weights
  );
  return as_named_data_frame(res.wrap());
}

[[cpp11::register]] SEXP
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
  return as_named_data_frame(res.wrap());
}

[[cpp11::register]] SEXP
layout_mds_(const cpp11::external_pointer<IGraph> graph, SEXP dist) {
  cpp11::writable::doubles null{};
  cpp11::writable::integers nulli{};
  IMatrix res(graph->vcount(), 2);
  igraph_layout_mds(graph->data(), res.data(), IMatrix(dist).data(), 2);
  return as_named_data_frame(res.wrap());
}

[[cpp11::register]] SEXP
layout_reingold_tilford_(const cpp11::external_pointer<IGraph> graph, int mode, const cpp11::integers& roots) {
  IMatrix res(graph->vcount(), 2);
  igraph_layout_reingold_tilford(
    graph->data(), res.data(),
    static_cast<igraph_neimode_t>(mode),
    roots.size() ? ISelectorInPlace(roots).data() : nullptr, nullptr);
  return as_named_data_frame(res.wrap());
}

[[cpp11::register]] SEXP
layout_reingold_tilford_circular_(const cpp11::external_pointer<IGraph> graph, int mode, const cpp11::integers& roots) {
  IMatrix res(graph->vcount(), 2);
  igraph_layout_reingold_tilford_circular(
    graph->data(), res.data(),
    static_cast<igraph_neimode_t>(mode),
    roots.size() ? ISelectorInPlace(roots).data() : nullptr, nullptr);
  return as_named_data_frame(res.wrap());
}
