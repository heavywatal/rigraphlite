test_that("attribute getters/setters work", {
  n = 7L
  g = graph_tree(7L)

  Vattr(g)$name = V(g)
  Vattr(g)$name |>
    expect_identical(Vnames(g)) |>
    expect_identical(V(g)) |>
    expect_identical(seq_len(vcount(g)))
  vattr = Vattr(g) |>
    expect_s3_class("data.frame")
  Vattr(g) = vattr
  expect_identical(Vattr(g), vattr)

  Vattr(g)$name = V(g) |> as.double()
  expect_type(Vnames(g), "double")
  Vattr(g)$name = V(g) |> as.character()
  expect_type(Vnames(g), "character")
  Vattr(g)$name = V(g) |> as.complex()
  expect_identical(Vnames(g), V(g))

  Eattr(g)$name = E(g)
  Eattr(g)$name |>
    expect_identical(E(g)) |>
    expect_identical(seq_len(ecount(g)))
  eattr = Eattr(g) |>
    expect_s3_class("data.frame")
  Eattr(g) = eattr
  expect_identical(Eattr(g), eattr)

  expect_null(Vattr(g, "argument"))
  Vattr(g, "argument") = V(g)
  expect_null(Vattr(g)[["brackets"]])
  Vattr(g)[["brackets"]] = V(g)
  skip_if_not_installed("tibble")
  expect_null(Vattr(g)$dollar) |>
    expect_warning("column")
  Vattr(g)$dollar = V(g)
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
