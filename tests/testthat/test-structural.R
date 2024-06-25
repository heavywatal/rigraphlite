test_that("are_adjacent works", {
  g = graph_tree(7L)
  expect_true(are_adjacent(g, 1L, 2L))
  expect_true(are_adjacent(g, 1L, 3L))
  expect_false(are_adjacent(g, 2L, 3L))
})

test_that("neighborhood_size works", {
  g = graph_tree(7L)
  vids = seq_len(3L)
  expect_length(neighborhood_size(g), vcount(g))
  expect_length(neighborhood_size(g, vids), length(vids))
  expect_identical(neighborhood_size(g, order = 42L, mode = 3L), rep(vcount(g), vcount(g)))
  expect_identical(neighborhood_size(g, order = 42L, mindist = 42L), rep(0L, vcount(g)))
})

test_that("neighborhood works", {
  g = graph_tree(7L)
  vids = seq_len(3L)
  expect_length(neighborhood(g), vcount(g))
  expect_length(neighborhood(g, vids), length(vids))
  expect_identical(lengths(neighborhood(g, mode = 1L)), neighborhood_size(g, mode = 1L))
  expect_identical(lengths(neighborhood(g, mode = 2L)), neighborhood_size(g, mode = 2L))
  expect_identical(lengths(neighborhood(g, mode = 3L)), neighborhood_size(g, mode = 3L))
  expect_identical(lengths(neighborhood(g, order = 42L)), neighborhood_size(g, order = 42L))
  expect_identical(lengths(neighborhood(g, order = 42L, mode = 3L)), rep(vcount(g), vcount(g)))
  expect_identical(neighborhood(g, order = 42L, mindist = 42L), rep(list(integer(0L)), vcount(g)))
})

test_that("subcomponent works", {
  g = graph_tree(7L)
  expect_identical(subcomponent(g, 1, mode = 1L), V(g))
  expect_identical(subcomponent(g, 2, mode = 1L), c(2L, 4L, 5L))
  expect_identical(subcomponent(g, 4, mode = 2L), c(4L, 2L, 1L))
  expect_setequal(subcomponent(g, 2, mode = 3L), V(g))
  expect_length(subcomponents(g, V(g)), vcount(g))
  expect_identical(subcomponents(g, c(2L, 3L), mode = 1L), list(c(2L, 4L, 5L), c(3L, 6L, 7L)))
})

test_that("induced_subgraph works", {
  g = graph_tree(7L)
  vids = seq_len(4L)
  subg = induced_subgraph(g, vids)
  expect_s3_class(subg, "igraph_ptr")
  length(V(subg)) |>
    expect_identical(vcount(subg)) |>
    expect_identical(nrow(Vattr(subg))) |>
    expect_identical(4L)
  length(E(subg)) |>
    expect_identical(ecount(subg)) |>
    expect_identical(nrow(Eattr(subg))) |>
    expect_identical(3L)

  g = graph_tree(7L)
  Vattr(g)$name = LETTERS[V(g)]
  Vattr(g)$weight = as.double(V(g))
  Eattr(g)$name = LETTERS[E(g)]
  Eattr(g)$weight = as.double(E(g))
  vids = seq_len(4L)
  expect_silent({
    subg = induced_subgraph(g, vids)
  })
  length(V(subg)) |>
    expect_identical(vcount(subg)) |>
    expect_identical(nrow(Vattr(subg))) |>
    expect_identical(4L)
  length(E(subg)) |>
    expect_identical(ecount(subg)) |>
    expect_identical(nrow(Eattr(subg))) |>
    expect_identical(3L)
  expect_length(V(subg), length(vids))
  expect_identical(ncol(Vattr(subg)), ncol(Vattr(g)))
  expect_identical(ncol(Eattr(subg)), 0L) # discarded
})
