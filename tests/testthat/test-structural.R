test_that("are_adjacent works", {
  g = graph_tree(7L)
  expect_true(are_adjacent(g, 1L, 2L))
  expect_true(are_adjacent(g, 1L, 3L))
  expect_false(are_adjacent(g, 2L, 3L))
})

test_that("distances works", {
  n = 7L
  g = graph_tree(n)
  d = distances(g) |>
    expect_type("double") |>
    expect_length(n**2L)
  expect_true(is.matrix(d))
  expect_identical(dim(d), c(vcount(g), vcount(g)))
  from = seq_len(3L)
  to = seq_len(3L) + 4L
  expect_identical(dim(distances(g, from)), c(length(from), length(from)))
  expect_identical(dim(distances(g, from, to)), c(length(from), length(to)))
  dw = distances(g, weights = E(g)) |>
    expect_type("double") |>
    expect_length(n**2L)
  expect_true(is.matrix(dw))
  expect_identical(dim(dw), c(vcount(g), vcount(g)))
  expect_error(distances(g, weights = TRUE), "hasName")
  Eattr(g, "weight") = E(g)
  expect_identical(distances(g, weights = TRUE), dw)
})

test_that("get_shortest_paths works", {
  g = graph_tree(7L)
  to = seq_len(3L)
  get_shortest_paths(g, 1L) |>
    expect_type("list") |>
    expect_length(vcount(g))
  get_shortest_paths(g, 1L, to) |>
    expect_length(length(to)) |>
    expect_identical(list(1L, c(1L, 2L), c(1L, 3L)))
  expect_error(
    get_shortest_paths(g, c(1L, 2L), to),
    "Expected single integer value"
  )
  expect_warning(
    get_shortest_paths(g, 1L, mode = 2L),
    "Couldn't reach some vertices"
  )
  expect_error(get_shortest_paths(g, 1L, weights = TRUE), "hasName")
  Eattr(g, "weight") = E(g)
  expect_type(get_shortest_paths(g, 1L, weights = TRUE), "list")
})

test_that("get_all_shortest_paths works", {
  g = graph_tree(7L)
  to = seq_len(3L)
  get_all_shortest_paths(g, 1L) |>
    expect_type("list") |>
    expect_length(vcount(g))
  get_all_shortest_paths(g, 1L, to) |>
    expect_length(length(to)) |>
    expect_identical(list(1L, c(1L, 2L), c(1L, 3L)))
  expect_error(
    get_all_shortest_paths(g, c(1L, 2L), to),
    "Expected single integer value"
  )
  expect_length(get_all_shortest_paths(g, 1L, mode = 2L), 1L)
  expect_error(get_all_shortest_paths(g, 1L, weights = TRUE), "hasName")
  Eattr(g, "weight") = E(g)
  expect_type(get_all_shortest_paths(g, 1L, weights = TRUE), "list")
})

test_that("get_all_simple_paths works", {
  g = graph_create(c(1L, 2L, 2L, 3L, 1L, 3L))
  expect_identical(get_all_simple_paths(g, 1L, 3L), list(c(1L, 2L, 3L), c(1L, 3L)))
})

test_that("path_length_hist and average_path_length works", {
  mean_hist = function(x) sum(x * seq_along(x)) / sum(x)
  g = graph_tree(7L)
  h = path_length_hist(g, FALSE)
  expect_length(h, 4L)
  expect_identical(mean_hist(h), average_path_length(g, FALSE))
  h = path_length_hist(g, TRUE)
  expect_length(h, 2L)
  expect_identical(mean_hist(h), average_path_length(g, TRUE))
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
  el = matrix(seq_len(8L), ncol = 2L)
  g = graph_from_symbolic_edgelist(el)
  Eattr(g, "name") = as.character(E(g))
  vids = seq_len(4L)
  expect_silent({
    subg = induced_subgraph(g, vids)
  })
  expect_s3_class(subg, "Rcpp_IGraph")
  expect_length(V(subg), length(vids))
  expect_identical(nrow(Vattr(subg)), vcount(subg))
  expect_identical(nrow(Eattr(subg)), ecount(subg))
  expect_identical(ncol(Vattr(subg)), ncol(Vattr(g)))
  expect_identical(ncol(Eattr(subg)), 0L) # discarded
})
