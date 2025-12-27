# `igraph_ptr`: cpp11-powered class for igraph objects

`igraph_ptr` is a subclass of external pointer to C++ `IGraph` objects.
The `IGraph` class is a thin wrapper of `igraph_t` in C igraph library.

## Usage

``` r
is_igraph(x)
```

## Source

<https://github.com/igraph/igraph/blob/master/include/igraph_datatype.h>

## Arguments

- x:

  An object to be tested.

## Value

A logical, `TRUE` if `x` is of class `igraph_ptr`, `FALSE` otherwise.

## See also

[`as_igraph()`](https://heavywatal.github.io/rigraphlite/reference/conversion.md)
and
[`as.data.frame.igraph_ptr()`](https://heavywatal.github.io/rigraphlite/reference/conversion.md)
for conversion from and to R objects.

## Examples

``` r
v = seq_len(6L)
is_igraph(v)
#> [1] FALSE

g = graph_create(v)
is_igraph(g)
#> [1] TRUE

print(g)
#> $V  tibble [6 × 0] (S3: tbl_df/tbl/data.frame)
#>  Named list()
#> # A tibble: 3 × 2
#>    from    to
#>   <int> <int>
#> 1     1     2
#> 2     3     4
#> 3     5     6
```
