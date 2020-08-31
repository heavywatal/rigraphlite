test_that("S3 methods work", {
  g = graph_tree(7L)
  expect_output(show(g))
  expect_s3_class(as.data.frame(g), c("tbl_df", "tbl", "data.frame"))
  expect_true(is.matrix(as.matrix(g)))
})

test_that("visualization methods work", {
  g = graph_tree(7L)
  .colnames = c("from", "to", "x", "y", "xend", "yend")
  expect_named(augment(g), .colnames)
  expect_named(augment(g, layout = layout_reingold_tilford), .colnames)
  expect_named(augment(g, layout = layout_reingold_tilford(g)), .colnames)
  expect_error(augment(g, layout = data.frame(a = 0, b = 0)), "hasName")
  expect_error(augment(g, layout = data.frame(x = 0, y = 0)), "nrow")
  expect_error(augment(g, layout = "layout_reingold_tilford"), "Invalid type")
  expect_silent(plot(g)) |>
    expect_s3_class(c("gg", "ggplot"))
  expect_silent(plot(g, layout = layout_reingold_tilford)) |>
    expect_s3_class(c("gg", "ggplot"))
})
