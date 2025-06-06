% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/structural.R
\name{neighborhood_size}
\alias{neighborhood_size}
\alias{neighborhood}
\title{Neighborhood of vertices}
\source{
\url{https://igraph.org/c/doc/igraph-Structural.html#neighborhood-of-a-vertex}
}
\usage{
neighborhood_size(
  graph,
  vids = integer(0),
  order = 1L,
  mode = 1L,
  mindist = 0L
)

neighborhood(graph, vids = integer(0), order = 1L, mode = 1L, mindist = 0L)
}
\arguments{
\item{graph}{An \code{\link{igraph_ptr}} object.}

\item{vids}{An integer vector of vertex IDs.}

\item{order}{An integer giving the order of the neighborhood;
e.g., \code{order = 1L} considers only the immediate neighbors.}

\item{mode}{An integer value of edge type to count; \{1: OUT, 2: IN, 3: ALL\}.}

\item{mindist}{The minimum distance to include a vertex in the counting;
e.g., \code{mindist = 1L} excludes the starting vertex itself, and \code{2L} excludes
the immediate neighbors.}
}
\value{
\code{neighborhood_size()} returns an integer vector of the neighborhood
sizes for the given vertices.

\code{neighborhood()} returns a list of integer vectors, each containing the
vertex IDs of the neighbors of the given vertices.
}
\description{
Neighborhood of vertices
}
\examples{
g = graph_tree(5L)
neighborhood_size(g)
neighborhood(g)
}
