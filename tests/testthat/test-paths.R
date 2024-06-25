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
  expect_warning(get_shortest_paths(g, 1L, weights = TRUE), "column")
  Eattr(g)$weight = E(g)
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
  expect_warning(get_shortest_paths(g, 1L, weights = TRUE), "column")
  Eattr(g)$weight = E(g)
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
  expect_warning(get_shortest_paths(g, 1L, weights = TRUE), "column")
  Eattr(g)$weight = E(g)
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
  expect_identical(mean_hist(h), average_path_length(g, directed = FALSE))
  h = path_length_hist(g, TRUE)
  expect_length(h, 2L)
  expect_identical(mean_hist(h), average_path_length(g, directed = TRUE))
})
