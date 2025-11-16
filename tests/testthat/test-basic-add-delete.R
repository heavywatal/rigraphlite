graph_tree_test = function(n = 7L) {
  g = graph_tree(7L)
  Vattr(g)$id = V(g)
  Vattr(g)$name = LETTERS[V(g)]
  Vattr(g)$weight = as.double(V(g))
  Vattr(g)$ls = as.list(V(g))
  Vattr(g)$bool = as.logical(V(g))
  Vattr(g)$raw = as.raw(V(g))
  Eattr(g)$id = E(g)
  Eattr(g)$name = LETTERS[E(g)]
  Eattr(g)$weight = as.double(E(g))
  g
}

test_that("add_edges/add_vertices work", {
  g = graph_empty()
  add_edges(g, c(1L, 2L))
  add_edges(g, c(3L, 4L))
  add_vertices(g, 2L)
  expect_identical(E(g), seq_len(2L))
  expect_identical(V(g), seq_len(6L))
  expect_shape(Eattr(g), dim = c(ecount(g), 0L))
  expect_shape(Vattr(g), dim = c(vcount(g), 0L))

  h = graph_copy(g)
  expect_identical(as.matrix(h), as.matrix(g))
  add_edges(h, c(5L, 6L))
  expect_false(identical(as.matrix(h), as.matrix(g)))

  g = graph_tree_test(7L)
  add_edges(g, c(6L, 7L))
  add_edges(g, c(8L, 9L))
  expect_identical(E(g), seq_len(8L))
  expect_shape(Eattr(g), dim = c(ecount(g), 3L))
  expect_identical(V(g), seq_len(9L))
  expect_shape(Vattr(g), dim = c(vcount(g), 6L))
  Vattr(g)$invalid = as.list(V(g))
  Eattr(g)$invalid = as.list(E(g))
  expect_error(add_edges(g, c(10, 11)), "Invalid input type")
})

test_that("delete_edges/delete_vertices work", {
  g = graph_tree(7L)
  delete_edges(g, c(2L, 4L))
  expect_identical(E(g), seq_len(4L))
  expect_shape(Eattr(g), dim = c(ecount(g), 0L))
  delete_vertices(g, c(2L, 4L))
  expect_identical(V(g), seq_len(5L))
  expect_shape(Vattr(g), dim = c(vcount(g), 0L))

  g = graph_tree_test(7L)
  delete_edges(g, c(4L, 2L))
  expect_identical(E(g), seq_len(4L))
  expect_shape(Eattr(g), dim = c(ecount(g), 3L))
  expect_identical(Eattr(g)$name, c("A", "C", "E", "F"))
  expect_identical(Eattr(g)$weight, c(1, 3, 5, 6))
  delete_vertices(g, c(4L, 2L))
  expect_identical(V(g), seq_len(5L))
  expect_shape(Vattr(g), dim = c(vcount(g), 6L))
  expect_identical(Vnames(g), c("A", "C", "E", "F", "G"))
  expect_identical(Vattr(g)$weight, c(1, 3, 5, 6, 7))

  Vattr(g)$invalid = as.list(V(g))
  Eattr(g)$invalid = as.list(E(g))
  expect_error(delete_edges(g, c(2, 5)), "Invalid input type")
})
