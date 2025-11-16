test_that("induced_subgraph works", {
  g = graph_tree(7L)
  vids = seq_len(4L)
  subg = induced_subgraph(g, vids)
  expect_s3_class(subg, "igraph_ptr")
  expect_shape(Vattr(subg), dim = c(vcount(subg), 0L))
  expect_identical(V(subg), vids)
  expect_shape(Eattr(subg), dim = c(ecount(subg), 0L))
  expect_identical(E(subg), seq_len(ecount(subg)))

  g = graph_tree(7L)
  Vattr(g)$name = LETTERS[V(g)]
  Vattr(g)$weight = as.double(V(g))
  Eattr(g)$name = LETTERS[E(g)]
  Eattr(g)$weight = as.double(E(g))
  vids = seq_len(4L)
  expect_silent({
    subg = induced_subgraph(g, vids)
  })
  expect_shape(Vattr(subg), dim = c(vcount(subg), ncol(Vattr(g))))
  expect_identical(Vnames(subg), Vnames(g)[vids])
  expect_shape(Eattr(subg), dim = c(ecount(subg), 0L)) # discarded
  expect_identical(E(subg), seq_len(ecount(subg)))
})

test_that("subgraph_from_edges works", {
  g = graph_tree(7L)
  Vattr(g)$name = LETTERS[V(g)]
  Vattr(g)$weight = as.double(V(g))
  Eattr(g)$name = LETTERS[E(g)]
  Eattr(g)$weight = as.double(E(g))
  vids = seq_len(4L)
  eids = induced_subgraph_edges(g, vids)
  expect_identical(eids, seq_len(3L))

  subg = subgraph_from_edges(g, eids)
  expect_length(V(subg), length(vids))
  expect_length(E(subg), length(eids))
  expect_shape(Vattr(subg), dim = c(vcount(subg), 0L)) # discarded
  expect_shape(Eattr(subg), dim = c(ecount(subg), ncol(Eattr(g))))
  expect_identical(as.matrix(subg), as.matrix(induced_subgraph(g, vids)))
})
