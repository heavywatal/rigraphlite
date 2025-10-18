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

  expect_identical(connected_components(g, connectedness = 1L), rep(1L, vcount(g)))
  expect_true(is_connected(g))
  expect_identical(count_reachable(g, mode = 1L), c(7L, 3L, 3L, 1L, 1L, 1L, 1L))
  expect_identical(count_reachable(g, mode = 2L), c(1L, 2L, 2L, 3L, 3L, 3L, 3L))
  expect_identical(count_reachable(g, mode = 3L), rep(7L, vcount(g)))
  expect_s3_class(transitive_closure(g), "igraph_ptr")
  expect_setequal(articulation_points(g), c(1L, 2L, 3L))
  expect_setequal(bridges(g), E(g))
  expect_false(is_biconnected(g))
})

test_that("non-simple graph functions work", {
  g = graph_tree(5L)
  expect_true(is_simple(g))
  expect_false(has_loop(g))
  expect_identical(count_loops(g), 0L)
  expect_false(has_multiple(g))
  expect_identical(count_multiple(g), rep(1L, ecount(g)))
  g = add_edges(g, c(1L, 1L)) # add a loop
  g = add_edges(g, c(1L, 2L)) # add a multiple edge
  g = add_edges(g, c(2L, 1L)) # not a multiple edge in directed graph
  expect_false(is_simple(g))
  expect_true(has_loop(g))
  expect_identical(count_loops(g), 1L)
  expect_true(has_multiple(g))
  expect_identical(count_multiple(g), c(2L, 1L, 1L, 1L, 1L, 2L, 1L))
})
