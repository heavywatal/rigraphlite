# Get and set vertex and edge attributes

Attributes can be set and retrieved in several ways:

- with the `name` argument: `Vattr(g, "name") = letters[1:6]`

- with the `$` operator: `Vattr(g)$name = letters[1:6]`

- with the `[[` operator: `Vattr(g)[["name"]] = letters[1:6]`

- direct operation with a data.frame:
  `Vattr(g) = data.frame(name = letters[1:6])`

Using the `name` argument for setting and `$` operator for getting is
the most efficient way according to the brief benchmarking.

## Usage

``` r
Vattr(graph, name)

Vattr(graph, name) <- value

Eattr(graph, name)

Eattr(graph, name) <- value

V(graph)

E(graph)
```

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- name:

  Name of the attribute to query or set. If missing, all the attributes
  are returned or replaced.

- value:

  A vector or data.frame.

## Value

`Vattr()` and `Eattr()` return a data.frame with the same number of rows
as the number of vertices and edges in the graph, respectively.

`V()` and `E()` return an integer vector of vertex and edge IDs,
respectively.

## See also

[`Vnames()`](https://heavywatal.github.io/rigraphlite/reference/vnames.md)
for specialized function for "name" attribute.

## Examples

``` r
g = graph_create(letters[1:6])
Vattr(g)
#> # A tibble: 6 × 1
#>   name 
#>   <chr>
#> 1 a    
#> 2 b    
#> 3 c    
#> 4 d    
#> 5 e    
#> 6 f    
Eattr(g, "weight") = seq_len(ecount(g))
Eattr(g)
#> # A tibble: 3 × 1
#>   weight
#>    <int>
#> 1      1
#> 2      2
#> 3      3
V(g)
#> [1] 1 2 3 4 5 6
E(g)
#> [1] 1 2 3
```
