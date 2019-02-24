load_all()
g = graph_tree(2000)
for (i in seq_len(1000)) {
  neighborhood(g, seq_len(g$vcount()), 65536L)
}

g = graph_tree(1000)
g$V[g$is_sink]
g$V[g$is_source]
g$sink
g$source

g = graph_tree(17)
g$Vattr %>% ggplot(aes(x, y)) + geom_point() + coord_fixed()

g$layout_drl()
g$layout_fruchterman_reingold()
g$layout_mds()
g$layout_reingold_tilford(3)
g$layout_reingold_tilford_circular(3)

bench::mark(
  g$V[g$is_sink],
  g$sink
)


Vsink(g)
degree(g)
terminal(g)
is_sink(g)
(g)
vids = sample.int(g$vcount(), 100L)

# bench::mark(
#   mean_branch_length_h(g, vids),
#   mean_branch_length_c(g, vids),
#   mean_branch_length_m(g, vids),
#   check = FALSE
# )

bench::mark(
  g$path_length_hist(FALSE),
  path_length_count_within(g, vids, FALSE),
  path_length_count_between(g, vids, vids, FALSE),
  check = FALSE
)

easierprof(
g$path_length_count(vids, FALSE)
)

vids = as.numeric(seq_len(g$vcount()))
path_length_count(g, vids, vids, FALSE)
