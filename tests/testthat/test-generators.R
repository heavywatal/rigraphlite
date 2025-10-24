test_that("generator functions work", {
  n = 8L
  edges = seq_len(n)
  el = matrix(edges, ncol = 2L)
  symel = matrix(as.character(edges), ncol = 2L)
  dfi = as.data.frame(el)
  dfc = as.data.frame(symel)
  expect_s3_class(graph_create(edges), "igraph_ptr")
  expect_s3_class(graph_create(letters[edges]), "igraph_ptr")
  expect_s3_class(graph_from_edgelist(el), "igraph_ptr")
  expect_identical(graph_from_edgelist(el) |> Vattr() |> ncol(), 0L)
  expect_type(graph_from_symbolic_edgelist(el) |> Vnames(), "integer")
  expect_type(graph_from_symbolic_edgelist(symel) |> Vnames(), "character")
  expect_type(graph_from_data_frame(dfi) |> Vnames(), "integer")
  expect_type(graph_from_data_frame(dfc) |> Vnames(), "character")
  expect_error(graph_create(seq_len(n - 1L)))
})

test_that("named generator functions work", {
  n = 8L
  expect_s3_class(graph_star(n), "igraph_ptr")

  for (dim in seq.int(2L, 5L)) {
    hc = graph_hypercube(dim)
    expect_identical(vcount(hc), as.integer(2L**dim))
    expect_identical(ecount(hc), as.integer(2L**(dim - 1L) * dim))
  }

  expect_s3_class(graph_square_lattice(c(2L, 3L)), "igraph_ptr")
  expect_s3_class(graph_triangular_lattice(c(2L, 3L)), "igraph_ptr")
  expect_s3_class(graph_hexagonal_lattice(c(2L, 3L)), "igraph_ptr")
  graph_hypercube(4L) |> plot()

  cycle = graph_ring(n) |> expect_s3_class("igraph_ptr")
  expect_true(is_same_graph(graph_path(n), graph_ring(n, circular = FALSE)))
  expect_true(is_same_graph(graph_cycle(n), cycle))

  expect_true(is_same_graph(graph_circulant(n, 1L), cycle))
  expect_true(is_same_graph(graph_lcf(n, integer(0L), 0L), cycle))
  expect_true(is_same_graph(graph_lcf(n, 2L), graph_circulant(n, c(1L, 2L))))

  expect_s3_class(graph_tree(n), "igraph_ptr")
  expect_s3_class(graph_full(n), "igraph_ptr")
  expect_s3_class(graph_famous("Diamond"), "igraph_ptr")
})

test_that("generator round-trip", {
  tree = graph_tree(7L)
  df = as.data.frame(tree)
  df$from = df$from + 10L
  df$to = df$to + 10L
  df$weight = df$to * 100
  g_df = graph_from_data_frame(df)
  expect_identical(as.data.frame(g_df), df)

  el = as.matrix(df[, 1:2])
  g_el = graph_from_symbolic_edgelist(el)
  expect_identical(as.data.frame(g_el) |> as.matrix(), el)

  df$from = as.double(df$from)
  df$to = as.double(df$to)
  g_df = graph_from_data_frame(df)
  expect_identical(as.data.frame(g_df), df)

  df$from = as.character(df$from)
  df$to = as.character(df$to)
  g_df = graph_from_data_frame(df)
  expect_identical(as.data.frame(g_df), df)

  df$from = as.complex(df$from)
  df$to = as.complex(df$to)
  expect_error(graph_from_data_frame(df))
})

test_that("as_/is_ functions work", {
  n = 8L
  edges = seq_len(n)
  el = matrix(edges, ncol = 2L)
  symel = matrix(as.character(edges), ncol = 2L)
  df = as.data.frame(el)
  expect_false(is_igraph(df))
  expect_true(is_igraph(as_igraph(edges)))
  expect_true(is_igraph(as_igraph(el)))
  expect_true(is_igraph(as_igraph(symel)))
  expect_true(is_igraph(as_igraph(df)))
})
