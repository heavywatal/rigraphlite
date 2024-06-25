test_that("attribute getters/setters work", {
  n = 7L
  g = graph_tree(7L)

  Vattr(g)$name = V(g)
  Vattr(g)$name |>
    expect_identical(V(g)) |>
    expect_identical(seq_len(vcount(g)))
  vattr = Vattr(g) |>
    expect_s3_class("data.frame")
  vattr$weight = V(g) + 10
  Vattr(g) = vattr
  expect_identical(Vattr(g), vattr)
  Vattr(g)$weight = V(g) + 100
  expect_true(all(Vattr(g)$weight > vattr$weight))

  Eattr(g)$name = E(g)
  Eattr(g)$name |>
    expect_identical(E(g)) |>
    expect_identical(seq_len(ecount(g)))
  eattr = Eattr(g) |>
    expect_s3_class("data.frame")
  eattr$weight = E(g) + 10
  Eattr(g) = eattr
  expect_identical(Eattr(g), eattr)
  Eattr(g)$weight = E(g) + 100
  expect_true(all(Eattr(g)$weight > eattr$weight))

  Vattr(g)[["brackets"]] = V(g)
  expect_identical(Vattr(g)[["brackets"]], V(g))
  skip_if_not_installed("tibble")
  expect_null(Vattr(g)$dollar) |>
    expect_warning("column")
  Vattr(g)$dollar = V(g)
  expect_identical(Vattr(g)$dollar, V(g))
})

test_that("mutate_*attr_() works", {
  g = graph_tree(7L)

  # mutate_Vattr_ push_back
  expect_null(Vattr(g, "argument"))
  Vattr(g, "argument") = V(g)
  expect_identical(Vattr(g, "argument"), V(g))

  # mutate_Vattr_ existing
  Vattr(g, "argument") = -V(g)
  expect_identical(Vattr(g, "argument"), -V(g))
  expect_null(Vattr(g)[["brackets"]])

  # mutate_Eattr_ push_back
  expect_null(Eattr(g, "argument"))
  Eattr(g, "argument") = E(g)
  expect_identical(Eattr(g, "argument"), E(g))

  # mutate_Eattr_ existing
  Eattr(g, "argument") = -E(g)
  expect_identical(Eattr(g, "argument"), -E(g))
  expect_null(Eattr(g)[["brackets"]])
})

test_that("Vnames() works", {
  g = graph_tree(7L)
  expect_identical(Vnames(g), V(g))
  Vattr(g)$name = V(g) |> as.raw()
  expect_type(Vnames(g), "raw")
  Vattr(g)$name = V(g)
  expect_type(Vnames(g), "integer")
  Vattr(g)$name = V(g) |> as.double()
  expect_type(Vnames(g), "double")
  Vattr(g)$name = V(g) |> as.complex()
  expect_type(Vnames(g), "complex")
  Vattr(g)$name = V(g) |> as.character()
  expect_type(Vnames(g), "character")
  Vattr(g)$name = V(g) |> as.list()
  expect_type(Vnames(g), "list")
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
