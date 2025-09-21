test_that("edge_betweenness() works", {
  g = graph_tree(7L)
  plot(g)
  exp = c(2, 2, 1, 1, 1, 1)
  expect_identical(edge_betweenness(g, from = Vsource(g), to = Vsink(g)), exp)
  expect_identical(edge_betweenness(g, cutoff = 1), c(1, 1, 1, 1, 1, 1))
  expect_warning(edge_betweenness(g, from = Vsource(g), to = Vsink(g), cutoff = 1), "ignored")
  expect_warning(edge_betweenness_subset(g, from = Vsource(g), to = Vsink(g)), "deprecated")

  skip("'weights' ignored in C igraph?")
  w = rep_len(3, ecount(g))
  expect_identical(edge_betweenness_subset(g, weights = w, from = Vsource(g), to = Vsink(g)), w * exp)
})
