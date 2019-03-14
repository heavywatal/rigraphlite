context("test-layout")

test_that("layout functions add x-y columns", {
  g = graph_tree(7L)
  expect_named(layout_nicely(g)$Vattr, c("x", "y"))
  expect_named(layout_random(g)$Vattr, c("x", "y"))
  expect_named(layout_drl(g)$Vattr, c("x", "y"))
  expect_named(layout_fruchterman_reingold(g)$Vattr, c("x", "y"))
  expect_named(layout_mds(g)$Vattr, c("x", "y"))
  expect_named(layout_reingold_tilford(g)$Vattr, c("x", "y"))
  expect_named(layout_reingold_tilford_circular(g)$Vattr, c("x", "y"))
})
