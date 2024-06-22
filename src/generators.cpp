// <https://igraph.org/c/doc/igraph-Generators.html>
#include "igraph.hpp"
#include "vector.hpp"
#include "dataframe.hpp"

#include <igraph/igraph_interface.h>
#include <igraph/igraph_constructors.h>
#include <igraph/igraph_operators.h>

#include <unordered_map>

namespace std {
  template <> struct hash<cpp11::r_string> {
    std::size_t operator()(const cpp11::r_string& x) const {
      return std::hash<std::string>{}(x);
    }
  };
}

namespace impl {

  template <class T> inline
  cpp11::r_vector<T>
  flatten_edgelist(const cpp11::sexp edgelist) {
    const auto mtrx = cpp11::as_cpp<cpp11::matrix<cpp11::r_vector<T>, T>>(edgelist);
    const int nrow = mtrx.nrow();
    cpp11::writable::r_vector<T> edges;
    edges.reserve(2 * nrow);
    for (int r = 0; r < nrow; ++r) {
      edges.push_back(mtrx(r, 0));
      edges.push_back(mtrx(r, 1));
    }
    return edges;
  }

  template <class T> inline
  cpp11::r_vector<T>
  flatten_edgelist(const cpp11::r_vector<T>& from, const cpp11::r_vector<T>& to) {
    const int nrow = from.size();
    cpp11::writable::r_vector<T> edges;
    edges.reserve(2 * nrow);
    for (int r = 0; r < nrow; ++r) {
      edges.push_back(from[r]);
      edges.push_back(to[r]);
    }
    return edges;
  }

  template <class T> inline
  cpp11::external_pointer<IGraph>
  graph_from_symbolic_edges(const cpp11::r_vector<T>& sym_edges, bool directed) {
    cpp11::writable::r_vector<T> symbols;
    cpp11::writable::integers edgelist;
    symbols.reserve(sym_edges.size());
    edgelist.reserve(sym_edges.size());
    std::unordered_map<T, int> map;
    int i = 1;
    for (const auto& elem: sym_edges) {
      const auto p = map.emplace(elem, i);
      if (p.second) {
        symbols.push_back(elem);
        ++i;
      }
      edgelist.push_back(p.first->second);
    }
    cpp11::external_pointer<IGraph> g(new IGraph(edgelist, 0, directed));
    g->Vattr_ = cpp11::writable::data_frame{cpp11::named_arg("name") = symbols};
    return g;
  }

  template <class T> inline
  cpp11::external_pointer<IGraph>
  graph_from_data_frame(const cpp11::data_frame& df, bool directed = true) {
    const auto edges = flatten_edgelist<T>(df.at(0), df.at(1));
    auto g = graph_from_symbolic_edges(edges, directed);
    const int n = df.ncol();
    if (n > 2) {
      cpp11::writable::list ls;
      ls.reserve(n - 2);
      const cpp11::strings names(df.names());
      for (int i = 2; i < n; ++i) {
        ls.push_back(cpp11::named_arg(static_cast<std::string>(names[i]).c_str()) = df[i]);
      }
      g->Eattr_ = cpp11::writable::data_frame(std::move(ls));
    }
    return g;
  }

}

IGraph::IGraph():
  data_(std::make_unique<igraph_t>()),
  Vattr_(cpp11::writable::list{}),
  Eattr_(cpp11::writable::list{}) {}

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

IGraph::IGraph(const cpp11::integers& edges, int n, bool directed): IGraph::IGraph() {
  igraph_create(data_.get(), ISelectorInPlace(edges).data(), n, directed);
  init_attr();
}

IGraph::IGraph(int n, int mode, double center): IGraph::IGraph() {
  // double center to distinguish overloaded contructors (vs tree).
  igraph_star(data_.get(), n, static_cast<igraph_star_mode_t>(mode), static_cast<int>(center));
  init_attr();
}

IGraph::IGraph(const cpp11::integers& dim, int nei, bool directed, bool mutual, bool circular): IGraph::IGraph() {
  igraph_vector_bool_t periodic;
  igraph_vector_bool_init(&periodic, dim.size());
  igraph_vector_bool_fill(&periodic, circular);
  igraph_square_lattice(data_.get(), IVector<AsValues, InitViewInt>(dim).data(), nei, directed, mutual, &periodic);
  igraph_vector_bool_destroy(&periodic);
  init_attr();
}

IGraph::IGraph(int n, bool directed, bool mutual, bool circular): IGraph::IGraph() {
  igraph_ring(data_.get(), n, directed, mutual, circular);
  init_attr();
}

IGraph::IGraph(int n, int children, int mode): IGraph::IGraph() {
  igraph_kary_tree(data_.get(), n, children, static_cast<igraph_tree_mode_t>(mode));
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

IGraph::IGraph(const IGraph& other, const cpp11::integers& vids, int impl): IGraph::IGraph() {
  igraph_induced_subgraph(
    other.data(), data_.get(), ISelectorInPlace(vids).vss(),
    static_cast<igraph_subgraph_implementation_t>(impl));
  init_attr();
}

void IGraph::init_attr() {
  impl::set_data_frame_attributes(&Vattr_, vcount());
  impl::set_data_frame_attributes(&Eattr_, ecount());
}

[[cpp11::register]]
cpp11::external_pointer<IGraph>
graph_from_data_frame_(const cpp11::data_frame& df, bool directed = true) {
  switch (TYPEOF(df.at(0))) {
    case INTSXP:  return impl::graph_from_data_frame<int>(df, directed);
    case REALSXP: return impl::graph_from_data_frame<double>(df, directed);
    case STRSXP:  return impl::graph_from_data_frame<cpp11::r_string>(df, directed);
    default:
      cpp11::stop("Invalid type for vertex names: %d", TYPEOF(df.at(0)));
  }
}

[[cpp11::register]]
cpp11::external_pointer<IGraph>
graph_from_symbolic_edgelist_(const cpp11::sexp edgelist, bool directed) {
  switch (TYPEOF(edgelist)) {
    case INTSXP:  return impl::graph_from_symbolic_edges(impl::flatten_edgelist<int>(edgelist), directed);
    case REALSXP: return impl::graph_from_symbolic_edges(impl::flatten_edgelist<double>(edgelist), directed);
    case STRSXP:  return impl::graph_from_symbolic_edges(impl::flatten_edgelist<cpp11::r_string>(edgelist), directed);
    default:
      cpp11::stop("Invalid type for vertex names: %d", TYPEOF(edgelist));
  }
}

[[cpp11::register]]
cpp11::external_pointer<IGraph>
graph_from_edgelist_(const cpp11::sexp edgelist, bool directed = true) {
  return new IGraph(impl::flatten_edgelist<int>(edgelist), 0, directed);
}

[[cpp11::register]]
cpp11::external_pointer<IGraph>
graph_create_(const cpp11::integers& edges, int n = 0, bool directed = true) {
  return new IGraph(edges, n, directed);
}

[[cpp11::register]]
cpp11::external_pointer<IGraph>
graph_star_(int n, int mode = 0, int center = 1) {
  return new IGraph(n, mode, static_cast<double>(center));
}

[[cpp11::register]]
cpp11::external_pointer<IGraph>
graph_lattice_(const cpp11::integers& dim, int nei = 1, bool directed = false, bool mutual = false, bool circular = false) {
  return new IGraph(dim, nei, directed, mutual, circular);
}

[[cpp11::register]]
cpp11::external_pointer<IGraph>
graph_ring_(int n, bool directed = false, bool mutual = false, bool circular = true) {
  return new IGraph(n, directed, mutual, circular);
}

[[cpp11::register]]
cpp11::external_pointer<IGraph>
graph_tree_(int n, int children = 2, int mode = 0) {
  return new IGraph(n, children, mode);
}

[[cpp11::register]]
cpp11::external_pointer<IGraph>
graph_full_(int n, bool directed = false, bool mutual = false) {
  return new IGraph(n, directed, mutual);
}

[[cpp11::register]]
cpp11::external_pointer<IGraph>
graph_famous_(const char* name) {
  return new IGraph(name);
}

[[cpp11::register]]
cpp11::external_pointer<IGraph>
induced_subgraph_(const cpp11::external_pointer<IGraph> other, const cpp11::integers& vids, int impl) {
  return new IGraph(*other.get(), vids, impl);
}
