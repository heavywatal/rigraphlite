test_that("read_graph and write_graph work", {
  g = graph_tree(7L)
  el = as.matrix(g)

  file_edgelist = tempfile(fileext = ".edgelist")
  write_graph(g, file_edgelist)
  read_graph(file_edgelist, directed = TRUE) |>
    as.matrix() |>
    expect_identical(el)

  file_ncol = tempfile(fileext = ".ncol")
  write_graph(g, file_ncol)
  read_graph(file_ncol, directed = TRUE) |>
    as.matrix() |>
    expect_identical(el)

  file_lgl = tempfile(fileext = ".lgl")
  write_graph(g, file_lgl)
  read_graph(file_lgl, directed = TRUE) |>
    as.matrix() |>
    expect_identical(el)

  file_graphml = tempfile(fileext = ".graphml")
  write_graph(g, file_graphml)
  read_graph(file_graphml) |>
    as.matrix() |>
    expect_identical(el)

  file_xml = tempfile(fileext = ".xml")
  write_graph(g, file_xml, "graphml")
  read_graph(file_xml, "graphml") |>
    as.matrix() |>
    expect_identical(el)

  file_gml = tempfile(fileext = ".gml")
  write_graph(g, file_gml)
  read_graph(file_gml) |>
    as.matrix() |>
    expect_identical(el)

  file_net = tempfile(fileext = ".net")
  write_graph(g, file_net)
  read_graph(file_net) |>
    as.matrix() |>
    expect_identical(el)

  file_pajek = tempfile(fileext = ".txt")
  write_graph(g, file_pajek, "pajek")
  read_graph(file_pajek, "pajek") |>
    as.matrix() |>
    expect_identical(el)

  file_dot = tempfile(fileext = ".dot")
  write_graph(g, file_dot)
  expect_error(read_graph(file_dot), "Unsupported file format")

  file_leda = tempfile(fileext = ".leda")
  write_graph(g, file_leda)
  expect_error(read_graph(file_leda), "Unsupported file format")
})

test_that("UCINET DL format can be read", {
  g = read_graph(test_path("fixtures", "ucinet-fullmatrix.dl"), directed = TRUE)
  expect_identical(vcount(g), 5L)
  expect_identical(ecount(g), 12L)
  g = read_graph(test_path("fixtures", "ucinet-edgelist1.dl"), directed = TRUE)
  expect_identical(vcount(g), 5L)
  expect_identical(ecount(g), 5L)
  g = read_graph(test_path("fixtures", "ucinet-nodelist1.dl"), directed = FALSE)
  expect_identical(vcount(g), 5L)
  expect_identical(ecount(g), 5L)

  expect_error(write_graph(g, tempfile(fileext = ".dl")), "Unsupported file format")
})
