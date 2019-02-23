n = 10000L
n = 10L
rigraph = igraph::make_tree(n)
ligraph = igraphlite::graph_tree(n)

bench::mark(
  igraph::make_tree(n),
  igraphlite::graph_tree(n),
  check = FALSE
)

df = ligraph$as_data_frame
bench::mark(
  igraph::graph_from_data_frame(df),
  igraphlite::graph_from_data_frame(df),
  check = FALSE
)

bench::mark(
  igraph::as_data_frame(rigraph),
  ligraph$as_data_frame,
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

n = 10L
ligraph = igraphlite::graph_tree(n)
bench::mark(
  # igraph::degree(rigraph),
  ligraph$degree(numeric(0), mode = 3L, loop = TRUE),
  degree(ligraph),
  igraphlite::degree(ligraph),
  degreep(ligraph),
  degreer(ligraph),
  ligraph$degreem()
)

n = 1000L
rigraph = igraph::make_tree(n)
ligraph = igraphlite::graph_tree(n)
bench::mark(
  igraph::distances(rigraph),
  igraphlite::shortest_paths(ligraph)
)

v = seq_len(n / 2)
bench::mark(
  igraph::distances(rigraph, v, v),
  igraphlite::shortest_paths(ligraph, v, v),
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
