# Convert igraph objects to and from other formats.

Round-trip conversion is not guaranteed currently. Conversion to
data.frame preserves edge attributes and vertex names, but the other
vertex attributes are lost, and internal vertex IDs may change.

## Usage

``` r
as_igraph(x, ...)

# Default S3 method
as_igraph(x, ...)

# S3 method for class 'matrix'
as_igraph(x, ...)

# S3 method for class 'data.frame'
as_igraph(x, ...)

# S3 method for class 'igraph_ptr'
as.data.frame(x, ...)

# S3 method for class 'igraph_ptr'
as.matrix(x, ...)
```

## Arguments

- x:

  A vector, matrix, data.frame, or graph object to be converted.

- ...:

  Additional arguments passed to the conversion function.

## Value

`as_igraph()` returns an
[igraph_ptr](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
object.

[`as.data.frame()`](https://rdrr.io/r/base/as.data.frame.html) returns
an edge list in data.frame format, which may include additional columns
for edge attributes.

[`as.matrix()`](https://rdrr.io/r/base/matrix.html) returns an edge list
in matrix format.

## See also

[`graph_from_symbolic_edgelist()`](https://heavywatal.github.io/rigraphlite/reference/conversion-impl.md),
[`graph_from_edgelist()`](https://heavywatal.github.io/rigraphlite/reference/conversion-impl.md),
[`graph_from_data_frame()`](https://heavywatal.github.io/rigraphlite/reference/conversion-impl.md),
[`graph_create()`](https://heavywatal.github.io/rigraphlite/reference/graph_create.md)
for underlying functions.

## Examples

``` r
edges = seq_len(6L)
g1 = as_igraph(edges)
edgelist = as.matrix(g1) |> print()
#>      [,1] [,2]
#> [1,]    1    2
#> [2,]    3    4
#> [3,]    5    6

g2 = as_igraph(edgelist)
g3 = as_igraph(as.data.frame(g2)) |> print()
#> $V  tibble [6 × 1] (S3: tbl_df/tbl/data.frame)
#>  $ name: int [1:6] 1 2 3 4 5 6
#> # A tibble: 3 × 2
#>    from    to
#>   <int> <int>
#> 1     1     2
#> 2     3     4
#> 3     5     6
```
