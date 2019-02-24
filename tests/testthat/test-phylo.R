context("test-phylo")

test_that("phylo conversion works", {
  ig = graph_tree(7L)
  expect_s3_class(as_phylo(ig), "phylo")
  phy = ape::rtree(4L)
  expect_s4_class(as_igraph(phy), "Rcpp_IGraph")
})
