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
  igraphlite::V(ligraph),
  check = FALSE
)

bench::mark(
  igraph::V(rigraph)[igraph::degree(rigraph, mode = "out") == 0L],
  Vsink(ligraph),
  check = FALSE
)

bench::mark(
  igraph::degree(rigraph),
  igraphlite::degree(ligraph),
  ligraph$degree(numeric(0), mode = 3L, loop = TRUE)
)

load_all()
n = 1023L
rigraph = igraph::make_tree(n)
ligraph = igraphlite::graph_tree(n)
plot(ligraph)
bench::mark(
  igraph::distances(rigraph),
  igraphlite::distances(ligraph)
)

n_half = length(Vsink(ligraph)) / 2L
from = Vsink(ligraph) |> head(n_half)
to = Vsink(ligraph) |> tail(n_half)
bench::mark(
  igraph::distances(rigraph, from, to),
  igraphlite::distances(ligraph, from, to),
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

result = tekkamaki::tekka("--seed 42 --sa 1,1 --sj 1,1")
sample_family = result$sample_family[[1]] |> dplyr::arrange(id)
sample_family |> dplyr::arrange(id)
tekkamaki::find_kinship(sample_family)
graph = sample_family |> tekkamaki::as_igraph()
plot(graph)
as_vids(graph, c("3", "6", "8"))
ca = common_ancestors(graph, c(156, 262))
subg = induced_subgraph(graph, do.call(intersect, ca))
as_vnames(subg, Vsink(subg))
ca = common_ancestors(graph, c(262, 310))

# install.packages(c("devtools", "bench", "tidyverse"))
# remotes::install_github("heavywatal/rigraphlite")
library(tidyverse)
library(igraphlite)
n = 1023L
g = igraphlite::graph_tree(n, mode = 2L)
from = Vsink(g)
to = Vsink(g)
bench::mark(
  mean_distances_mat(g, from, to, mode = 1L),
  mean_distances_mat(g, from, to, mode = 2L),
  mean_distances_mat(g, from, to, mode = 3L),
  mean_distances_vec(g, from, to, mode = 1L),
  mean_distances_vec(g, from, to, mode = 2L),
  mean_distances_vec(g, from, to, mode = 3L),
  mean_distances_avg(g, from, to),
  mean_distances_avg(g),
  check = FALSE
)[,1:10]
#                                   expression          min         mean       median          max    itr/sec     mem_alloc  n_gc n_itr   total_time
#                                        <chr> <bench_time> <bench_time> <bench_time> <bench_time>      <dbl> <bench_bytes> <dbl> <int> <bench_time>
# 1 mean_distances_mat(g, from, to, mode = 1L)       34.2ms       34.6ms       34.4ms       35.5ms 28.9074998        2.02MB     1    14      484.3ms
# 2 mean_distances_mat(g, from, to, mode = 2L)       34.3ms       34.7ms       34.6ms         36ms 28.7777870        2.02MB     1    14      486.5ms
# 3 mean_distances_mat(g, from, to, mode = 3L)       12.6ms       12.9ms       12.8ms       14.1ms 77.5247046        2.02MB     4    34      438.6ms
# 4 mean_distances_vec(g, from, to, mode = 1L)      108.5ms      110.1ms      108.9ms      114.1ms  9.0845938       16.23KB     0     5      550.4ms
# 5 mean_distances_vec(g, from, to, mode = 2L)      153.2ms      154.3ms      154.1ms      155.8ms  6.4815314       16.23KB     0     4      617.1ms
# 6 mean_distances_vec(g, from, to, mode = 3L)         3.8s         3.8s         3.8s         3.8s  0.2628722       16.23KB     0     1         3.8s
# 7            mean_distances_avg(g, from, to)       19.8ms       20.1ms         20ms       21.4ms 49.7976920      187.39KB     0    25        502ms
# 8                      mean_distances_avg(g)      18.17ms      18.57ms      18.44ms      19.23ms 53.8513661          264B     0    27     501.38ms

bench::mark(
  OUT___1col = g$shortest_paths(from, to[1], numeric(0), 1L, ""),
   IN___1col = g$shortest_paths(from, to[1], numeric(0), 2L, ""),
  ALL___1col = g$shortest_paths(from, to[1], numeric(0), 3L, ""),
  ALL_512col = g$shortest_paths(from, to, numeric(0), 3L, ""),
  check = FALSE
)[,1:10]
#   expression          min         mean       median          max    itr/sec     mem_alloc  n_gc n_itr   total_time
#        <chr> <bench_time> <bench_time> <bench_time> <bench_time>      <dbl> <bench_bytes> <dbl> <int> <bench_time>
# 1 OUT___1col      268.4µs      279.2µs     274.48µs     605.32µs 3581.70844        8.09KB     1  1776        496ms
# 2  IN___1col      356.3µs     366.66µs     361.79µs     541.37µs 2727.32030        8.09KB     1  1354        496ms
# 3 ALL___1col        6.9ms       7.17ms       7.06ms       7.92ms  139.38327        8.09KB     0    70        502ms
# 4 ALL_512col       12.7ms      13.22ms      13.17ms      14.03ms   75.64487        2.01MB     2    36        476ms

bench::mark(
  g$as_adjlist(1L),
  g$as_adjlist(2L),
  g$as_adjlist(3L),
  check = FALSE
)

bench::mark(
  mean_distances(ligraph, Vsink(ligraph)),
  mean_distances_mat(ligraph, Vsink(ligraph)),
  mean_distances_vec(ligraph, Vsink(ligraph)),
  mean_distances_hist(ligraph, Vsink(ligraph)),
  mean_distances_avg(ligraph, Vsink(ligraph)),
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
  get_shortest_paths(g, 1L, Vsink(g), mode = 1L),
  neighborhood(g, Vsink(g), order = 65535L, mode = 2L),
  g$subcomponents(Vsink(g), mode = 2L),
  lapply(Vsink(g), subcomponent, graph = g, mode = 2L),
  check = FALSE
)
