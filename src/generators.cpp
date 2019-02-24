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

  // temporary; for compatibility with rigraph
  template <int RTYPE> inline
  Rcpp::Vector<RTYPE> unique_stable(const Rcpp::Vector<RTYPE>& x) {
    using T = typename Rcpp::Vector<RTYPE>::stored_type;
    std::vector<T> res;
    res.reserve(x.size());
    std::unordered_set<T> set;
    for (const auto& elem: x) {
      if (set.insert(elem).second) {
        res.push_back(elem);
      }
    }
    return Rcpp::wrap(res);
  }

  template <int RTYPE> inline
  IGraph graph_from_symbolic_edges(const Rcpp::Vector<RTYPE>& sym_edges, bool directed) {
    auto symbols = unique_stable(sym_edges);
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

//' @param df data.frame that includes an edgelist and edge attributes.
//' @param edgelist Two-column matrix.
//' @param directed Boolean
//' @rdname as_igraph
//' @export
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

//' @rdname as_igraph
//' @export
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

//' @rdname as_igraph
//' @export
// [[Rcpp::export]]
IGraph graph_from_edgelist(const Rcpp::NumericMatrix& edgelist, bool directed = true) {
  return IGraph(impl::flatten_edgelist(edgelist), 0, directed);
}

//' Deterministic Graph Generators
//'
//' @param edges The edges to add, the first two elements are the first edge, etc.
//' @param n Integer, the number of vertices in the graph.
//' @param directed Boolean
//' @param mutual Boolean
//' @param circular Boolean
//' @param mode Integer;
//'   `igraph_star_mode_t` {1: OUT, 2: IN, 3: MUTUAL, 4: UNDIRECTED};
//'   `igraph_tree_mode_t` {1: OUT, 2: IN, 3: UNDIRECTED};
//' @seealso [as_igraph()], [graph_from_data_frame()]
//' @source <https://igraph.org/c/doc/igraph-Generators.html>
//' @rdname generators
//' @export
// [[Rcpp::export]]
IGraph graph_create(const Rcpp::NumericVector& edges, int n = 0, bool directed = true) {
  return IGraph(edges, n, directed);
}

//' @param center Id of the vertex which will be the center of the graph.
//' @rdname generators
//' @export
// [[Rcpp::export]]
IGraph graph_star(int n, int mode = 0, int center = 1) {
  return IGraph(n, mode, static_cast<double>(center));
}

//' @param dim Vector giving the sizes of the lattice in each of its dimensions.
//' @param nei Integer distance within which two vertices will be connected.
//' @rdname generators
//' @export
// [[Rcpp::export]]
IGraph graph_lattice(const Rcpp::NumericVector& dim, int nei = 1, bool directed = false, bool mutual = false, bool circular = false) {
  return IGraph(dim, nei, directed, mutual, circular);
}

//' @rdname generators
//' @export
// [[Rcpp::export]]
IGraph graph_ring(int n, bool directed = false, bool mutual = false, bool circular = true) {
  return IGraph(n, directed, mutual, circular);
}

//' @param children Integer, the number of children of a vertex in the tree.
//' @rdname generators
//' @export
// [[Rcpp::export]]
IGraph graph_tree(int n, int children = 2, int mode = 0) {
  return IGraph(n, children, mode);
}

//' @rdname generators
//' @export
// [[Rcpp::export]]
IGraph graph_full(int n, bool directed = false, bool mutual = false) {
  return IGraph(n, directed, mutual);
}
