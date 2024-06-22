test_that("igraph_version() works", {
  igraph_version() |>
    expect_silent() |>
    expect_type("character")
})

test_that("common_params does nothing", {
  common_params() |>
    expect_silent() |>
    expect_null()
})
