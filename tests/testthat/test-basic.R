context("test-basic")

test_that("neighbors works", {
  g = graph_tree(7L)
  expect_error(neighbors(g, 0L))
  expect_equal(neighbors(g, 1L, mode = 1L), c(2, 3))
  expect_equal(neighbors(g, 1L, mode = 2L), numeric(0L))
  expect_equal(neighbors(g, 1L, mode = 3L), c(2, 3))
})

test_that("degree works", {
  g = graph_tree(7L)
  vids = seq_len(3L)
  expect_length(degree(g), g$vcount)
  expect_length(degree(g, vids), length(vids))
  expect_equal(degree(g, mode = 1L), c(2, 2, 2, 0, 0, 0, 0))
  expect_equal(degree(g, mode = 2L), c(0, 1, 1, 1, 1, 1, 1))
  expect_equal(degree(g, mode = 3L), c(2, 3, 3, 1, 1, 1, 1))
})
