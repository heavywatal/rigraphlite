#include "igraph.hpp"
#include "adjlist.hpp"
#include "dataframe.hpp"

Rcpp::List IGraph::as_adjlist(const int mode) const {
  return IAdjList<AsIndicesInPlace>(data_.get(), mode).wrap();
}

Rcpp::List IGraph::as_inclist(const int mode) const {
  return IIncList<AsIndicesInPlace>(data_.get(), mode).wrap();
}

Rcpp::NumericMatrix IGraph::as_edgelist() const {
  return Rcpp::cbind(from(), to());
}

Rcpp::DataFrame IGraph::as_data_frame() const {
  auto df = Rcpp::DataFrame::create(
    Rcpp::_["from"] = from(),
    Rcpp::_["to"] = to()
  );
  const long n = Eattr_.ncol();
  const Rcpp::StringVector names = Eattr_.attr("names");
  for (long i = 0; i < n; ++i) {
    impl::mutate(df, names[i], Eattr_[i]);
  }
  df.attr("class") = impl::tibble_class();
  return df;
}

Rcpp::LogicalVector IGraph::is_sink() const {
  return degree(Rcpp::NumericVector(0L), 1L, true) == 0;
}

Rcpp::LogicalVector IGraph::is_source() const {
  return degree(Rcpp::NumericVector(0L), 2L, true) == 0;
}

Rcpp::IntegerVector IGraph::sink() const {
  return Rcpp::IntegerVector(V())[is_sink()];
}

Rcpp::IntegerVector IGraph::source() const {
  return Rcpp::IntegerVector(V())[is_source()];
}

Rcpp::NumericVector IGraph::from() const {return AsIndices::wrap(&data_->from);}
Rcpp::NumericVector IGraph::to() const {return AsIndices::wrap(&data_->to);}
Rcpp::NumericVector IGraph::oi() const {return AsIndices::wrap(&data_->oi);}
Rcpp::NumericVector IGraph::ii() const {return AsIndices::wrap(&data_->ii);}
Rcpp::NumericVector IGraph::os() const {return AsIndices::wrap(&data_->os);}
Rcpp::NumericVector IGraph::is() const {return AsIndices::wrap(&data_->is);}

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
