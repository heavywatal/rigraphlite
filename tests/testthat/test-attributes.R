test_that("attribute getters/setters work", {
  g = graph_tree(7L)
  expect_length(
    {
      vertex_attr(g, "name") = g$V
    },
    g$vcount
  )
  expect_equal(vertex_attr(g, "name"), g$V)
  expect_s3_class(
    {
      vattr = vertex_attr(g)
    },
    "data.frame"
  )
  expect_s3_class(
    {
      vertex_attr(g) = vattr
    },
    "data.frame"
  )
  expect_length(
    {
      edge_attr(g, "name") = g$E
    },
    g$ecount
  )
  expect_equal(edge_attr(g, "name"), g$E)
  expect_s3_class(
    {
      eattr = edge_attr(g)
    },
    "data.frame"
  )
  expect_s3_class(
    {
      edge_attr(g) = eattr
    },
    "data.frame"
  )
})

test_that("name-id conversion works", {
  edges = seq_len(8L)
  el = matrix(edges, ncol = 2L)
  vnames = as.vector(t(el))
  g = graph_from_symbolic_edgelist(el)
  expect_equal(Vnames(g), vnames)
  expect_equal(as_vnames(g, g$V), vnames)
  expect_equal(as_vids(g, vnames), g$V)
})
