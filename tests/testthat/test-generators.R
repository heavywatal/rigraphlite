context("test-generators")

test_that("generator functions work", {
  n = 8L
  edges = seq_len(n)
  el = matrix(edges, ncol = 2L)
  df = as.data.frame(el)
  expect_s4_class(graph_tree(n), "Rcpp_IGraph")
  expect_s4_class(graph_create(edges), "Rcpp_IGraph")
  expect_s4_class(graph_from_edgelist(el), "Rcpp_IGraph")
  expect_s4_class(graph_from_symbolic_edgelist(el), "Rcpp_IGraph")
  expect_s4_class(graph_from_data_frame(el), "Rcpp_IGraph")
  expect_error(graph_create(seq_len(n - 1L)))
})
