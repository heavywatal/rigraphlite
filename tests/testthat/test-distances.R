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
  expect_identical(dim(distances(g, from = from)), c(length(from), length(from)))
  expect_identical(dim(distances(g, from = from, to = to)), c(length(from), length(to)))
  dw = distances(g, weights = E(g)) |>
    expect_type("double") |>
    expect_length(n**2L)
  expect_true(is.matrix(dw))
  expect_identical(dim(dw), c(vcount(g), vcount(g)))
  suppressWarnings(distances(g, weights = TRUE)) |>
    expect_identical(d)
  Eattr(g)$weight = E(g)
  expect_identical(distances(g, weights = TRUE), dw)
  distances(g, cutoff = 3) |>
    is.infinite() |>
    sum() |>
    expect_identical(8L)
  expect_error(distances(g, from, to), "named arguments")
})

test_that("path_length_hist and average_path_length works", {
  mean_hist = function(x) sum(x * seq_along(x)) / sum(x)
  g = graph_tree(7L)
  h = path_length_hist(g, FALSE)
  expect_length(h, 4L)
  expect_identical(mean_hist(h), average_path_length(g, directed = FALSE))
  h = path_length_hist(g, TRUE)
  expect_length(h, 2L)
  average_path_length(g, directed = TRUE) |>
    expect_identical(mean_hist(h)) |>
    expect_identical(suppressWarnings(average_path_length(g, weights = TRUE)))
  expect_error(average_path_length(g, TRUE), "named arguments")
})

test_that("diameter, radius, and girth work", {
  g = graph_tree(7L)

  ecc1 = eccentricity(g, mode = 1L) |>
    expect_identical(c(2, 1, 1, 0, 0, 0, 0))
  ecc2 = eccentricity(g, mode = 2L) |>
    expect_identical(c(0, 1, 1, 2, 2, 2, 2))
  ecc3 = eccentricity(g, mode = 3L) |>
    expect_identical(c(2, 3, 3, 4, 4, 4, 4))

  expect_identical(diameter(g, directed = TRUE), max(ecc1))
  expect_identical(diameter(g, directed = FALSE), max(ecc3))
  expect_identical(diameter(g, directed = TRUE, unconn = FALSE), Inf)
  expect_identical(suppressWarnings(diameter(g, weights = TRUE)), 2)
  expect_identical(radius(g, mode = 1L), min(ecc1))
  expect_identical(radius(g, mode = 2L), min(ecc2))
  expect_identical(radius(g, mode = 3L), min(ecc3))
  expect_identical(girth(g), Inf)

  h = add_edges(g, c(2L, 3L))
  expect_identical(girth(h), 3) # directed graphs are treated as undirected

  Eattr(g)$weight = E(g)
  diameter(g, weights = TRUE) |>
    expect_identical(max(eccentricity(g, weights = TRUE, mode = 1L)))
  diameter(g, weights = TRUE, directed = FALSE) |>
    expect_identical(max(eccentricity(g, weights = TRUE, mode = 3L)))
  for (mode in seq_len(3L)) {
    radius(g, weights = TRUE, mode = mode) |>
      expect_identical(min(eccentricity(g, weights = TRUE, mode = mode)))
  }
})
