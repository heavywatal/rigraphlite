# Package index

## R Interface

- [`is_igraph()`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  :

  `igraph_ptr`: cpp11-powered class for igraph objects

- [`as_igraph()`](https://heavywatal.github.io/rigraphlite/reference/conversion.md)
  [`as.data.frame(`*`<igraph_ptr>`*`)`](https://heavywatal.github.io/rigraphlite/reference/conversion.md)
  [`as.matrix(`*`<igraph_ptr>`*`)`](https://heavywatal.github.io/rigraphlite/reference/conversion.md)
  : Convert igraph objects to and from other formats.

- [`graph_from_data_frame()`](https://heavywatal.github.io/rigraphlite/reference/conversion-impl.md)
  [`graph_from_symbolic_edgelist()`](https://heavywatal.github.io/rigraphlite/reference/conversion-impl.md)
  [`graph_from_edgelist()`](https://heavywatal.github.io/rigraphlite/reference/conversion-impl.md)
  : Convert edge lists to igraph objects.

## Basic Interface

<https://igraph.org/c/doc/igraph-Basic.html>

- [`graph_empty()`](https://heavywatal.github.io/rigraphlite/reference/constructors.md)
  [`graph_copy()`](https://heavywatal.github.io/rigraphlite/reference/constructors.md)
  : Graph constructors
- [`vcount()`](https://heavywatal.github.io/rigraphlite/reference/basic.md)
  [`ecount()`](https://heavywatal.github.io/rigraphlite/reference/basic.md)
  [`is_directed()`](https://heavywatal.github.io/rigraphlite/reference/basic.md)
  : Basic query operations
- [`edge()`](https://heavywatal.github.io/rigraphlite/reference/basic-adjacent.md)
  [`edges()`](https://heavywatal.github.io/rigraphlite/reference/basic-adjacent.md)
  [`get_eids()`](https://heavywatal.github.io/rigraphlite/reference/basic-adjacent.md)
  [`get_all_eids_between()`](https://heavywatal.github.io/rigraphlite/reference/basic-adjacent.md)
  [`neighbors()`](https://heavywatal.github.io/rigraphlite/reference/basic-adjacent.md)
  [`incident()`](https://heavywatal.github.io/rigraphlite/reference/basic-adjacent.md)
  [`degree()`](https://heavywatal.github.io/rigraphlite/reference/basic-adjacent.md)
  : Basic query operations to get adjacency
- [`add_edges()`](https://heavywatal.github.io/rigraphlite/reference/basic-add-delete.md)
  [`add_vertices()`](https://heavywatal.github.io/rigraphlite/reference/basic-add-delete.md)
  [`delete_edges()`](https://heavywatal.github.io/rigraphlite/reference/basic-add-delete.md)
  [`delete_vertices()`](https://heavywatal.github.io/rigraphlite/reference/basic-add-delete.md)
  : Adding and deleting vertices and edges
- [`IGRAPH_VCOUNT_MAX`](https://heavywatal.github.io/rigraphlite/reference/basic-macros.md)
  [`IGRAPH_ECOUNT_MAX`](https://heavywatal.github.io/rigraphlite/reference/basic-macros.md)
  [`IGRAPH_UNLIMITED`](https://heavywatal.github.io/rigraphlite/reference/basic-macros.md)
  [`expand_path_to_pairs()`](https://heavywatal.github.io/rigraphlite/reference/basic-macros.md)
  [`is_same_graph()`](https://heavywatal.github.io/rigraphlite/reference/basic-macros.md)
  : Miscellaneous macros

## Data Structure

<https://igraph.org/c/doc/igraph-Data-structures.html>

- [`as_adjlist()`](https://heavywatal.github.io/rigraphlite/reference/adjlist.md)
  [`as_inclist()`](https://heavywatal.github.io/rigraphlite/reference/adjlist.md)
  : Adjacency lists and incidence lists

## Random numbers

<https://igraph.org/c/doc/igraph-Random.html>

- [`igraph_rng_seed()`](https://heavywatal.github.io/rigraphlite/reference/random.md)
  : Seeds a random number generator

## Graph Generators

### Deterministic Graph Generators

<https://igraph.org/c/doc/igraph-Generators.html>

- [`graph_create()`](https://heavywatal.github.io/rigraphlite/reference/graph_create.md)
  : Create a graph with the specified edges
- [`graph_star()`](https://heavywatal.github.io/rigraphlite/reference/graph_star.md)
  : Create a star graph
- [`graph_hypercube()`](https://heavywatal.github.io/rigraphlite/reference/graph_hypercube.md)
  : Create an n-dimensional hypercube graph
- [`graph_square_lattice()`](https://heavywatal.github.io/rigraphlite/reference/graph_lattice.md)
  [`graph_triangular_lattice()`](https://heavywatal.github.io/rigraphlite/reference/graph_lattice.md)
  [`graph_hexagonal_lattice()`](https://heavywatal.github.io/rigraphlite/reference/graph_lattice.md)
  [`graph_ring()`](https://heavywatal.github.io/rigraphlite/reference/graph_lattice.md)
  [`graph_path()`](https://heavywatal.github.io/rigraphlite/reference/graph_lattice.md)
  : Create arbitrary dimensional lattices
- [`graph_lcf()`](https://heavywatal.github.io/rigraphlite/reference/graph_lcf.md)
  [`graph_circulant()`](https://heavywatal.github.io/rigraphlite/reference/graph_lcf.md)
  : Creates a graph from LCF notation
- [`graph_kary_tree()`](https://heavywatal.github.io/rigraphlite/reference/graph_tree.md)
  : Create a tree graph
- [`graph_full()`](https://heavywatal.github.io/rigraphlite/reference/graph_full.md)
  : Create a full graph (complete graph)
- [`graph_famous()`](https://heavywatal.github.io/rigraphlite/reference/graph_famous.md)
  : Create a famous graph by simply providing its name

### Stochastic Graph Generators (“games”)

<https://igraph.org/c/doc/igraph-Games.html>

- [`erdos_renyi_game_gnm()`](https://heavywatal.github.io/rigraphlite/reference/games-erdos-renyi.md)
  [`erdos_renyi_game_gnp()`](https://heavywatal.github.io/rigraphlite/reference/games-erdos-renyi.md)
  : The Erdős-Rényi and related models
- [`degree_sequence_game()`](https://heavywatal.github.io/rigraphlite/reference/games-degree-constrained.md)
  [`k_regular_game()`](https://heavywatal.github.io/rigraphlite/reference/games-degree-constrained.md)
  [`rewire()`](https://heavywatal.github.io/rigraphlite/reference/games-degree-constrained.md)
  : Degree-constrained models
- [`watts_strogatz_game()`](https://heavywatal.github.io/rigraphlite/reference/games-edge-rewiring.md)
  [`rewire_edges()`](https://heavywatal.github.io/rigraphlite/reference/games-edge-rewiring.md)
  : Edge rewiring models

## Attributes of Graph, Vertices, and Edges

<https://igraph.org/c/doc/igraph-Attributes.html>

- [`Vattr()`](https://heavywatal.github.io/rigraphlite/reference/attributes.md)
  [`` `Vattr<-`() ``](https://heavywatal.github.io/rigraphlite/reference/attributes.md)
  [`Eattr()`](https://heavywatal.github.io/rigraphlite/reference/attributes.md)
  [`` `Eattr<-`() ``](https://heavywatal.github.io/rigraphlite/reference/attributes.md)
  [`V()`](https://heavywatal.github.io/rigraphlite/reference/attributes.md)
  [`E()`](https://heavywatal.github.io/rigraphlite/reference/attributes.md)
  : Get and set vertex and edge attributes
- [`Vnames()`](https://heavywatal.github.io/rigraphlite/reference/vnames.md)
  [`as_vids()`](https://heavywatal.github.io/rigraphlite/reference/vnames.md)
  [`as_vnames()`](https://heavywatal.github.io/rigraphlite/reference/vnames.md)
  : Conversion between vertex IDs and names
- [`igraph_from()`](https://heavywatal.github.io/rigraphlite/reference/from-to.md)
  [`igraph_to()`](https://heavywatal.github.io/rigraphlite/reference/from-to.md)
  : Quick access to edge list columns

## Structural Properties

<https://igraph.org/c/doc/igraph-Structural.html>

- [`are_adjacent()`](https://heavywatal.github.io/rigraphlite/reference/adjacent.md)
  : Basic Properties
- [`distances()`](https://heavywatal.github.io/rigraphlite/reference/distances.md)
  [`average_path_length()`](https://heavywatal.github.io/rigraphlite/reference/distances.md)
  [`path_length_hist()`](https://heavywatal.github.io/rigraphlite/reference/distances.md)
  [`eccentricity()`](https://heavywatal.github.io/rigraphlite/reference/distances.md)
  [`diameter()`](https://heavywatal.github.io/rigraphlite/reference/distances.md)
  [`girth()`](https://heavywatal.github.io/rigraphlite/reference/distances.md)
  [`radius()`](https://heavywatal.github.io/rigraphlite/reference/distances.md)
  : Distance-related Functions
- [`get_shortest_paths()`](https://heavywatal.github.io/rigraphlite/reference/paths.md)
  [`get_all_shortest_paths()`](https://heavywatal.github.io/rigraphlite/reference/paths.md)
  [`get_all_simple_paths()`](https://heavywatal.github.io/rigraphlite/reference/paths.md)
  : Shortest Path Related Functions
- [`global_efficiency()`](https://heavywatal.github.io/rigraphlite/reference/efficiency.md)
  [`local_efficiency()`](https://heavywatal.github.io/rigraphlite/reference/efficiency.md)
  [`average_local_efficiency()`](https://heavywatal.github.io/rigraphlite/reference/efficiency.md)
  : Efficiency measures
- [`neighborhood_size()`](https://heavywatal.github.io/rigraphlite/reference/neighborhood.md)
  [`neighborhood()`](https://heavywatal.github.io/rigraphlite/reference/neighborhood.md)
  : Neighborhood of vertices
- [`subcomponent()`](https://heavywatal.github.io/rigraphlite/reference/components.md)
  [`connected_components()`](https://heavywatal.github.io/rigraphlite/reference/components.md)
  [`is_connected()`](https://heavywatal.github.io/rigraphlite/reference/components.md)
  [`count_reachable()`](https://heavywatal.github.io/rigraphlite/reference/components.md)
  [`transitive_closure()`](https://heavywatal.github.io/rigraphlite/reference/components.md)
  [`articulation_points()`](https://heavywatal.github.io/rigraphlite/reference/components.md)
  [`bridges()`](https://heavywatal.github.io/rigraphlite/reference/components.md)
  [`is_biconnected()`](https://heavywatal.github.io/rigraphlite/reference/components.md)
  [`subcomponents()`](https://heavywatal.github.io/rigraphlite/reference/components.md)
  : Graph Components
- [`closeness()`](https://heavywatal.github.io/rigraphlite/reference/centrality.md)
  [`harmonic_centrality()`](https://heavywatal.github.io/rigraphlite/reference/centrality.md)
  [`betweenness()`](https://heavywatal.github.io/rigraphlite/reference/centrality.md)
  [`edge_betweenness()`](https://heavywatal.github.io/rigraphlite/reference/centrality.md)
  [`edge_betweenness_subset()`](https://heavywatal.github.io/rigraphlite/reference/centrality.md)
  [`pagerank()`](https://heavywatal.github.io/rigraphlite/reference/centrality.md)
  [`constraint()`](https://heavywatal.github.io/rigraphlite/reference/centrality.md)
  [`maxdegree()`](https://heavywatal.github.io/rigraphlite/reference/centrality.md)
  [`strength()`](https://heavywatal.github.io/rigraphlite/reference/centrality.md)
  [`eigenvector_centrality()`](https://heavywatal.github.io/rigraphlite/reference/centrality.md)
  [`hub_and_authority_scores()`](https://heavywatal.github.io/rigraphlite/reference/centrality.md)
  [`convergence_degree()`](https://heavywatal.github.io/rigraphlite/reference/centrality.md)
  : Centrality measures
- [`is_simple()`](https://heavywatal.github.io/rigraphlite/reference/non-simple.md)
  [`has_loop()`](https://heavywatal.github.io/rigraphlite/reference/non-simple.md)
  [`count_loops()`](https://heavywatal.github.io/rigraphlite/reference/non-simple.md)
  [`has_multiple()`](https://heavywatal.github.io/rigraphlite/reference/non-simple.md)
  [`count_multiple()`](https://heavywatal.github.io/rigraphlite/reference/non-simple.md)
  : Non-simple graphs: multiple and loop edges

## Graph cycles

<https://igraph.org/c/doc/igraph-Cycles.html>

- [`is_dag()`](https://heavywatal.github.io/rigraphlite/reference/cycles-acyclic.md)
  [`is_acyclic()`](https://heavywatal.github.io/rigraphlite/reference/cycles-acyclic.md)
  [`topological_sorting()`](https://heavywatal.github.io/rigraphlite/reference/cycles-acyclic.md)
  : Acyclic graphs and feedback sets
- [`is_eulerian()`](https://heavywatal.github.io/rigraphlite/reference/cycles-eulerian.md)
  : Eulerian cycles and paths

## Cliques and independent vertex sets

<https://igraph.org/c/doc/igraph-Cliques.html>

- [`is_complete()`](https://heavywatal.github.io/rigraphlite/reference/cliques.md)
  [`is_clique()`](https://heavywatal.github.io/rigraphlite/reference/cliques.md)
  [`cliques()`](https://heavywatal.github.io/rigraphlite/reference/cliques.md)
  [`clique_size_hist()`](https://heavywatal.github.io/rigraphlite/reference/cliques.md)
  [`largest_cliques()`](https://heavywatal.github.io/rigraphlite/reference/cliques.md)
  [`maximal_cliques()`](https://heavywatal.github.io/rigraphlite/reference/cliques.md)
  [`maximal_cliques_count()`](https://heavywatal.github.io/rigraphlite/reference/cliques.md)
  [`maximal_cliques_hist()`](https://heavywatal.github.io/rigraphlite/reference/cliques.md)
  [`clique_number()`](https://heavywatal.github.io/rigraphlite/reference/cliques.md)
  : Cliques
- [`is_independent_vertex_set()`](https://heavywatal.github.io/rigraphlite/reference/independent.md)
  [`independent_vertex_sets()`](https://heavywatal.github.io/rigraphlite/reference/independent.md)
  [`largest_independent_vertex_sets()`](https://heavywatal.github.io/rigraphlite/reference/independent.md)
  [`maximal_independent_vertex_sets()`](https://heavywatal.github.io/rigraphlite/reference/independent.md)
  [`independence_number()`](https://heavywatal.github.io/rigraphlite/reference/independent.md)
  : Independent vertex sets

## Graph isomorphism

<https://igraph.org/c/doc/igraph-Isomorphism.html>

- [`isomorphic()`](https://heavywatal.github.io/rigraphlite/reference/isomorphic.md)
  [`subisomorphic()`](https://heavywatal.github.io/rigraphlite/reference/isomorphic.md)
  : The simple interface for graph isomorphism
- [`canonical_permutation()`](https://heavywatal.github.io/rigraphlite/reference/permutation.md)
  [`permutate_vertices()`](https://heavywatal.github.io/rigraphlite/reference/permutation.md)
  : Permute the vertices

## Generating Layouts for Graph Drawing

<https://igraph.org/c/doc/igraph-Layout.html>

- [`layout_random()`](https://heavywatal.github.io/rigraphlite/reference/layout-2d.md)
  [`layout_circle()`](https://heavywatal.github.io/rigraphlite/reference/layout-2d.md)
  [`layout_star()`](https://heavywatal.github.io/rigraphlite/reference/layout-2d.md)
  [`layout_grid()`](https://heavywatal.github.io/rigraphlite/reference/layout-2d.md)
  [`layout_drl()`](https://heavywatal.github.io/rigraphlite/reference/layout-2d.md)
  [`layout_fruchterman_reingold()`](https://heavywatal.github.io/rigraphlite/reference/layout-2d.md)
  [`layout_mds()`](https://heavywatal.github.io/rigraphlite/reference/layout-2d.md)
  : 2D layout generators
- [`layout_reingold_tilford()`](https://heavywatal.github.io/rigraphlite/reference/layout-tree.md)
  [`layout_reingold_tilford_circular()`](https://heavywatal.github.io/rigraphlite/reference/layout-tree.md)
  : Layouts for trees and acyclic graphs
- [`layout_nicely()`](https://heavywatal.github.io/rigraphlite/reference/layout.md)
  : Choose a layout algorithm automatically
- [`augment(`*`<igraph_ptr>`*`)`](https://heavywatal.github.io/rigraphlite/reference/plot.md)
  [`plot(`*`<igraph_ptr>`*`)`](https://heavywatal.github.io/rigraphlite/reference/plot.md)
  : Methods for quick visualization

## Miscellaneous operators

<https://igraph.org/c/doc/igraph-Operators.html>

- [`induced_subgraph()`](https://heavywatal.github.io/rigraphlite/reference/subgraph.md)
  [`induced_subgraph_edges()`](https://heavywatal.github.io/rigraphlite/reference/subgraph.md)
  [`subgraph_from_edges()`](https://heavywatal.github.io/rigraphlite/reference/subgraph.md)
  : Miscellaneous operators

## Non-graph related functions

<https://igraph.org/c/doc/igraph-Nongraph.html>

- [`igraph_version()`](https://heavywatal.github.io/rigraphlite/reference/version.md)
  : Get the version of the igraph C library
- [`common_params()`](https://heavywatal.github.io/rigraphlite/reference/common_params.md)
  : Common parameters used throughout the package

## Reading and writing graphs from and to files

<https://igraph.org/c/doc/igraph-Foreign.html>

- [`read_graph()`](https://heavywatal.github.io/rigraphlite/reference/read.md)
  [`read_graph_edgelist()`](https://heavywatal.github.io/rigraphlite/reference/read.md)
  [`read_graph_ncol()`](https://heavywatal.github.io/rigraphlite/reference/read.md)
  [`read_graph_lgl()`](https://heavywatal.github.io/rigraphlite/reference/read.md)
  [`read_graph_graphml()`](https://heavywatal.github.io/rigraphlite/reference/read.md)
  [`read_graph_gml()`](https://heavywatal.github.io/rigraphlite/reference/read.md)
  [`read_graph_pajek()`](https://heavywatal.github.io/rigraphlite/reference/read.md)
  [`read_graph_dl()`](https://heavywatal.github.io/rigraphlite/reference/read.md)
  : Read graphs from files
- [`write_graph()`](https://heavywatal.github.io/rigraphlite/reference/write.md)
  [`write_graph_edgelist()`](https://heavywatal.github.io/rigraphlite/reference/write.md)
  [`write_graph_ncol()`](https://heavywatal.github.io/rigraphlite/reference/write.md)
  [`write_graph_lgl()`](https://heavywatal.github.io/rigraphlite/reference/write.md)
  [`write_graph_graphml()`](https://heavywatal.github.io/rigraphlite/reference/write.md)
  [`write_graph_gml()`](https://heavywatal.github.io/rigraphlite/reference/write.md)
  [`write_graph_pajek()`](https://heavywatal.github.io/rigraphlite/reference/write.md)
  [`write_graph_dot()`](https://heavywatal.github.io/rigraphlite/reference/write.md)
  [`write_graph_leda()`](https://heavywatal.github.io/rigraphlite/reference/write.md)
  : Write graphs to files

## Other Packages

- [`as_igraph(`*`<phylo>`*`)`](https://heavywatal.github.io/rigraphlite/reference/phylo.md)
  [`as_phylo()`](https://heavywatal.github.io/rigraphlite/reference/phylo.md)
  : Conversion between phylo and igraph
- [`as_igraph(`*`<tbl_tree>`*`)`](https://heavywatal.github.io/rigraphlite/reference/tbl_tree.md)
  [`as_tbl_tree()`](https://heavywatal.github.io/rigraphlite/reference/tbl_tree.md)
  : Conversion between tbl_tree and igraph
- [`is_sink()`](https://heavywatal.github.io/rigraphlite/reference/sink.md)
  [`is_source()`](https://heavywatal.github.io/rigraphlite/reference/sink.md)
  [`Vsink()`](https://heavywatal.github.io/rigraphlite/reference/sink.md)
  [`Vsource()`](https://heavywatal.github.io/rigraphlite/reference/sink.md)
  : Shortcuts to get sink/source vertices.
- [`find_common_ancestors()`](https://heavywatal.github.io/rigraphlite/reference/experimental.md)
  [`upstream_vertices()`](https://heavywatal.github.io/rigraphlite/reference/experimental.md)
  : Experimental functions
