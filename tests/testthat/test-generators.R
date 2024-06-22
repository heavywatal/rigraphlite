test_that("generator functions work", {
  n = 8L
  edges = seq_len(n)
  el = matrix(edges, ncol = 2L)
  symel = matrix(as.character(edges), ncol = 2L)
  dfi = as.data.frame(el)
  dfc = as.data.frame(symel)
  expect_s3_class(graph_tree(n), "igraph_ptr")
  expect_s3_class(graph_create(edges), "igraph_ptr")
  expect_s3_class(graph_from_edgelist(el), "igraph_ptr")
  expect_identical(graph_from_edgelist(el) |> Vattr() |> ncol(), 0L)
  expect_type(graph_from_symbolic_edgelist(el) |> Vattr("name"), "integer")
  expect_type(graph_from_symbolic_edgelist(symel) |> Vattr("name"), "character")
  expect_type(graph_from_data_frame(dfi) |> Vattr("name"), "integer")
  expect_type(graph_from_data_frame(dfc) |> Vattr("name"), "character")
  expect_error(graph_create(seq_len(n - 1L)))
})

test_that("generator round-trip", {
  tree = graph_tree(7L)
  df = as.data.frame(tree)
  el = as.matrix(df) + 10L
  gdf = graph_from_data_frame(df)
  expect_identical(as.data.frame(gdf), df)
  gel = graph_from_symbolic_edgelist(el)
  expect_identical(as.data.frame(gel) |> as.matrix(), el)
})

test_that("as_/is_ functions work", {
  n = 8L
  edges = seq_len(n)
  el = matrix(edges, ncol = 2L)
  symel = matrix(as.character(edges), ncol = 2L)
  df = as.data.frame(el)
  expect_false(is_igraph(df))
  expect_true(is_igraph(as_igraph(edges)))
  expect_true(is_igraph(as_igraph(el)))
  expect_true(is_igraph(as_igraph(symel)))
  expect_true(is_igraph(as_igraph(df)))
})
