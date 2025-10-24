test_that("erdos-renyi models work", {
  n = 7L
  m = 7L
  p = 0.5
  gnm = erdos_renyi_game_gnm(n, m)
  expect_identical(vcount(gnm), n)
  expect_identical(ecount(gnm), m)
  gnp = erdos_renyi_game_gnp(n, p)
  expect_identical(vcount(gnp), n)
})

test_that("degree-constrained models works", {
  out_deg = seq_len(4L)
  in_deg = rev(out_deg)
  g = degree_sequence_game(out_deg)
  expect_identical(degree(g), out_deg)
  g_d = degree_sequence_game(out_deg, in_deg)
  expect_identical(degree(g_d, mode = 1L), out_deg)
  expect_identical(degree(g_d, mode = 2L), in_deg)

  n = 7L
  k = 2L
  g_k = k_regular_game(n, k)
  expect_identical(degree(g_k), rep(k, n))
  g_kd = k_regular_game(n, k, directed = TRUE)
  expect_identical(degree(g_kd, mode = 1L), rep(k, n))
  expect_identical(degree(g_kd, mode = 2L), rep(k, n))

  g_rw = rewire(g_k, 9L)
  expect_identical(degree(g_rw), degree(g_k))
  expect_false(identical(as.matrix(g_rw), as.matrix(g_k)))
})

test_that("edge rewiring models work", {
  dim = 1L
  size = 20L
  nei = 2L
  prob = 0.1
  g_ws0 = watts_strogatz_game(dim, size, nei, 0)
  expect_true(is_same_graph(g_ws0, graph_circulant(size, c(1L, 2L))))
  expect_identical(vcount(g_ws0), as.integer(size**dim))
  expect_identical(degree(g_ws0), rep(4L, vcount(g_ws0)))

  g_small_world = watts_strogatz_game(dim, size, nei, prob)
  expect_identical(vcount(g_small_world), vcount(g_ws0))
  expect_identical(sum(degree(g_small_world)), sum(degree(g_ws0)))

  g_rewired = rewire_edges(g_ws0, prob)
  expect_identical(vcount(g_rewired), vcount(g_ws0))
  expect_identical(sum(degree(g_rewired)), sum(degree(g_ws0)))
  expect_false(identical(as.matrix(g_rewired), as.matrix(g_ws0)))
})
