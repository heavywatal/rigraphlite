# Conversion between vertex IDs and names

`Vnames()` is a faster alternative to
[`Vattr()`](https://heavywatal.github.io/rigraphlite/reference/attributes.md)
to get the "name" attribute, falling back to
[`V()`](https://heavywatal.github.io/rigraphlite/reference/attributes.md)
when it is not set. `as_vids()` and `as_vnames()` provide convenient
shorthands using `Vnames()`.

## Usage

``` r
Vnames(graph)

as_vids(graph, vnames)

as_vnames(graph, vids)
```

## Arguments

- graph:

  An
  [`igraph_ptr`](https://heavywatal.github.io/rigraphlite/reference/igraph-class.md)
  object.

- vnames:

  Vertex names stored in `Vattr(g)$name`.

- vids:

  An integer vector of vertex IDs.

## Value

`Vnames()` and `as_vnames()` return a vector of vertex names or IDs.

`as_vids()` returns an integer vector of vertex IDs.

## Examples

``` r
g = graph_create(letters[1:6])
Vnames(g)
#> [1] "a" "b" "c" "d" "e" "f"
as_vids(g, c("d", "b"))
#> [1] 4 2
as_vnames(g, c(4L, 2L))
#> [1] "d" "b"

# Falls back to V(), not NULL
Vnames(graph_empty(3L))
#> [1] 1 2 3
```
