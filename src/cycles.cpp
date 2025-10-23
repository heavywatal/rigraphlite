// <https://igraph.org/c/doc/igraph-Cycles.html>
#include "igraph.hpp"

#include <igraph/igraph_cycles.h>
#include <igraph/igraph_eulerian.h>

#include <cpp11/logicals.hpp>

[[cpp11::register]] bool
is_dag_(const cpp11::external_pointer<IGraph> graph) {
  igraph_bool_t res;
  igraph_is_dag(graph->data(), &res);
  return res;
}

[[cpp11::register]] SEXP
is_eulerian_(const cpp11::external_pointer<IGraph> graph) {
  igraph_bool_t has_path;
  igraph_bool_t has_cycle;
  igraph_is_eulerian(graph->data(), &has_path, &has_cycle);
  return cpp11::writable::logicals{has_path, has_cycle};
}
