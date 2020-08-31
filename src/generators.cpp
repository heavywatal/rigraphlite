#include "igraph.hpp"
#include "vector.hpp"

#include <igraph/igraph_interface.h>
#include <igraph/igraph_constructors.h>

#include <unordered_set>
#include <unordered_map>

namespace impl {
  // namespace traits {
  //   template <class RTYPE> struct storage_type {
  //     using type = SEXP;
  //   };
  //   template <> struct storage_type<INTSXP> {
  //     using type = int;
  //   };
  //   template <> struct storage_type<REALSXP> {
  //     using type = double;
  //   };
  //   template <> struct storage_type<STRSXP> {
  //     using type = const char*;
  //   };
  // }

  template <class RTYPE> inline
  cpp11::r_vector<RTYPE> flatten_edgelist(const cpp11::matrix<cpp11::r_vector<RTYPE>, RTYPE>& edgelist) {
    const long nrow = edgelist.nrow();
    cpp11::writable::r_vector<RTYPE> edges(2 * nrow);
    long i = -1;
    for (long r = 0; r < nrow; ++r) {
      edges[++i] = edgelist[r];
      edges[++i] = edgelist[r + nrow];
    }
    return edges;
  }

  template <class RTYPE> inline
  cpp11::r_vector<RTYPE> flatten_edgelist(const cpp11::r_vector<RTYPE>& from, const cpp11::r_vector<RTYPE>& to) {
    const long nrow = from.size();
    cpp11::writable::r_vector<RTYPE> edges(2 * nrow);
    long i = -1;
    for (long r = 0; r < nrow; ++r) {
      edges[++i] = from[r];
      edges[++i] = to[r];
    }
    return edges;
  }

  // temporary; for compatibility with rigraph
  template <class T> inline
  cpp11::r_vector<T> unique_stable(const cpp11::r_vector<T>& x) {
    std::vector<T> res;
    res.reserve(x.size());
    std::unordered_set<T> set;
    for (const auto& elem: x) {
      if (set.insert(elem).second) {
        res.push_back(elem);
      }
    }
    return res;
  }

  template <class RTYPE> inline
  IGraph graph_from_symbolic_edges(const cpp11::r_vector<RTYPE>& sym_edges, bool directed) {
    cpp11::writable::doubles edges;
    edges.reserve(sym_edges.size());
    std::unordered_map<RTYPE, int> map;
    int i = 0;
    for (const auto& elem: sym_edges) {
      const auto res = map.emplace(elem, i);
      if (res.second) {
        edges.push_back(++i);
      } else {
        edges.push_back(res.first->second);
      }
    }
    cpp11::writable::r_vector<RTYPE> symbols;
    symbols.reserve(map.size());
    for (const auto& p: map) {
      symbols.push_back(p.first);
    }
    // auto symbols = unique_stable(sym_edges);
    // auto edges = Rcpp::match(sym_edges, symbols);
    IGraph g(edges, 0, directed);
    g.mutate_Vattr("name", symbols);
    return g;
  }

  // template <class RTYPE> inline
  // IGraph graph_from_symbolic_edgelist(const cpp11::matrix<cpp11::r_vector<RTYPE>, RTYPE>& edgelist, bool directed) {
  //   return graph_from_symbolic_edges(flatten_edgelist(edgelist), directed);
  // }

  template <class RTYPE> inline
  IGraph graph_from_data_frame(const cpp11::data_frame& df, bool directed = true) {
    const auto edges = flatten_edgelist<RTYPE>(df.at(0), df.at(1));
    auto g = graph_from_symbolic_edges(edges, directed);
    const long n = df.ncol();
    if (n > 2) {
      const cpp11::strings names(df.attr("names"));
      for (long i = 2; i < n; ++i) {
        g.mutate_Eattr(static_cast<std::string>(names[i]).c_str(), df[i]);
      }
    }
    return g;
  }

}

IGraph::IGraph(): data_(std::make_unique<igraph_t>()) {}

IGraph::~IGraph() noexcept {
  if (data_) igraph_destroy(data_.get());
}

IGraph::IGraph(const IGraph& other) noexcept: IGraph::IGraph() {
  igraph_copy(data_.get(), other.data_.get());
  Vattr_ = other.Vattr_;
  Eattr_ = other.Eattr_;
}

IGraph::IGraph(IGraph&& other) = default;

IGraph::IGraph(int n, bool directed): IGraph::IGraph() {
  igraph_empty(data_.get(), n, directed);
  init_attr();
}

IGraph::IGraph(const cpp11::doubles& edges, int n, bool directed): IGraph::IGraph() {
  igraph_create(data_.get(), ISelectorInPlace(edges).data(), n, directed);
  init_attr();
}

IGraph::IGraph(int n, int mode, double center): IGraph::IGraph() {
  // double center to distinguish overloaded contructors (vs tree).
  igraph_star(data_.get(), n, static_cast<igraph_star_mode_t>(mode), static_cast<int>(center));
  init_attr();
}

IGraph::IGraph(const cpp11::doubles& dim, int nei, bool directed, bool mutual, bool circular): IGraph::IGraph() {
  igraph_lattice(data_.get(), ISelectorInPlace(dim).data(), nei, directed, mutual, circular);
  init_attr();
}

IGraph::IGraph(int n, bool directed, bool mutual, bool circular): IGraph::IGraph() {
  igraph_ring(data_.get(), n, directed, mutual, circular);
  init_attr();
}

IGraph::IGraph(int n, int children, int mode): IGraph::IGraph() {
  igraph_tree(data_.get(), n, children, static_cast<igraph_tree_mode_t>(mode));
  init_attr();
}

IGraph::IGraph(int n, bool directed, bool loops): IGraph::IGraph() {
  igraph_full(data_.get(), n, directed, loops);
  init_attr();
}

IGraph::IGraph(const char* name): IGraph::IGraph() {
  igraph_famous(data_.get(), name);
  init_attr();
}

//' @param df data.frame that includes an edgelist and edge attributes.
//' @param edgelist Two-column matrix.
//' @param directed Boolean
//' @rdname as_igraph
//' @export
[[cpp11::register]]
IGraph graph_from_data_frame(const cpp11::data_frame& df, bool directed = true) {
  switch (TYPEOF(df.at(0))) {
    case INTSXP:  return impl::graph_from_data_frame<int>(df, directed);
    case REALSXP: return impl::graph_from_data_frame<double>(df, directed);
    case STRSXP:  return impl::graph_from_data_frame<cpp11::r_string>(df, directed);
    default:
      cpp11::stop("Invalid type for vertex names: %d", TYPEOF(df.at(0)));
  }
}

//' @rdname as_igraph
//' @export
// [[cpp11::register]]
  template <class RTYPE> inline
  IGraph graph_from_symbolic_edgelist(const cpp11::matrix<cpp11::r_vector<RTYPE>, RTYPE>& edgelist, bool directed) {
    return graph_from_symbolic_edges(impl::flatten_edgelist(edgelist), directed);
  }
// IGraph graph_from_symbolic_edgelist(const cpp11::sexp& edgelist, bool directed = true) {
//   switch (edgelist.sexp_type()) {
//     case INTSXP:  return impl::graph_from_symbolic_edgelist(cpp11::matrix<cpp11::integers, int>(edgelist), directed);
//     case REALSXP: return impl::graph_from_symbolic_edgelist(cpp11::matrix<cpp11::doubles, double>(edgelist), directed);
//     case STRSXP:  return impl::graph_from_symbolic_edgelist(cpp11::matrix<STRSXP>(edgelist), directed);
//     default:
//       cpp11::stop("Invalid type for vertex names: %d", edgelist.sexp_type());
//   }
// }

//' @rdname as_igraph
//' @export
[[cpp11::register]]
IGraph graph_from_edgelist(const cpp11::doubles_matrix& edgelist, bool directed = true) {
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
//'   - `igraph_star_mode_t` \\{0: OUT, 1: IN, 2: MUTUAL, 3: UNDIRECTED\\}
//'   - `igraph_tree_mode_t` \\{0: OUT, 1: IN, 2: UNDIRECTED\\}
//' @seealso [as_igraph()], [graph_from_data_frame()]
//' @source <https://igraph.org/c/doc/igraph-Generators.html>
//' @rdname generators
//' @export
[[cpp11::register]]
IGraph graph_create(const cpp11::doubles& edges, int n = 0, bool directed = true) {
  return IGraph(edges, n, directed);
}

//' @param center Id of the vertex which will be the center of the graph.
//' @rdname generators
//' @export
[[cpp11::register]]
IGraph graph_star(int n, int mode = 0, int center = 1) {
  return IGraph(n, mode, static_cast<double>(center));
}

//' @param dim Vector giving the sizes of the lattice in each of its dimensions.
//' @param nei Integer distance within which two vertices will be connected.
//' @rdname generators
//' @export
[[cpp11::register]]
IGraph graph_lattice(const cpp11::doubles& dim, int nei = 1, bool directed = false, bool mutual = false, bool circular = false) {
  return IGraph(dim, nei, directed, mutual, circular);
}

//' @rdname generators
//' @export
[[cpp11::register]]
IGraph graph_ring(int n, bool directed = false, bool mutual = false, bool circular = true) {
  return IGraph(n, directed, mutual, circular);
}

//' @param children Integer, the number of children of a vertex in the tree.
//' @rdname generators
//' @export
[[cpp11::register]]
IGraph graph_tree(int n, int children = 2, int mode = 0) {
  return IGraph(n, children, mode);
}

//' @rdname generators
//' @export
[[cpp11::register]]
IGraph graph_full(int n, bool directed = false, bool mutual = false) {
  return IGraph(n, directed, mutual);
}

//' @param name \\{Bull, Chvatal, Coxeter, Cubical, Diamond, Dodecahedral,
//'   Dodecahedron, Folkman, Franklin, Frucht, Grotzsch, Heawood, Herschel, House,
//'   HouseX, Icosahedral, Icosahedron, Krackhardt_Kite, Levi, McGee, Meredith,
//'   Noperfectmatching, Nonline, Octahedral, Octahedron, Petersen, Robertson,
//'   Smallestcyclicgroup, Tetrahedral, Tetrahedron, Thomassen, Tutte,
//'   Uniquely3colorable, Walther, Zachary\\}
//' @rdname generators
//' @export
[[cpp11::register]]
IGraph graph_famous(const char* name) {
  return IGraph(name);
}
