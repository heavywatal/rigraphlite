test_that("get_shortest_paths works", {
  g = graph_tree(7L)
  to = seq_len(3L)
  d = get_shortest_paths(g, from = 1L) |>
    expect_type("list") |>
    expect_length(vcount(g))
  dw = get_shortest_paths(g, weights = E(g), from = 1L) |>
    expect_type("list") |>
    expect_length(vcount(g))
  get_shortest_paths(g, from = 1L, to = to) |>
    expect_length(length(to)) |>
    expect_identical(list(1L, c(1L, 2L), c(1L, 3L)))
  expect_error(
    get_shortest_paths(g, from = c(1L, 2L), to = to),
    "Expected single integer value"
  )
  expect_warning(
    get_shortest_paths(g, from = 1L, mode = 2L),
    "Couldn't reach some vertices"
  )
  suppressWarnings(get_shortest_paths(g, weights = TRUE, from = 1L)) |>
    expect_identical(d)
  Eattr(g)$weight = E(g)
  expect_identical(get_shortest_paths(g, weights = TRUE, from = 1L), dw)
  expect_error(get_shortest_paths(g, from, to), "named arguments")
})

test_that("get_all_shortest_paths works", {
  g = graph_tree(7L)
  to = seq_len(3L)
  d = get_all_shortest_paths(g, from = 1L) |>
    expect_type("list") |>
    expect_length(vcount(g))
  dw = get_all_shortest_paths(g, weights = E(g), from = 1L) |>
    expect_type("list") |>
    expect_length(vcount(g))
  get_all_shortest_paths(g, from = 1L, to = to) |>
    expect_length(length(to)) |>
    expect_identical(list(1L, c(1L, 2L), c(1L, 3L)))
  expect_error(
    get_all_shortest_paths(g, from = c(1L, 2L), to = to),
    "Expected single integer value"
  )
  expect_length(get_all_shortest_paths(g, from = 1L, mode = 2L), 1L)
  suppressWarnings(get_all_shortest_paths(g, weights = TRUE, from = 1L)) |>
    expect_identical(d)
  Eattr(g)$weight = E(g)
  expect_identical(get_all_shortest_paths(g, weights = TRUE, from = 1L), dw)
  expect_error(get_all_shortest_paths(g, from, to), "named arguments")
})

test_that("get_all_simple_paths works", {
  g = graph_create(c(1L, 2L, 2L, 3L, 1L, 3L))
  expect_identical(get_all_simple_paths(g, 1L, 3L), list(c(1L, 2L, 3L), c(1L, 3L)))
})
