#include "igraph.hpp"
#include "vector.hpp"

[[cpp11::register]]
SEXP V_(const cpp11::external_pointer<IGraph> graph) {return graph->V();}
[[cpp11::register]]
SEXP E_(const cpp11::external_pointer<IGraph> graph) {return graph->E();}
[[cpp11::register]]
SEXP Vnames_(const cpp11::external_pointer<IGraph> graph) {return graph->Vnames();}
[[cpp11::register]]
cpp11::integers from_(const cpp11::external_pointer<IGraph> graph) {return graph->from();}
[[cpp11::register]]
cpp11::integers to_(const cpp11::external_pointer<IGraph> graph) {return graph->to();}
[[cpp11::register]]
cpp11::data_frame getVattr_(const cpp11::external_pointer<IGraph> graph) {return graph->Vattr_;}
[[cpp11::register]]
cpp11::data_frame getEattr_(const cpp11::external_pointer<IGraph> graph) {return graph->Eattr_;}
[[cpp11::register]]
void setVattr_(cpp11::external_pointer<IGraph> graph, cpp11::data_frame other) {
  graph->Vattr_ = cpp11::writable::data_frame(other);
}
[[cpp11::register]]
void setEattr_(cpp11::external_pointer<IGraph> graph, cpp11::data_frame other) {
  graph->Eattr_ = cpp11::writable::data_frame(other);
}

SEXP IGraph::V() const {
  return Vattr_.attr(R_RowNamesSymbol);
}

SEXP IGraph::E() const {
  return Eattr_.attr(R_RowNamesSymbol);
}

SEXP IGraph::Vnames() const {
  const auto vnames = Vattr_["name"];
  switch (TYPEOF(vnames)) {
    case NULL:
      return V();
    case INTSXP:
      return cpp11::as_cpp<cpp11::integers>(vnames);
    case REALSXP:
      return cpp11::as_cpp<cpp11::doubles>(vnames);
    case STRSXP:
      return cpp11::as_cpp<cpp11::strings>(vnames);
    default: cpp11::stop("Invalid type for vnames: %d", TYPEOF(vnames));
  }
}

cpp11::integers IGraph::from() const {return AsIndices::wrap(&data_->from);}
cpp11::integers IGraph::to() const {return AsIndices::wrap(&data_->to);}
cpp11::integers IGraph::oi() const {return AsIndices::wrap(&data_->oi);}
cpp11::integers IGraph::ii() const {return AsIndices::wrap(&data_->ii);}
cpp11::integers IGraph::os() const {return AsIndices::wrap(&data_->os);}
cpp11::integers IGraph::is() const {return AsIndices::wrap(&data_->is);}