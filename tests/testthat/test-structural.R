context("test-structural")

test_that("shortest_paths works", {
  g = graph_tree(7L)
  from = seq_len(3L)
  to = seq_len(3L) + 4L
  expect_is(shortest_paths(g), "matrix")
  expect_equal(dim(shortest_paths(g)), c(g$vcount, g$vcount))
  expect_equal(dim(shortest_paths(g, from)), c(length(from), length(from)))
  expect_equal(dim(shortest_paths(g, from, to)), c(length(from), length(to)))
  expect_is(shortest_paths(g, weights = g$E), "matrix")
})

test_that("neighborhood_size works", {
  g = graph_tree(7L)
  vids = seq_len(3L)
  expect_length(neighborhood_size(g), g$vcount)
  expect_length(neighborhood_size(g, vids), length(vids))
  expect_equal(neighborhood_size(g, order = 42L, mode = 3L), rep(g$vcount, g$vcount))
  expect_equal(neighborhood_size(g, order = 42L, mindist = 42L), rep(0, g$vcount))
})

test_that("neighborhood works", {
  g = graph_tree(7L)
  vids = seq_len(3L)
  expect_length(neighborhood(g), g$vcount)
  expect_length(neighborhood(g, vids), length(vids))
  expect_equal(lengths(neighborhood(g, mode = 1L)), neighborhood_size(g, mode = 1L))
  expect_equal(lengths(neighborhood(g, mode = 2L)), neighborhood_size(g, mode = 2L))
  expect_equal(lengths(neighborhood(g, mode = 3L)), neighborhood_size(g, mode = 3L))
  expect_equal(lengths(neighborhood(g, order = 42L)), neighborhood_size(g, order = 42L))
  expect_equal(lengths(neighborhood(g, order = 42L, mode = 3L)), rep(g$vcount, g$vcount))
  expect_equal(neighborhood(g, order = 42L, mindist = 42L), rep(list(numeric(0L)), g$vcount))
})

test_that("induced_subgraph works", {
  g = graph_tree(7L)
  vids = seq_len(3L)
  subg = induced_subgraph(g, vids)
  expect_s4_class(subg, "Rcpp_IGraph")
  expect_length(subg$V, length(vids))
  expect_equal(nrow(subg$Vattr), subg$vcount)
  expect_equal(nrow(subg$Eattr), subg$ecount)
  expect_equal(ncol(subg$Vattr), ncol(g$Vattr))
  expect_equal(ncol(subg$Eattr), ncol(g$Eattr))
})