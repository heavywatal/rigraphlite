#include "igraph.hpp"

namespace impl {

  template <int RTYPE> inline
  Rcpp::Vector<RTYPE> flatten_edgelist(const Rcpp::Matrix<RTYPE>& edgelist) {
    const long nrow = edgelist.nrow();
    Rcpp::Vector<RTYPE> edges(2 * nrow);
    long i = -1;
    for (long r = 0; r < nrow; ++r) {
      edges[++i] = edgelist[r];
      edges[++i] = edgelist[r + nrow];
    }
    return edges;
  }

  template <int RTYPE> inline
  Rcpp::Vector<RTYPE> flatten_edgelist(const Rcpp::Vector<RTYPE>& from, const Rcpp::Vector<RTYPE>& to) {
    const long nrow = from.length();
    Rcpp::Vector<RTYPE> edges(2 * nrow);
    long i = -1;
    for (long r = 0; r < nrow; ++r) {
      edges[++i] = from[r];
      edges[++i] = to[r];
    }
    return edges;
  }

  template <int RTYPE> inline
  IGraph graph_from_symbolic_edges(const Rcpp::Vector<RTYPE>& sym_edges, bool directed) {
    auto symbols = Rcpp::sort_unique(sym_edges);
    auto edges = Rcpp::match(sym_edges, symbols);
    IGraph g(Rcpp::as<Rcpp::NumericVector>(edges), 0, directed);
    g.setV("name", symbols);
    return g;
  }

  template <int RTYPE> inline
  IGraph graph_from_symbolic_edgelist(const Rcpp::Matrix<RTYPE>& edgelist, bool directed) {
    return graph_from_symbolic_edges(flatten_edgelist(edgelist), directed);
  }

  template <int RTYPE> inline
  IGraph graph_from_data_frame(const Rcpp::DataFrame& df, bool directed = true) {
    const auto edges = flatten_edgelist<RTYPE>(df.at(0), df.at(1));
    auto g = graph_from_symbolic_edges(edges, directed);
    const long n = df.ncol();
    if (n > 2) {
      const Rcpp::StringVector names = df.attr("names");
      for (long i = 2; i < n; ++i) {
        g.setE(names[i], df[i]);
      }
    }
    return g;
  }

}

// [[Rcpp::export]]
IGraph graph_from_data_frame(const Rcpp::DataFrame& df, bool directed = true) {
  switch (TYPEOF(df.at(0))) {
    case INTSXP:  return impl::graph_from_data_frame<INTSXP>(df, directed);
    case REALSXP: return impl::graph_from_data_frame<REALSXP>(df, directed);
    case STRSXP:  return impl::graph_from_data_frame<STRSXP>(df, directed);
    default:
      throw std::range_error("Invalid type for vertex names");
  }
}

// [[Rcpp::export]]
IGraph graph_from_symbolic_edgelist(const Rcpp::RObject& edgelist, bool directed = true) {
  switch (edgelist.sexp_type()) {
    case INTSXP:  return impl::graph_from_symbolic_edgelist(Rcpp::Matrix<INTSXP>(edgelist), directed);
    case REALSXP: return impl::graph_from_symbolic_edgelist(Rcpp::Matrix<REALSXP>(edgelist), directed);
    case STRSXP:  return impl::graph_from_symbolic_edgelist(Rcpp::Matrix<STRSXP>(edgelist), directed);
    default:
      throw std::range_error("Invalid type for vertex names");
  }
}

// [[Rcpp::export]]
IGraph graph_from_edgelist(const Rcpp::NumericMatrix& edgelist, bool directed = true) {
  return IGraph(impl::flatten_edgelist(edgelist), 0, directed);
}

// [[Rcpp::export]]
IGraph graph_create(const Rcpp::NumericVector& edges, int n = 0, bool directed = true) {
  return IGraph(edges, n, directed);
}

// [[Rcpp::export]]
IGraph graph_tree(int n, int children = 2, int mode = 0) {
  return IGraph(n, children, mode);
}
