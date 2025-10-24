test_that("basic queries work", {
  g = graph_tree(7L)
  expect_identical(vcount(g), 7L)
  expect_identical(ecount(g), 6L)
  expect_identical(edge(g, 1L), c(1L, 2L))
  eids = c(1L, 3L, 5L)
  pairs = c(1L, 2L, 2L, 4L, 3L, 6L)
  expect_identical(edges(g, eids), pairs)
  expect_identical(get_eids(g, pairs), eids)
  expect_error(get_eids(g, c(7L, 8L)), "invalid vertex ID")
  add_vertices(g, 1L)
  expect_error(get_eids(g, c(7L, 8L)), "no such edge")
  expect_identical(get_eids(g, c(7L, 8L), error = FALSE), 0L)
  add_edges(g, c(1L, 2L))
  expect_length(get_eids(g, c(1L, 2L)), 1L)
  expect_setequal(get_all_eids_between(g, 1L, 2L), c(1L, 7L))
  expect_true(is_directed(g))
})

test_that("neighbors works", {
  g = graph_tree(7L)
  expect_error(neighbors(g, 0L), "not in the graph")
  expect_identical(neighbors(g, 1L, mode = 1L), c(2L, 3L))
  expect_identical(neighbors(g, 1L, mode = 2L), integer(0L))
  expect_identical(neighbors(g, 1L, mode = 3L), c(2L, 3L))
})

test_that("incident works", {
  g = graph_tree(7L)
  expect_error(incident(g, 0L), "not in the graph")
  expect_identical(incident(g, 1L, mode = 1L), c(1L, 2L))
  expect_identical(incident(g, 1L, mode = 2L), integer(0L))
  expect_identical(incident(g, 1L, mode = 3L), c(1L, 2L))
})

test_that("degree works", {
  g = graph_tree(7L)
  vids = seq_len(3L)
  expect_length(degree(g), vcount(g))
  expect_length(degree(g, vids), length(vids))
  expect_identical(degree(g, mode = 1L), c(2L, 2L, 2L, 0L, 0L, 0L, 0L))
  expect_identical(degree(g, mode = 2L), c(0L, 1L, 1L, 1L, 1L, 1L, 1L))
  expect_identical(degree(g, mode = 3L), c(2L, 3L, 3L, 1L, 1L, 1L, 1L))
  expect_identical(degree(g, Vsink(g), mode = 1L), c(0L, 0L, 0L, 0L))
  expect_identical(degree(g, Vsource(g), mode = 2L), 0L)
})

test_that("as_adjlist and as_inclist work", {
  n = 7L
  g = graph_tree(n)
  for (mode in seq_len(3L)) {
    expect_identical(as_adjlist(g, mode)[[1L]], neighbors(g, 1L, mode = mode))
    expect_identical(as_inclist(g, mode)[[1L]], incident(g, 1L, mode = mode))
    expect_identical(lengths(as_adjlist(g, mode)), degree(g, mode = mode))
    expect_identical(lengths(as_inclist(g, mode)), degree(g, mode = mode))
  }
})

test_that("macros work", {
  expect_identical(VCOUNT_MAX(), 2147483646L)
  expect_identical(ECOUNT_MAX(), VCOUNT_MAX() %/% 2L)
  expect_identical(UNLIMITED(), -1L)
  expect_identical(IGRAPH_VCOUNT_MAX, VCOUNT_MAX())
  expect_identical(IGRAPH_ECOUNT_MAX, ECOUNT_MAX())
  expect_identical(IGRAPH_UNLIMITED, UNLIMITED())
  expect_identical(expand_path_to_pairs(seq_len(4L)), c(1L, 2L, 2L, 3L, 3L, 4L))
})
