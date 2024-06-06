test_that("basic queries work", {
  g = graph_tree(7L)
  expect_identical(vcount(g), 7L)
  expect_identical(ecount(g), 6L)
  expect_identical(edge(g, 1L), c(1L, 2L))
  expect_true(is_directed(g))
})

test_that("neighbors works", {
  g = graph_tree(7L)
  expect_error(neighbors(g, 0L), "not in the graph")
  expect_identical(neighbors(g, 1L, mode = 1L), c(2L, 3L))
  expect_identical(neighbors(g, 1L, mode = 2L), integer(0L))
  expect_identical(neighbors(g, 1L, mode = 3L), c(2L, 3L))
})

test_that("incident works", {
  g = graph_tree(7L)
  expect_error(incident(g, 0L), "not in the graph")
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
  Vattr(g, "id") = V(g)
  Vattr(g, "name") = LETTERS[V(g)]
  Vattr(g, "weight") = as.double(V(g))
  Eattr(g, "id") = E(g)
  Eattr(g, "name") = LETTERS[E(g)]
  Eattr(g, "weight") = as.double(E(g))
  add_edges(g, c(6L, 7L, 8L, 9L))
  expect_length(E(g), 8L)
  expect_length(Eattr(g)[[1L]], 8L)
  expect_identical(nrow(Eattr(g)), 8L)
  expect_length(V(g), 9L)
  expect_length(Vattr(g)[[1L]], 9L)
  expect_identical(nrow(Vattr(g)), 9L)
  Vattr(g, "invalid") = as.list(V(g))
  Eattr(g, "weight") = as.list(E(g))
  expect_error(add_edges(g, c(10, 11)), "Invalid type")
})

test_that("delete_edges/delete_vertices work", {
  g = graph_tree(7L)
  Vattr(g, "id") = V(g)
  Vattr(g, "name") = LETTERS[V(g)]
  Vattr(g, "weight") = as.double(V(g))
  Eattr(g, "id") = E(g)
  Eattr(g, "name") = LETTERS[E(g)]
  Eattr(g, "weight") = as.double(E(g))
  delete_edges(g, c(2L, 4L))
  expect_length(E(g), 4L)
  expect_length(Eattr(g)[[1L]], 4L)
  expect_identical(nrow(Eattr(g)), 4L)
  delete_vertices(g, c(2L, 4L))
  expect_length(V(g), 5L)
  expect_length(Vattr(g)[[1L]], 5L)
  expect_identical(nrow(Vattr(g)), 5L)
  expect_identical(nrow(Eattr(g)), ecount(g))
  Vattr(g, "invalid") = as.list(V(g))
  Eattr(g, "weight") = as.list(E(g))
  expect_error(delete_edges(g, c(2, 5)), "Invalid type")
})
