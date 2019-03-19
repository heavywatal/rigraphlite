n = 10000L
rigraph = igraph::make_tree(n)
ligraph = igraphlite::graph_tree(n)

bench::mark(
  igraph::make_tree(n),
  igraphlite::graph_tree(n),
  check = FALSE
)

df = as.data.frame(ligraph)
bench::mark(
  igraph::graph_from_data_frame(df),
  igraphlite::graph_from_data_frame(df),
  check = FALSE
)

bench::mark(
  igraph::as_data_frame(rigraph),
  as.data.frame(ligraph),
  check = FALSE
)

bench::mark(
  igraph::V(rigraph),
  ligraph$V,
  check = FALSE
)

bench::mark(
  igraph::V(rigraph)[igraph::degree(rigraph, mode = "out") == 0L],
  ligraph$sink,
  check = FALSE
)

bench::mark(
  igraph::degree(rigraph),
  igraphlite::degree(ligraph),
  degree(ligraph),
  ligraph$degree(numeric(0), mode = 3L, loop = TRUE)
)

load_all()
n = 1023L
rigraph = igraph::make_tree(n)
ligraph = igraphlite::graph_tree(n)
plot(ligraph)
bench::mark(
  igraph::distances(rigraph),
  igraphlite::shortest_paths(ligraph)
)

from = ligraph$sink %>% head(length(.) / 2L)
to = ligraph$sink %>% tail(length(.) / 2L)
bench::mark(
  igraph::distances(rigraph, from, to),
  igraphlite::shortest_paths(ligraph, from, to),
  check = FALSE
)

bench::mark(
  mean_distances(ligraph, from, to),
  mean_distances_mat(ligraph, from, to),
  mean_distances_vec(ligraph, from, to),
  mean_distances_hist(ligraph, from, to),
  mean_distances_avg(ligraph, from, to),
  check = FALSE
)

bench::mark(
  mean_distances(ligraph, ligraph$sink),
  mean_distances_mat(ligraph, ligraph$sink),
  mean_distances_vec(ligraph, ligraph$sink),
  mean_distances_hist(ligraph, ligraph$sink),
  mean_distances_avg(ligraph, ligraph$sink),
  check = FALSE
)

bench::mark(
  mean_distances(ligraph),
  mean_distances_mat(ligraph),
  mean_distances_vec(ligraph),
  mean_distances_hist(ligraph),
  mean_distances_avg(ligraph),
  check = FALSE
)

bench::mark(
  igraph::ego_size(rigraph),
  igraphlite::neighborhood_size(ligraph, mode = 3L)
)

bench::mark(
  igraph::ego(rigraph),
  igraphlite::neighborhood(ligraph, mode = 3L),
  check = FALSE
)

# #######1#########2#########3#########4#########5#########6#########7#########

load_all()
g = graph_tree(10L)
bench::mark(
  g$average_path_length(FALSE),
  average_path_length(g)
)

# all paths between root and tips
g = graph_tree(511L)
bench::mark(
  get_shortest_paths(g, 1L, g$sink, mode = 1L),
  neighborhood(g, g$sink, order = 65535L, mode = 2L),
  g$subcomponents(g$sink, mode = 2L),
  lapply(g$sink, subcomponent, graph = g, mode = 2L),
  check = FALSE
)
