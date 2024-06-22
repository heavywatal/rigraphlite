#include "igraph.hpp"
#include "adjlist.hpp"
#include "dataframe.hpp"

[[cpp11::register]]
cpp11::list
as_adjlist_(const cpp11::external_pointer<IGraph> graph, const int mode, const int loops, const int multiple) {
  return IAdjList<AsIndices>(graph->data(), mode, loops, multiple).wrap();
}

[[cpp11::register]]
cpp11::list
as_inclist_(const cpp11::external_pointer<IGraph> graph, const int mode, const int loops) {
  return IIncList<AsIndices>(graph->data(), mode, loops).wrap();
}

[[cpp11::register]]
cpp11::integers_matrix<> as_edgelist_(const cpp11::external_pointer<IGraph> graph) {
  const int nrow = graph->ecount();
  cpp11::writable::integers el(2 * nrow);
  el.attr(R_DimSymbol) = {nrow, 2};
  for (int i=0; i<nrow; ++i) {
    el[i] = graph->from()[i];
    el[i + nrow] = graph->to()[i];
  }
  return {el};
}

[[cpp11::register]]
cpp11::data_frame as_data_frame_(const cpp11::external_pointer<IGraph> graph) {
  using namespace cpp11::literals;
  const auto eattr_size = graph->Eattr_.size();
  cpp11::writable::list ls;
  ls.reserve(2 + eattr_size);
  const auto vnames = graph->Vattr_["name"];
  switch (TYPEOF(vnames)) {
    case NULL:
      ls.push_back("from"_nm = graph->from());
      ls.push_back("to"_nm = graph->to());
      break;
    case INTSXP:
      ls.push_back("from"_nm = impl::subset<int>(vnames, graph->from()));
      ls.push_back("to"_nm = impl::subset<int>(vnames, graph->to()));
      break;
    case STRSXP:
      ls.push_back("from"_nm = impl::subset<cpp11::r_string>(vnames, graph->from()));
      ls.push_back("to"_nm = impl::subset<cpp11::r_string>(vnames, graph->to()));
      break;
    default: cpp11::stop("Invalid type for vnames: %d", TYPEOF(vnames));
  }
  const auto eattr_names = cpp11::as_cpp<cpp11::strings>(graph->Eattr_.names());
  for (int i=0; i<eattr_size; ++i) {
    const auto name = eattr_names[i];
    ls.push_back(cpp11::named_arg(static_cast<std::string>(name).c_str()) = graph->Eattr_[i]);
  }
  return cpp11::writable::data_frame(std::move(ls));
}