test_that("phylo conversion works", {
  g = graph_tree(7L)
  expect_s3_class(as_phylo(g), "phylo")
  phy = ape::rtree(4L)
  expect_s3_class(as_igraph(phy), "igraph_ptr")
})

test_that("tbl_tree conversion works", {
  g = graph_tree(7L)
  tree = as_tbl_tree(g) |>
    expect_s3_class("tbl_tree")
  g2 = as_igraph(tree) |>
    expect_s3_class("igraph_ptr")
  expect_identical(row.names(as_tbl_tree(g2)), row.names(tree))
  expect_identical(as_tbl_tree(g2), tree)
})
