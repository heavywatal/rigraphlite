% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/generators.R
\name{graph_create}
\alias{graph_create}
\alias{graph_star}
\alias{graph_lattice}
\alias{graph_ring}
\alias{graph_tree}
\alias{graph_full}
\alias{graph_famous}
\title{Deterministic Graph Generators}
\source{
\url{https://igraph.org/c/doc/igraph-Generators.html}
}
\usage{
graph_create(edges, n = 0L, directed = TRUE)

graph_star(n, mode = 0L, center = 1L)

graph_lattice(
  dim,
  nei = 1L,
  directed = FALSE,
  mutual = FALSE,
  circular = FALSE
)

graph_ring(n, directed = FALSE, mutual = FALSE, circular = TRUE)

graph_tree(n, children = 2L, mode = 0L)

graph_full(n, directed = FALSE, mutual = FALSE)

graph_famous(name)
}
\arguments{
\item{edges}{The edges to add, the first two elements are the first edge, etc.}

\item{n}{Integer, the number of vertices in the graph.}

\item{directed}{Boolean}

\item{mode}{Integer;
\itemize{
\item \code{igraph_star_mode_t} \{0: OUT, 1: IN, 2: MUTUAL, 3: UNDIRECTED\}
\item \code{igraph_tree_mode_t} \{0: OUT, 1: IN, 2: UNDIRECTED\}
}}

\item{center}{Id of the vertex which will be the center of the graph.}

\item{dim}{Vector giving the sizes of the lattice in each of its dimensions.}

\item{nei}{Integer distance within which two vertices will be connected.}

\item{mutual}{Boolean}

\item{circular}{Boolean}

\item{children}{Integer, the number of children of a vertex in the tree.}

\item{name}{\{Bull, Chvatal, Coxeter, Cubical, Diamond, Dodecahedral,
Dodecahedron, Folkman, Franklin, Frucht, Grotzsch, Heawood, Herschel, House,
HouseX, Icosahedral, Icosahedron, Krackhardt_Kite, Levi, McGee, Meredith,
Noperfectmatching, Nonline, Octahedral, Octahedron, Petersen, Robertson,
Smallestcyclicgroup, Tetrahedral, Tetrahedron, Thomassen, Tutte,
Uniquely3colorable, Walther, Zachary\}}
}
\description{
Deterministic Graph Generators
}
\seealso{
\code{\link[=as_igraph]{as_igraph()}}, \code{\link[=graph_from_data_frame]{graph_from_data_frame()}}
}
