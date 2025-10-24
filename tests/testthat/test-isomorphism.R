test_that("permutation and isomophic tests work", {
  g1 = graph_create(c(1L, 2L, 1L, 3L), directed = FALSE)
  g2 = graph_create(c(3L, 2L, 3L, 1L), directed = FALSE)
  g3 = graph_create(c(3L, 1L, 3L, 2L), directed = FALSE)
  expect_true(isomorphic(g1, g2))
  expect_true(isomorphic(g2, g3))
  expect_false(is_same_graph(g1, g2))
  expect_true(is_same_graph(g2, g3))

  perm1 = canonical_permutation(g1) |>
    expect_type("integer") |>
    expect_length(3L)
  g1can = permutate_vertices(g1, perm1)
  g2can = permutate_vertices(g2, canonical_permutation(g2))
  expect_true(is_same_graph(g1can, g2can))
  # Note that edge order may differ

  g4 = graph_create(c(1L, 2L, 1L, 3L, 3L, 4L), directed = FALSE)
  expect_true(subisomorphic(g4, g1))
  expect_false(subisomorphic(g1, g4))
})
