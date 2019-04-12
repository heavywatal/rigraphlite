context("test-experimental")

test_that("upstream_vertices works", {
  g = graph_tree(7L)
  g = graph_tree(15L)
  expect_equal(find_common_ancestors(g, c(6, 7)), c(3, 1))
  expect_length(upstream_vertices(g, c(6, 7), to_mrca = TRUE), 3L)
  expect_length(upstream_vertices(g, c(6, 7), to_mrca = FALSE), 4L)
})
