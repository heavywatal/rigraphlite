#include "igraph.hpp"
#include "adjlist.hpp"
#include "dataframe.hpp"

// [[Rcpp::export]]
Rcpp::List
as_adjlist_(const IGraph& graph, const int mode, const int loops, const int multiple) {
  return IAdjList<AsIndicesInPlace>(graph.data(), mode, loops, multiple).wrap();
}

// [[Rcpp::export]]
Rcpp::List as_inclist_(const IGraph& graph, const int mode, const int loops) {
  return IIncList<AsIndicesInPlace>(graph.data(), mode, loops).wrap();
}

// [[Rcpp::export]]
Rcpp::IntegerMatrix as_edgelist_(const IGraph& graph) {
  return Rcpp::cbind(graph.from(), graph.to());
}

Rcpp::IntegerVector IGraph::from() const {return AsIndices::wrap(&data_->from);}
Rcpp::IntegerVector IGraph::to() const {return AsIndices::wrap(&data_->to);}
Rcpp::IntegerVector IGraph::oi() const {return AsIndices::wrap(&data_->oi);}
Rcpp::IntegerVector IGraph::ii() const {return AsIndices::wrap(&data_->ii);}
Rcpp::IntegerVector IGraph::os() const {return AsIndices::wrap(&data_->os);}
Rcpp::IntegerVector IGraph::is() const {return AsIndices::wrap(&data_->is);}

// [[Rcpp::export]]
Rcpp::IntegerVector from_(const IGraph& graph) {return graph.from();}

// [[Rcpp::export]]
Rcpp::IntegerVector to_(const IGraph& graph) {return graph.to();}

// [[Rcpp::export]]
void setVattr_(IGraph* graph, Rcpp::DataFrame other) {graph->Vattr_ = other;}
// [[Rcpp::export]]
void setEattr_(IGraph* graph, Rcpp::DataFrame other) {graph->Eattr_ = other;}
// [[Rcpp::export]]
Rcpp::DataFrame getVattr_(const IGraph& graph) {return graph.Vattr_;}
// [[Rcpp::export]]
Rcpp::DataFrame getEattr_(const IGraph& graph) {return graph.Eattr_;}

void IGraph::mutate_Vattr(const char* name, const Rcpp::RObject& value) {
  impl::mutate(Vattr_, name, value);
}

void IGraph::mutate_Eattr(const char* name, const Rcpp::RObject& value) {
  impl::mutate(Eattr_, name, value);
}

void IGraph::init_attr() {
  Vattr_.attr("class") = impl::tibble_class();
  Eattr_.attr("class") = impl::tibble_class();
  impl::set_rownames(Vattr_, vcount());
  impl::set_rownames(Eattr_, ecount());
}
