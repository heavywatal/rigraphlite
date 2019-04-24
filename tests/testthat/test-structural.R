test_that("are_connected works", {
  g = graph_tree(7L)
  expect_true(are_connected(g, 1L, 2L))
  expect_true(are_connected(g, 1L, 3L))
  expect_false(are_connected(g, 2L, 3L))
})

test_that("shortest_paths works", {
  g = graph_tree(7L)
  from = seq_len(3L)
  to = seq_len(3L) + 4L
  expect_is(shortest_paths(g), "matrix")
  expect_equal(dim(shortest_paths(g)), c(g$vcount, g$vcount))
  expect_equal(dim(shortest_paths(g, from)), c(length(from), length(from)))
  expect_equal(dim(shortest_paths(g, from, to)), c(length(from), length(to)))
  expect_is(shortest_paths(g, weights = g$E), "matrix")
  expect_error(shortest_paths(g, weights = TRUE), "hasName")
  g$Eattr["weight"] = g$E
  expect_is(shortest_paths(g, weights = TRUE), "matrix")
})

test_that("get_shortest_paths works", {
  g = graph_tree(7L)
  to = seq_len(3L)
  expect_is(get_shortest_paths(g, 1L), "list")
  expect_length(get_shortest_paths(g, 1L), g$vcount)
  expect_length(get_shortest_paths(g, 1L, to), length(to))
  expect_equal(get_shortest_paths(g, 1L, to), list(1, c(1, 2), c(1, 3)))
  expect_error(
    get_shortest_paths(g, c(1L, 2L), to),
    "Expecting a single value"
  )
  expect_warning(
    get_shortest_paths(g, 1L, mode = 2L),
    "Couldn't reach some vertices"
  )
  expect_error(get_shortest_paths(g, 1L, weights = TRUE), "hasName")
  g$Eattr["weight"] = g$E
  expect_is(get_shortest_paths(g, 1L, weights = TRUE), "list")
})

test_that("get_all_shortest_paths works", {
  g = graph_tree(7L)
  to = seq_len(3L)
  expect_is(get_all_shortest_paths(g, 1L), "list")
  expect_length(get_all_shortest_paths(g, 1L), g$vcount)
  expect_length(get_all_shortest_paths(g, 1L, to), length(to))
  expect_equal(get_all_shortest_paths(g, 1L, to), list(1, c(1, 2), c(1, 3)))
  expect_error(
    get_all_shortest_paths(g, c(1L, 2L), to),
    "Expecting a single value"
  )
  expect_length(get_all_shortest_paths(g, 1L, mode = 2L), 1L)
  expect_error(get_all_shortest_paths(g, 1L, weights = TRUE), "hasName")
  g$Eattr["weight"] = g$E
  expect_is(get_all_shortest_paths(g, 1L, weights = TRUE), "list")
})

test_that("get_all_simple_paths works", {
  g = graph_create(c(1, 2, 2, 3, 1, 3))
  expect_equal(get_all_simple_paths(g, 1L, 3L), list(c(1, 2, 3), c(1, 3)))
})

test_that("path_length_hist and average_path_length works", {
  mean_hist = function(x) sum(x * seq_along(x)) / sum(x)
  g = graph_tree(7L)
  h = path_length_hist(g, FALSE)
  expect_length(h, 4L)
  expect_equal(mean_hist(h), average_path_length(g, FALSE))
  h = path_length_hist(g, TRUE)
  expect_length(h, 2L)
  expect_equal(mean_hist(h), average_path_length(g, TRUE))
})

test_that("neighborhood_size works", {
  g = graph_tree(7L)
  vids = seq_len(3L)
  expect_length(neighborhood_size(g), g$vcount)
  expect_length(neighborhood_size(g, vids), length(vids))
  expect_equal(neighborhood_size(g, order = 42L, mode = 3L), rep(g$vcount, g$vcount))
  expect_equal(neighborhood_size(g, order = 42L, mindist = 42L), rep(0, g$vcount))
})

test_that("neighborhood works", {
  g = graph_tree(7L)
  vids = seq_len(3L)
  expect_length(neighborhood(g), g$vcount)
  expect_length(neighborhood(g, vids), length(vids))
  expect_equal(lengths(neighborhood(g, mode = 1L)), neighborhood_size(g, mode = 1L))
  expect_equal(lengths(neighborhood(g, mode = 2L)), neighborhood_size(g, mode = 2L))
  expect_equal(lengths(neighborhood(g, mode = 3L)), neighborhood_size(g, mode = 3L))
  expect_equal(lengths(neighborhood(g, order = 42L)), neighborhood_size(g, order = 42L))
  expect_equal(lengths(neighborhood(g, order = 42L, mode = 3L)), rep(g$vcount, g$vcount))
  expect_equal(neighborhood(g, order = 42L, mindist = 42L), rep(list(numeric(0L)), g$vcount))
})

test_that("subcomponent works", {
  g = graph_tree(7L)
  expect_equal(subcomponent(g, 1, mode = 1L), g$V)
  expect_equal(subcomponent(g, 2, mode = 1L), c(2, 4, 5))
  expect_equal(subcomponent(g, 4, mode = 2L), c(4, 2, 1))
  expect_setequal(subcomponent(g, 2, mode = 3L), g$V)
  expect_length(subcomponents(g, g$V), g$vcount)
  expect_equal(subcomponents(g, c(2, 3), mode = 1L), list(c(2, 4, 5), c(3, 6, 7)))
})

test_that("induced_subgraph works", {
  el = matrix(seq_len(8L), ncol = 2L)
  g = graph_from_symbolic_edgelist(el)
  g$Eattr$name = as.character(g$E)
  vids = seq_len(4L)
  expect_warning({subg = induced_subgraph(g, vids)})
  expect_s4_class(subg, "Rcpp_IGraph")
  expect_length(subg$V, length(vids))
  expect_equal(nrow(subg$Vattr), subg$vcount)
  expect_equal(nrow(subg$Eattr), subg$ecount)
  expect_equal(ncol(subg$Vattr), ncol(g$Vattr))
  expect_equal(ncol(subg$Eattr), ncol(g$Eattr))
})
