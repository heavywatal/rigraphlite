#include "igraph.hpp"
#include "adjlist.hpp"
#include "dataframe.hpp"

Rcpp::List IGraph::as_adjlist(const int mode, const int loops, const int multiple) const {
  return IAdjList<AsIndicesInPlace>(data_.get(), mode, loops, multiple).wrap();
}

Rcpp::List IGraph::as_inclist(const int mode, const int loops) const {
  return IIncList<AsIndicesInPlace>(data_.get(), mode, loops).wrap();
}

Rcpp::IntegerMatrix IGraph::as_edgelist() const {
  return Rcpp::cbind(from(), to());
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
