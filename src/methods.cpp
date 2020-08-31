#include "igraph.hpp"
#include "adjlist.hpp"
#include "dataframe.hpp"

cpp11::list IGraph::as_adjlist(const int mode, const int loops, const int multiple) const {
  return IAdjList<AsIndicesInPlace>(data_.get(), mode, loops, multiple).wrap();
}

cpp11::list IGraph::as_inclist(const int mode, const int loops) const {
  return IIncList<AsIndicesInPlace>(data_.get(), mode, loops).wrap();
}

cpp11::integers_matrix<> IGraph::as_edgelist() const {
  const int nrow = ecount();
  cpp11::writable::integers el(2 * nrow);
  el.attr(R_DimSymbol) = {nrow, 2};
  for (int i=0; i<nrow; ++i) {
    el[i] = from()[i];
    el[i + nrow] = to()[i];
  }
  return {el};
}

cpp11::integers IGraph::from() const {return AsIndices::wrap(&data_->from);}
cpp11::integers IGraph::to() const {return AsIndices::wrap(&data_->to);}
cpp11::integers IGraph::oi() const {return AsIndices::wrap(&data_->oi);}
cpp11::integers IGraph::ii() const {return AsIndices::wrap(&data_->ii);}
cpp11::integers IGraph::os() const {return AsIndices::wrap(&data_->os);}
cpp11::integers IGraph::is() const {return AsIndices::wrap(&data_->is);}

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
