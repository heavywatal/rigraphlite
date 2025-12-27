# Convert edge lists to igraph objects.

An edge list is a two-column matrix or data.frame where the first column
contains the source vertices and the second column contains the target
vertices.

## Usage

``` r
graph_from_data_frame(edgelist, directed = TRUE)

graph_from_symbolic_edgelist(edgelist, directed = TRUE)

graph_from_edgelist(edgelist, directed = TRUE)
```

## Arguments

- edgelist:

  An edge list in two-column matrix or data.frame format.
  `graph_from_edgelist()` only accepts integer values, interpreting them
  directly as vertex IDs starting from 1. Other functions support
  non-numeric values, treating them as vertex names. A data.frame may
  contain additional columns for edge attributes.

- directed:

  A logical.

## Value

An
[igraph_ptr](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object.

## See also

[`as.data.frame.igraph_ptr()`](https://heavywatal.github.io/rigraphlite/reference/conversion.md)
and
[`as.matrix.igraph_ptr()`](https://heavywatal.github.io/rigraphlite/reference/conversion.md)
do the opposite conversion.

## Examples

``` r
edges = seq_len(6L) + 3L
edgelist = matrix(edges, ncol = 2L, byrow = TRUE)
g = graph_from_edgelist(edgelist) |> print()
#> $V  tibble [9 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 3 × 2
#>    from    to
#>   <int> <int>
#> 1     4     5
#> 2     6     7
#> 3     8     9
stopifnot(all.equal(as.matrix(g), as.matrix(graph_create(edges))))

symbolic = matrix(letters[edges], ncol = 2L)
graph_from_symbolic_edgelist(symbolic)
#> $V  tibble [6 × 1] (S3: tbl_df/tbl/data.frame)
#>  $ name: chr [1:6] "d" "g" "e" "h" ...
#> # A tibble: 3 × 2
#>   from  to   
#>   <chr> <chr>
#> 1 d     g    
#> 2 e     h    
#> 3 f     i    
```
