context("test-basic")

test_that("neighbors works", {
  g = graph_tree(7L)
  expect_error(neighbors(g, 0L))
  expect_equal(neighbors(g, 1L, mode = 1L), c(2, 3))
  expect_equal(neighbors(g, 1L, mode = 2L), numeric(0L))
  expect_equal(neighbors(g, 1L, mode = 3L), c(2, 3))
})

test_that("incident works", {
  g = graph_tree(7L)
  expect_error(incident(g, 0L))
  expect_equal(incident(g, 1L, mode = 1L), c(1, 2))
  expect_equal(incident(g, 1L, mode = 2L), numeric(0L))
  expect_equal(incident(g, 1L, mode = 3L), c(1, 2))
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

test_that("add_edges/add_vertices works", {
  g = graph_tree(7L)
  g$Vattr$id = g$V
  g$Vattr$name = LETTERS[g$V]
  g$Eattr$id = g$E
  g$Eattr$name = LETTERS[g$E]
  g$add_edges(c(6, 7, 8, 9))
  expect_length(g$E, 8L)
  expect_length(g$Eattr[[1L]], 8L)
  expect_equal(nrow(g$Eattr), 8L)
  expect_length(g$V, 9L)
  expect_length(g$Vattr[[1L]], 9L)
  expect_equal(nrow(g$Vattr), 9L)
})
