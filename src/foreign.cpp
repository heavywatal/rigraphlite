// <https://igraph.org/c/doc/igraph-Foreign.html>
#include "igraph.hpp"

#include <igraph/igraph_foreign.h>

[[cpp11::register]] SEXP
read_graph_edgelist_(const char* path, const bool directed) {
  cpp11::external_pointer<IGraph> graph(new IGraph());
  FILE* fp = fopen(path, "r");
  igraph_read_graph_edgelist(graph->data(), fp, 0, directed);
  fclose(fp);
  graph->init_attr();
  return graph;
}

[[cpp11::register]] SEXP
write_graph_edgelist_(const cpp11::external_pointer<IGraph> graph, const char* path) {
  FILE* fp = fopen(path, "w");
  igraph_write_graph_edgelist(graph->data(), fp);
  fclose(fp);
  return graph;
}

[[cpp11::register]] SEXP
read_graph_ncol_(const char* path, const bool names, const bool directed) {
  cpp11::external_pointer<IGraph> graph(new IGraph());
  FILE* fp = fopen(path, "r");
  igraph_read_graph_ncol(graph->data(), fp, nullptr, names, IGRAPH_ADD_WEIGHTS_IF_PRESENT, directed);
  fclose(fp);
  graph->init_attr();
  return graph;
}

[[cpp11::register]] SEXP
write_graph_ncol_(const cpp11::external_pointer<IGraph> graph, const char* path) {
  const char* names = nullptr;
  const char* weights = nullptr;
  FILE* fp = fopen(path, "w");
  igraph_write_graph_ncol(graph->data(), fp, names, weights);
  fclose(fp);
  return graph;
}

[[cpp11::register]] SEXP
read_graph_lgl_(const char* path, const bool names, const bool directed) {
  cpp11::external_pointer<IGraph> graph(new IGraph());
  FILE* fp = fopen(path, "r");
  igraph_read_graph_lgl(graph->data(), fp, names, IGRAPH_ADD_WEIGHTS_IF_PRESENT, directed);
  fclose(fp);
  graph->init_attr();
  return graph;
}

[[cpp11::register]] SEXP
write_graph_lgl_(const cpp11::external_pointer<IGraph> graph, const char* path, const bool isolates) {
  const char* names = nullptr;
  const char* weights = nullptr;
  FILE* fp = fopen(path, "w");
  igraph_write_graph_lgl(graph->data(), fp, names, weights, isolates);
  fclose(fp);
  return graph;
}

[[cpp11::register]] SEXP
read_graph_graphml_(const char* path, const int index) {
  cpp11::external_pointer<IGraph> graph(new IGraph());
  FILE* fp = fopen(path, "r");
  igraph_read_graph_graphml(graph->data(), fp, index);
  fclose(fp);
  graph->init_attr();
  return graph;
}

[[cpp11::register]] SEXP
write_graph_graphml_(const cpp11::external_pointer<IGraph> graph, const char* path, const bool prefixattr) {
  FILE* fp = fopen(path, "w");
  igraph_write_graph_graphml(graph->data(), fp, prefixattr);
  fclose(fp);
  return graph;
}

[[cpp11::register]] SEXP
read_graph_gml_(const char* path) {
  cpp11::external_pointer<IGraph> graph(new IGraph());
  FILE* fp = fopen(path, "r");
  igraph_read_graph_gml(graph->data(), fp);
  fclose(fp);
  graph->init_attr();
  return graph;
}

[[cpp11::register]] SEXP
write_graph_gml_(const cpp11::external_pointer<IGraph> graph, const char* path, const char* creator) {
  FILE* fp = fopen(path, "w");
  igraph_write_graph_gml(graph->data(), fp, 0, nullptr, creator);
  fclose(fp);
  return graph;
}

[[cpp11::register]] SEXP
read_graph_pajek_(const char* path) {
  cpp11::external_pointer<IGraph> graph(new IGraph());
  FILE* fp = fopen(path, "r");
  igraph_read_graph_pajek(graph->data(), fp);
  fclose(fp);
  graph->init_attr();
  return graph;
}

[[cpp11::register]] SEXP
write_graph_pajek_(const cpp11::external_pointer<IGraph> graph, const char* path) {
  FILE* fp = fopen(path, "w");
  igraph_write_graph_pajek(graph->data(), fp);
  fclose(fp);
  return graph;
}

[[cpp11::register]] SEXP
read_graph_dl_(const char* path, const bool directed) {
  cpp11::external_pointer<IGraph> graph(new IGraph());
  FILE* fp = fopen(path, "r");
  igraph_read_graph_dl(graph->data(), fp, directed);
  fclose(fp);
  graph->init_attr();
  return graph;
}

[[cpp11::register]] SEXP
write_graph_dot_(const cpp11::external_pointer<IGraph> graph, const char* path) {
  FILE* fp = fopen(path, "w");
  igraph_write_graph_dot(graph->data(), fp);
  fclose(fp);
  return graph;
}

[[cpp11::register]] SEXP
write_graph_leda_(const cpp11::external_pointer<IGraph> graph, const char* path) {
  FILE* fp = fopen(path, "w");
  igraph_write_graph_leda(graph->data(), fp, nullptr, nullptr);
  fclose(fp);
  return graph;
}
