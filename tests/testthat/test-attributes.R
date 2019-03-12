context("test-attributes")

test_that("name-id conversion works", {
  edges = seq_len(8L)
  el = matrix(edges, ncol = 2L)
  vnames = as.vector(t(el))
  g = graph_from_symbolic_edgelist(el)
  expect_equal(Vnames(g), vnames)
  expect_equal(as_vnames(g, g$V), vnames)
  expect_equal(as_vids(g, vnames), g$V)
})
