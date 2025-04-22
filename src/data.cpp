#include "igraph.hpp"
#include "adjlist.hpp"
#include "dataframe.hpp"

[[cpp11::register]] SEXP
as_adjlist_(const cpp11::external_pointer<IGraph> graph, const int mode, const int loops, const int multiple) {
  return IAdjList(graph->data(), mode, loops, multiple).wrap();
}

[[cpp11::register]] SEXP
as_inclist_(const cpp11::external_pointer<IGraph> graph, const int mode, const int loops) {
  return IIncList(graph->data(), mode, loops).wrap();
}

[[cpp11::register]] SEXP
as_edgelist_(const cpp11::external_pointer<IGraph> graph) {
  const int nrow = graph->ecount();
  cpp11::writable::integers el(2 * nrow);
  el.attr(R_DimSymbol) = {nrow, 2};
  const auto from = graph->from();
  const auto to = graph->to();
  for (int i=0; i<nrow; ++i) {
    el[i] = from[i];
    el[i + nrow] = to[i];
  }
  return cpp11::integers_matrix<>{el};
}

[[cpp11::register]] SEXP
as_data_frame_(const cpp11::external_pointer<IGraph> graph) {
  using namespace cpp11::literals;
  const auto eattr_size = graph->Eattr_.size();
  cpp11::writable::list ls;
  ls.reserve(2 + eattr_size);
  const auto vnames = graph->Vattr_["name"];
  if (vnames == R_NilValue) {
    ls.push_back("from"_nm = graph->from());
    ls.push_back("to"_nm = graph->to());
  } else {
    ls.push_back("from"_nm = impl::subset(vnames, graph->from()));
    ls.push_back("to"_nm = impl::subset(vnames, graph->to()));
  }
  const auto eattr_names = cpp11::as_cpp<cpp11::strings>(graph->Eattr_.names());
  for (int i=0; i<eattr_size; ++i) {
    const auto name = eattr_names[i];
    ls.push_back(cpp11::named_arg(static_cast<std::string>(name).c_str()) = graph->Eattr_[i]);
  }
  return impl::tibble(std::move(ls));
}
