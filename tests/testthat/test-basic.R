context("test-basic")

test_that("basic queries work", {
  g = graph_tree(7L)
  expect_equal(vcount(g), 7L)
  expect_equal(ecount(g), 6L)
  expect_equal(edge(g, 1L), c(1, 2))
  expect_true(is_directed(g))
})

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

test_that("as_adjlist and as_inclist work", {
  n = 7L
  g = graph_tree(n)
  for (mode in seq_len(3L)) {
    expect_equal(as_adjlist(g, mode)[[1L]], neighbors(g, 1L, mode = mode))
    expect_equal(as_inclist(g, mode)[[1L]], incident(g, 1L, mode = mode))
    expect_equal(lengths(as_adjlist(g, mode)), degree(g, mode = mode))
    expect_equal(lengths(as_inclist(g, mode)), degree(g, mode = mode))
  }
})

test_that("add_edges/add_vertices work", {
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

test_that("delete_edges/delete_vertices work", {
  g = graph_tree(7L)
  g$Vattr$id = g$V
  g$Vattr$name = LETTERS[g$V]
  g$Eattr$id = g$E
  g$Eattr$name = LETTERS[g$E]
  g$delete_edges(c(2, 4))
  expect_length(g$E, 4L)
  expect_length(g$Eattr[[1L]], 4L)
  expect_equal(nrow(g$Eattr), 4L)
  g$delete_vertices(c(2, 4))
  expect_length(g$V, 5L)
  expect_length(g$Vattr[[1L]], 5L)
  expect_equal(nrow(g$Vattr), 5L)
  expect_equal(nrow(g$Eattr), g$ecount)
})
