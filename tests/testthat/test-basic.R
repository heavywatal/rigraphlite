test_that("basic queries work", {
  g = graph_tree(7L)
  expect_identical(vcount(g), 7L)
  expect_identical(ecount(g), 6L)
  expect_identical(edge(g, 1L), c(1L, 2L))
  expect_true(is_directed(g))
})

test_that("neighbors works", {
  g = graph_tree(7L)
  expect_error(neighbors(g, 0L))
  expect_identical(neighbors(g, 1L, mode = 1L), c(2L, 3L))
  expect_identical(neighbors(g, 1L, mode = 2L), integer(0L))
  expect_identical(neighbors(g, 1L, mode = 3L), c(2L, 3L))
})

test_that("incident works", {
  g = graph_tree(7L)
  expect_error(incident(g, 0L))
  expect_identical(incident(g, 1L, mode = 1L), c(1L, 2L))
  expect_identical(incident(g, 1L, mode = 2L), integer(0L))
  expect_identical(incident(g, 1L, mode = 3L), c(1L, 2L))
})

test_that("degree works", {
  g = graph_tree(7L)
  vids = seq_len(3L)
  expect_length(degree(g), vcount(g))
  expect_length(degree(g, vids), length(vids))
  expect_identical(degree(g, mode = 1L), c(2L, 2L, 2L, 0L, 0L, 0L, 0L))
  expect_identical(degree(g, mode = 2L), c(0L, 1L, 1L, 1L, 1L, 1L, 1L))
  expect_identical(degree(g, mode = 3L), c(2L, 3L, 3L, 1L, 1L, 1L, 1L))
  expect_identical(degree(g, Vsink(g), mode = 1L), c(0L, 0L, 0L, 0L))
  expect_identical(degree(g, Vsource(g), mode = 2L), 0L)
})

test_that("as_adjlist and as_inclist work", {
  n = 7L
  g = graph_tree(n)
  for (mode in seq_len(3L)) {
    expect_identical(as_adjlist(g, mode)[[1L]], neighbors(g, 1L, mode = mode))
    expect_identical(as_inclist(g, mode)[[1L]], incident(g, 1L, mode = mode))
    expect_identical(lengths(as_adjlist(g, mode)), degree(g, mode = mode))
    expect_identical(lengths(as_inclist(g, mode)), degree(g, mode = mode))
  }
})

test_that("add_edges/add_vertices work", {
  g = graph_tree(7L)
  g$Vattr$id = V(g)
  g$Vattr$name = LETTERS[V(g)]
  g$Vattr$weight = as.double(V(g))
  g$Eattr$id = E(g)
  g$Eattr$name = LETTERS[E(g)]
  g$Eattr$weight = as.double(E(g))
  g$add_edges(c(6, 7, 8, 9))
  expect_length(E(g), 8L)
  expect_length(g$Eattr[[1L]], 8L)
  expect_identical(nrow(g$Eattr), 8L)
  expect_length(V(g), 9L)
  expect_length(g$Vattr[[1L]], 9L)
  expect_identical(nrow(g$Vattr), 9L)
  g$Vattr$invalid = as.list(V(g))
  g$Eattr$weight = as.list(E(g))
  expect_error(g$add_edges(c(10, 11)), "Invalid type")
})

test_that("delete_edges/delete_vertices work", {
  g = graph_tree(7L)
  g$Vattr$id = V(g)
  g$Vattr$name = LETTERS[V(g)]
  g$Vattr$weight = as.double(V(g))
  g$Eattr$id = E(g)
  g$Eattr$name = LETTERS[E(g)]
  g$Eattr$weight = as.double(E(g))
  g$delete_edges(c(2, 4))
  expect_length(E(g), 4L)
  expect_length(g$Eattr[[1L]], 4L)
  expect_identical(nrow(g$Eattr), 4L)
  g$delete_vertices(c(2, 4))
  expect_length(V(g), 5L)
  expect_length(g$Vattr[[1L]], 5L)
  expect_identical(nrow(g$Vattr), 5L)
  expect_identical(nrow(g$Eattr), ecount(g))
  g$Vattr$invalid = as.list(V(g))
  g$Eattr$weight = as.list(E(g))
  expect_error(g$delete_edges(c(2, 5)), "Invalid type")
})
