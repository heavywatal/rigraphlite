#include "igraph.hpp"
#include "dataframe.hpp"

[[cpp11::register]] SEXP
V_(const cpp11::external_pointer<IGraph> graph) {
  return graph->Vattr_.attr(R_RowNamesSymbol);
}

[[cpp11::register]] SEXP
E_(const cpp11::external_pointer<IGraph> graph) {
  return graph->Eattr_.attr(R_RowNamesSymbol);
}

[[cpp11::register]] SEXP
Vnames_(const cpp11::external_pointer<IGraph> graph) {
  const auto vnames = graph->Vattr_["name"];
  if (vnames == R_NilValue) return V_(graph);
  return vnames;
}

[[cpp11::register]] SEXP
from_(const cpp11::external_pointer<IGraph> graph) {return graph->from();}
[[cpp11::register]] SEXP
to_(const cpp11::external_pointer<IGraph> graph) {return graph->to();}
[[cpp11::register]] SEXP
getVattr_(const cpp11::external_pointer<IGraph> graph) {return graph->Vattr_;}
[[cpp11::register]] SEXP
getEattr_(const cpp11::external_pointer<IGraph> graph) {return graph->Eattr_;}
[[cpp11::register]]
void setVattr_(cpp11::external_pointer<IGraph> graph, SEXP other) {
  graph->Vattr_ = impl::tibble(other);
}
[[cpp11::register]]
void setEattr_(cpp11::external_pointer<IGraph> graph, SEXP other) {
  graph->Eattr_ = impl::tibble(other);
}
[[cpp11::register]]
void mutate_Vattr_(cpp11::external_pointer<IGraph> graph, const char* key, SEXP value) {
  impl::mutate(&graph->Vattr_, key, value);
}
[[cpp11::register]]
void mutate_Eattr_(cpp11::external_pointer<IGraph> graph, const char* key, SEXP value) {
  impl::mutate(&graph->Eattr_, key, value);
}
