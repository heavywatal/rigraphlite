#include "igraphlite_types.h"

RCPP_MODULE(igraph) {
  Rcpp::class_<IGraph>("IGraph")
    .constructor<const IGraph&, Rcpp::IntegerVector, int>() // induced_subgraph

    // Basic interface
    .property("vcount", &IGraph::vcount)
    .property("ecount", &IGraph::ecount)
    .property("is_directed", &IGraph::is_directed)
    .const_method("edge", &IGraph::edge)
    .const_method("neighbors", &IGraph::neighbors)
    .const_method("incident", &IGraph::incident)
    .const_method("degree", &IGraph::degree)
    .method("add_edges", &IGraph::add_edges)
    .method("add_vertices", &IGraph::add_vertices)
    .method("delete_edges", &IGraph::delete_edges)
    .method("delete_vertices", &IGraph::delete_vertices)

    // Structural properties
    .const_method("are_adjacent", &IGraph::are_adjacent)
    .const_method("distances", &IGraph::distances)
    .const_method("get_shortest_paths", &IGraph::get_shortest_paths)
    .const_method("get_all_shortest_paths", &IGraph::get_all_shortest_paths)
    .const_method("get_all_simple_paths", &IGraph::get_all_simple_paths)
    .const_method("average_path_length", &IGraph::average_path_length)
    .const_method("path_length_hist", &IGraph::path_length_hist)
    .const_method("neighborhood_size", &IGraph::neighborhood_size)
    .const_method("neighborhood", &IGraph::neighborhood)
    .const_method("subcomponent", &IGraph::subcomponent)
    .const_method("subcomponents", &IGraph::subcomponents)

    .const_method("mean_distances", &IGraph::mean_distances)

    // Layout
    .const_method("layout_random", &IGraph::layout_random)
    .const_method("layout_drl", &IGraph::layout_drl)
    .const_method("layout_fruchterman_reingold", &IGraph::layout_fruchterman_reingold)
    .const_method("layout_mds", &IGraph::layout_mds)
    .const_method("layout_reingold_tilford", &IGraph::layout_reingold_tilford)
    .const_method("layout_reingold_tilford_circular", &IGraph::layout_reingold_tilford_circular)

    // Original methods
    .const_method("as_adjlist", &IGraph::as_adjlist)
    .const_method("as_inclist", &IGraph::as_inclist)
    .const_method("as_edgelist", &IGraph::as_edgelist)

    .property("Vattr", &IGraph::getVattr, &IGraph::setVattr)
    .property("Eattr", &IGraph::getEattr, &IGraph::setEattr)

    // igraph_t
    .property("from", &IGraph::from)
    .property("to", &IGraph::to)
    .property("oi", &IGraph::oi)
    .property("ii", &IGraph::ii)
    .property("os", &IGraph::os)
    .property("is", &IGraph::is)
  ;
}
