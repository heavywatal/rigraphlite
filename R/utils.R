# Use this function with @eval tag
common_params = function(...) {
  dots = as.character(substitute(...()))
  params = c(
    graph = "IGraph object.",
    vids = "Vertices of interest.",
    mode = "Edge type to count; {1: OUT, 2: IN, 3: ALL}.",
    weights = "Numeric edge weights; `TRUE` to use `graph$Eattr$weight`.",
    directed = "Boolean, whether to consider directed paths. Ignored for undirected graphs."
  )
  params["v"] = params["vids"]
  params["from"] = params["vids"]
  params["to"] = params["vids"]
  lines = setNames(paste("@param", names(params), params), names(params))
  lines[dots]
}
