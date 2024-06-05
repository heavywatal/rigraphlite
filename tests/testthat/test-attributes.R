test_that("attribute getters/setters work", {
  g = graph_tree(7L)
  Vattr(g, "name") = V(g) |>
    expect_length(vcount(g))
  expect_identical(Vattr(g, "name"), V(g))
  vattr = Vattr(g) |>
    expect_s3_class("data.frame")
  Vattr(g) = vattr
  expect_identical(Vattr(g), vattr)
  Eattr(g, "name") = E(g) |>
    expect_length(ecount(g))
  expect_identical(Eattr(g, "name"), E(g))
  eattr = Eattr(g) |>
    expect_s3_class("data.frame")
  Eattr(g) = eattr
  expect_identical(Eattr(g), eattr)
})

test_that("name-id conversion works", {
  edges = seq_len(8L)
  el = matrix(edges, ncol = 2L)
  vnames = as.vector(t(el))
  g = graph_from_symbolic_edgelist(el)
  expect_identical(Vnames(g), vnames)
  expect_identical(as_vnames(g, V(g)), vnames)
  expect_identical(as_vids(g, vnames), V(g))
})
