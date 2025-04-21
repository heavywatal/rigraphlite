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
  g = graph_tree(7L)
  add_edges(g, c(6L, 7L))
  add_edges(g, c(8L, 9L))
  length(E(g)) |>
    expect_identical(ecount(g)) |>
    expect_identical(nrow(Eattr(g))) |>
    expect_identical(8L)
  length(V(g)) |>
    expect_identical(vcount(g)) |>
    expect_identical(nrow(Vattr(g))) |>
    expect_identical(9L)

  g = graph_tree_test(7L)
  add_edges(g, c(6L, 7L))
  add_edges(g, c(8L, 9L))
  length(E(g)) |>
    expect_identical(ecount(g)) |>
    expect_identical(nrow(Eattr(g))) |>
    expect_identical(8L)
  length(V(g)) |>
    expect_identical(vcount(g)) |>
    expect_identical(nrow(Vattr(g))) |>
    expect_identical(9L)
  expect_identical(ncol(Vattr(g)), 6L)
  expect_identical(ncol(Eattr(g)), 3L)
  Vattr(g)$invalid = as.list(V(g))
  Eattr(g)$invalid = as.list(E(g))
  expect_error(add_edges(g, c(10, 11)), "Invalid input type")
})

test_that("delete_edges/delete_vertices work", {
  g = graph_tree(7L)
  delete_edges(g, c(2L, 4L))
  length(E(g)) |>
    expect_identical(ecount(g)) |>
    expect_identical(nrow(Eattr(g))) |>
    expect_identical(4L)
  delete_vertices(g, c(2L, 4L))
  length(V(g)) |>
    expect_identical(vcount(g)) |>
    expect_identical(nrow(Vattr(g))) |>
    expect_identical(5L)

  g = graph_tree_test(7L)
  delete_edges(g, c(4L, 2L))
  length(E(g)) |>
    expect_identical(ecount(g)) |>
    expect_identical(nrow(Eattr(g))) |>
    expect_identical(4L)
  expect_identical(nrow(Eattr(g)), ecount(g))
  expect_identical(Eattr(g)$name, c("A", "C", "E", "F"))
  expect_identical(Eattr(g)$weight, c(1, 3, 5, 6))
  delete_vertices(g, c(4L, 2L))
  length(V(g)) |>
    expect_identical(vcount(g)) |>
    expect_identical(nrow(Vattr(g))) |>
    expect_identical(5L)
  expect_identical(Vnames(g), c("A", "C", "E", "F", "G"))
  expect_identical(Vattr(g)$weight, c(1, 3, 5, 6, 7))
  expect_identical(ncol(Vattr(g)), 6L)
  expect_identical(ncol(Eattr(g)), 3L)

  Vattr(g)$invalid = as.list(V(g))
  Eattr(g)$invalid = as.list(E(g))
  expect_error(delete_edges(g, c(2, 5)), "Invalid input type")
})
