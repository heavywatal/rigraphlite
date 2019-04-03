context("test-method")

test_that("S3/S4 methods work", {
  g = graph_tree(7L)
  expect_output(show(g))
  expect_s3_class(as.data.frame(g), c("tbl_df", "tbl", "data.frame"))
  expect_is(as.matrix(g), "matrix")
  .colnames = c("from", "to", "x", "y", "xfrom", "yfrom")
  expect_named(augment(g), .colnames)
  expect_named(augment(g, layout = layout_reingold_tilford), .colnames)
  expect_error(augment(g, layout = "layout_reingold_tilford"), c("Invalid type"))
  expect_s3_class(plot(g), c("gg", "ggplot"))
  expect_s3_class(plot(g, layout = layout_reingold_tilford), c("gg", "ggplot"))
})
