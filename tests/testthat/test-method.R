context("test-method")

test_that("S3/S4 methods work", {
  g = graph_tree(7L)
  expect_output(show(g))
  expect_s3_class(as.data.frame(g), c("tbl_df", "tbl", "data.frame"))
  expect_is(as.matrix(g), "matrix")
  expect_s3_class(augment(g), c("tbl_df", "tbl", "data.frame"))
  expect_s3_class(plot(g), c("gg", "ggplot"))
})
