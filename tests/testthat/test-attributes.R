test_that("attribute getters/setters work", {
  g = graph_tree(7L)
  vertex_attr(g, "name") = V(g) |>
    expect_length(g$vcount)
  expect_identical(vertex_attr(g, "name"), V(g))
  vattr = vertex_attr(g) |>
    expect_s3_class("data.frame")
  vertex_attr(g) = vattr
  expect_identical(vertex_attr(g), vattr)
  edge_attr(g, "name") = E(g) |>
    expect_length(g$ecount)
  expect_identical(edge_attr(g, "name"), E(g))
  eattr = edge_attr(g) |>
    expect_s3_class("data.frame")
  edge_attr(g) = eattr
  expect_identical(edge_attr(g), eattr)
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
