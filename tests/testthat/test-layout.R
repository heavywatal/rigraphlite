context("test-layout")

test_that("layout functions return x-y columns", {
  g = graph_tree(7L)
  expect_named(layout_nicely(g), c("x", "y"))
  expect_named(layout_random(g), c("x", "y"))
  expect_named(layout_drl(g), c("x", "y"))
  expect_named(layout_fruchterman_reingold(g), c("x", "y"))
  expect_named(layout_mds(g), c("x", "y"))
  expect_named(layout_reingold_tilford(g), c("x", "y"))
  expect_named(layout_reingold_tilford_circular(g), c("x", "y"))
})
