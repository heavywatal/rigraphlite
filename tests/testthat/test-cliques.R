test_that("cliques work", {
  full = graph_full(5L)
  expect_true(is_complete(full))
  expect_true(is_clique(full))
  g = graph_circulant(6L, c(1L, 2L))
  expect_false(is_complete(g))
  expect_true(is_clique(g, c(1L, 2L, 3L)))
  cn = expect_identical(clique_number(g), 3L)
  h = expect_identical(clique_size_hist(g), c(6L, 12L, 8L))
  expect_length(cliques(g), sum(h))
  expect_length(largest_cliques(g), h[cn])
  mcc = expect_identical(maximal_cliques_count(g), h[cn])
  expect_identical(maximal_cliques_hist(g), c(0L, 0L, mcc))
  expect_length(maximal_cliques(g), mcc)
})

test_that("independent vertex sets work", {
  full = graph_full(5L)
  tree = graph_tree(7L, mode = 2L)
  expect_false(is_independent_vertex_set(full))
  expect_true(is_independent_vertex_set(tree, seq.int(4L, 7L)))
  expect_length(independent_vertex_sets(full, min_size = 2L), 0L)
  ivs = independent_vertex_sets(tree, min_size = 2L)
  mivs = maximal_independent_vertex_sets(tree) |>
    expect_in(ivs)
  livs = largest_independent_vertex_sets(tree) |>
    expect_in(mivs) |>
    expect_identical(list(c(1L, 4L, 5L, 6L, 7L)))
  expect_identical(independence_number(tree), lengths(livs))
})
