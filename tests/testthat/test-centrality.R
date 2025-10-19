test_that("centrality functions works", {
  g = graph_tree(7L)
  closeness(g) |>
    expect_type("double") |>
    expect_length(vcount(g))
  harmonic_centrality(g) |>
    expect_type("double") |>
    expect_length(vcount(g))
  pagerank(g) |>
    expect_type("double") |>
    expect_length(vcount(g))
  pagerank(g, reset = as.numeric(V(g))) |>
    expect_type("double") |>
    expect_length(vcount(g))
  constraint(g) |>
    expect_type("double") |>
    expect_length(vcount(g))
  for (mode in seq_len(3L)) {
    deg = degree(g, mode = mode)
    expect_identical(maxdegree(g, mode = mode), max(deg))
    expect_identical(strength(g, mode = mode), as.numeric(deg))
  }
  eigenvector_centrality(g, mode = 3L) |>
    expect_type("double") |>
    expect_length(vcount(g))
  convergence_degree(g) |>
    expect_type("double") |>
    expect_length(ecount(g))
  ha = hub_and_authority_scores(g) |>
    expect_s3_class("data.frame") |>
    expect_named(c("hub", "authority"))
  expect_identical(nrow(ha), vcount(g))

  gw = graph_copy(g)
  Eattr(gw, "weight") = as.double(E(g))
  closeness(gw, weights = TRUE) |>
    expect_type("double") |>
    expect_length(vcount(gw))
  harmonic_centrality(gw, weights = TRUE) |>
    expect_type("double") |>
    expect_length(vcount(gw))
  pagerank(gw, weights = TRUE) |>
    expect_type("double") |>
    expect_length(vcount(gw))
  constraint(gw, weights = TRUE) |>
    expect_type("double") |>
    expect_length(vcount(gw))

  for (mode in seq_len(3L)) {
    exp_str = as_inclist(gw, mode = mode) |>
      lapply(\(edges) sum(Eattr(gw)$weight[edges])) |>
      unlist(recursive = FALSE, use.names = FALSE)
    expect_identical(strength(gw, mode = mode, weights = TRUE), exp_str)
  }

  eigenvector_centrality(gw, mode = 3L, weights = TRUE) |>
    expect_type("double") |>
    expect_length(vcount(gw))
  haw = hub_and_authority_scores(gw, weights = TRUE) |>
    expect_s3_class("data.frame") |>
    expect_named(c("hub", "authority"))
  expect_identical(nrow(haw), vcount(gw))
})

test_that("betweenness() works", {
  g = graph_tree(7L)
  betweenness(g) |>
    expect_identical(c(0, 2, 2, 0, 0, 0, 0)) |>
    expect_identical(suppressWarnings(betweenness(g, weights = TRUE))) |>
    expect_identical(betweenness(g, from = Vsource(g), to = Vsink(g)))
  betweenness(g, cutoff = 1) |>
    expect_identical(c(0, 0, 0, 0, 0, 0, 0))
  expect_warning(betweenness(g, from = Vsource(g), to = Vsink(g), cutoff = 1), "ignored")
  expect_error(betweenness(g, Vsource(g)), "named arguments")

  skip("'weights' ignored in C igraph?")
  w = rep_len(3, ecount(g))
  expect_identical(betweenness(g, weights = w), w * betweenness(g))
})

test_that("edge_betweenness() works", {
  g = graph_tree(7L)
  edge_betweenness(g) |>
    expect_identical(c(3, 3, 2, 2, 2, 2)) |>
    expect_identical(suppressWarnings(edge_betweenness(g, weights = TRUE)))
  edge_betweenness(g, from = Vsource(g), to = Vsink(g)) |>
    expect_identical(c(2, 2, 1, 1, 1, 1))
  edge_betweenness(g, cutoff = 1) |>
    expect_identical(c(1, 1, 1, 1, 1, 1))
  expect_warning(edge_betweenness(g, from = Vsource(g), to = Vsink(g), cutoff = 1), "ignored")
  expect_error(edge_betweenness(g, Vsource(g)), "named arguments")

  suppressWarnings(edge_betweenness_subset(g, to = Vsink(g), weights = TRUE)) |>
    expect_identical(edge_betweenness(g, to = Vsink(g)))
  expect_warning(edge_betweenness_subset(g, to = Vsink(g)), "deprecated")
  expect_error(edge_betweenness_subset(g, Vsource(g)), "named arguments")

  skip("'weights' ignored in C igraph?")
  w = rep_len(3, ecount(g))
  expect_identical(edge_betweenness(g, weights = w), w * edge_betweenness(g))
})
