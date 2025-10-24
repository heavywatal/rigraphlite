test_that("acyclic tests work", {
  dag = graph_tree(5L)
  tree = graph_tree(5L, mode = 2L)
  ring = graph_ring(5L)

  expect_true(is_dag(dag))
  expect_false(is_dag(tree))
  expect_false(is_dag(ring))

  expect_true(is_acyclic(dag))
  expect_true(is_acyclic(tree))
  expect_false(is_acyclic(ring))
})

test_that("topological_sorting works", {
  dag = graph_tree(5L)
  unsorted = permutate_vertices(dag, c(2L, 4L, 5L, 3L, 1L))
  perm = topological_sorting(unsorted) |>
    expect_type("integer") |>
    expect_length(vcount(dag))
  sorted = permutate_vertices(unsorted, perm)
  expect_true(is_same_graph(sorted, dag))
  expect_identical(as.matrix(sorted), as.matrix(dag))
})

test_that("eulerian test works", {
  expect_identical(is_eulerian(graph_tree(5L)), c(FALSE, FALSE))
  expect_identical(is_eulerian(graph_square_lattice(5L)), c(TRUE, FALSE))
  expect_identical(is_eulerian(graph_ring(5L)), c(TRUE, TRUE))
})
