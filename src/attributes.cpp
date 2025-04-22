#include "igraph.hpp"
#include "policy.hpp"
#include "dataframe.hpp"

#include <igraph/igraph_datatype.h>

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

void IGraph::init_attr() {
  impl::set_data_frame_attributes(&Vattr_, vcount());
  impl::set_data_frame_attributes(&Eattr_, ecount());
}

cpp11::integers IGraph::from() const {return AsIndices::wrap(&data_->from);}
cpp11::integers IGraph::to() const {return AsIndices::wrap(&data_->to);}
cpp11::integers IGraph::oi() const {return AsIndices::wrap(&data_->oi);}
cpp11::integers IGraph::ii() const {return AsIndices::wrap(&data_->ii);}
cpp11::integers IGraph::os() const {return AsIndices::wrap(&data_->os);}
cpp11::integers IGraph::is() const {return AsIndices::wrap(&data_->is);}
