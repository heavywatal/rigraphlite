context("test-generators")

test_that("generator functions work", {
  n = 8L
  edges = seq_len(n)
  el = matrix(as.numeric(edges), ncol = 2L)
  symel = matrix(edges, ncol = 2L)
  df = as.data.frame(el)
  expect_s4_class(graph_tree(n), "Rcpp_IGraph")
  expect_s4_class(graph_create(edges), "Rcpp_IGraph")
  expect_s4_class(graph_from_edgelist(el), "Rcpp_IGraph")
  expect_s4_class(graph_from_symbolic_edgelist(symel), "Rcpp_IGraph")
  expect_s4_class(graph_from_data_frame(el), "Rcpp_IGraph")
  expect_error(graph_create(seq_len(n - 1L)))
})

test_that("S3/S4 methods work", {
  n = 8L
  edges = seq_len(n)
  el = matrix(as.numeric(edges), ncol = 2L)
  symel = matrix(edges, ncol = 2L)
  df = as.data.frame(el)
  expect_false(is_igraph(df))
  expect_true(is_igraph(as_igraph(edges)))
  expect_true(is_igraph(as_igraph(el)))
  expect_true(is_igraph(as_igraph(symel)))
  expect_true(is_igraph(as_igraph(df)))
  g = as_igraph(df)
  expect_output(show(g))
  expect_s3_class(as.data.frame(g), c("tbl_df", "tbl", "data.frame"))
  expect_is(as.matrix(g), "matrix")
})
