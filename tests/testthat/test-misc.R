context("test-misc")

test_that("common_params does nothing", {
  expect_silent(common_params())
  expect_null(common_params())
})
