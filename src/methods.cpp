#include "igraph.hpp"
#include "adjlist.hpp"
#include "dataframe.hpp"

cpp11::list IGraph::as_adjlist(const int mode) const {
  return IAdjList<AsIndicesInPlace>(data_.get(), mode).wrap();
}

cpp11::list IGraph::as_inclist(const int mode) const {
  return IIncList<AsIndicesInPlace>(data_.get(), mode).wrap();
}

cpp11::doubles_matrix IGraph::as_edgelist() const {
  return Rcpp::cbind(from(), to());
}

cpp11::data_frame IGraph::as_data_frame() const {
  auto df = cpp11::data_frame::create(
    Rcpp::_["from"] = from(),
    Rcpp::_["to"] = to()
  );
  const long n = Eattr_.ncol();
  const cpp11::strings names = Eattr_.attr("names");
  for (long i = 0; i < n; ++i) {
    impl::mutate(df, names[i], Eattr_[i]);
  }
  df.attr("class") = impl::tibble_class();
  return df;
}

cpp11::logicals IGraph::is_sink() const {
  return degree(cpp11::doubles(0L), 1L, true) == 0;
}

cpp11::logicals IGraph::is_source() const {
  return degree(cpp11::doubles(0L), 2L, true) == 0;
}

cpp11::integers IGraph::sink() const {
  return V()[is_sink()];
}

cpp11::integers IGraph::source() const {
  return V()[is_source()];
}

cpp11::doubles IGraph::from() const {return AsIndices::wrap(&data_->from);}
cpp11::doubles IGraph::to() const {return AsIndices::wrap(&data_->to);}
cpp11::doubles IGraph::oi() const {return AsIndices::wrap(&data_->oi);}
cpp11::doubles IGraph::ii() const {return AsIndices::wrap(&data_->ii);}
cpp11::doubles IGraph::os() const {return AsIndices::wrap(&data_->os);}
cpp11::doubles IGraph::is() const {return AsIndices::wrap(&data_->is);}

void IGraph::mutate_Vattr(const char* name, const cpp11::sexp& value) {
  impl::mutate(Vattr_, name, value);
}

void IGraph::mutate_Eattr(const char* name, const cpp11::sexp& value) {
  impl::mutate(Eattr_, name, value);
}

void IGraph::init_attr() {
  Vattr_.attr("class") = impl::tibble_class();
  Eattr_.attr("class") = impl::tibble_class();
  impl::set_rownames(Vattr_, vcount());
  impl::set_rownames(Eattr_, ecount());
}
