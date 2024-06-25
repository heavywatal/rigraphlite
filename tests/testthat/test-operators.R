test_that("induced_subgraph works", {
  g = graph_tree(7L)
  vids = seq_len(4L)
  subg = induced_subgraph(g, vids)
  expect_s3_class(subg, "igraph_ptr")
  length(V(subg)) |>
    expect_identical(vcount(subg)) |>
    expect_identical(nrow(Vattr(subg))) |>
    expect_identical(4L)
  length(E(subg)) |>
    expect_identical(ecount(subg)) |>
    expect_identical(nrow(Eattr(subg))) |>
    expect_identical(3L)

  g = graph_tree(7L)
  Vattr(g)$name = LETTERS[V(g)]
  Vattr(g)$weight = as.double(V(g))
  Eattr(g)$name = LETTERS[E(g)]
  Eattr(g)$weight = as.double(E(g))
  vids = seq_len(4L)
  expect_silent({
    subg = induced_subgraph(g, vids)
  })
  length(V(subg)) |>
    expect_identical(vcount(subg)) |>
    expect_identical(nrow(Vattr(subg))) |>
    expect_identical(4L)
  length(E(subg)) |>
    expect_identical(ecount(subg)) |>
    expect_identical(nrow(Eattr(subg))) |>
    expect_identical(3L)
  expect_length(V(subg), length(vids))
  expect_identical(ncol(Vattr(subg)), ncol(Vattr(g)))
  expect_identical(ncol(Eattr(subg)), 0L) # discarded
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
  expect_identical(ncol(Vattr(subg)), 0L) # discarded
  expect_identical(ncol(Eattr(subg)), ncol(Eattr(g)))
  expect_identical(as.matrix(subg), as.matrix(induced_subgraph(g, vids)))
})
