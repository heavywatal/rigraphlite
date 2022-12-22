test_that("upstream_vertices works", {
  g = graph_tree(7L)
  g = graph_tree(15L)
  expect_identical(find_common_ancestors(g, c(6, 7)), c(3L, 1L))
  expect_length(upstream_vertices(g, c(6, 7), to_mrca = TRUE), 3L)
  expect_length(upstream_vertices(g, c(6, 7), to_mrca = FALSE), 4L)
})
