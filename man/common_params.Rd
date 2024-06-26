% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/utils.R
\name{common_params}
\alias{common_params}
\title{Common parameters used throughout the package}
\usage{
common_params(
  graph,
  vids,
  vid,
  from,
  to,
  eids,
  eid,
  mode,
  weights,
  directed,
  loops,
  multiple
)
}
\arguments{
\item{graph}{igraph_ptr object.}

\item{vids}{Vertices of interest.}

\item{vid}{Vertices of interest.}

\item{from}{Vertices of interest.}

\item{to}{Vertices of interest.}

\item{eids}{Edges of interest.}

\item{eid}{Edges of interest.}

\item{mode}{Edge type to count; \{1: OUT, 2: IN, 3: ALL\}.}

\item{weights}{Numeric edge weights; \code{TRUE} to use \code{Eattr(graph, "weight")}.}

\item{directed}{Boolean, whether to consider directed paths. Ignored for undirected graphs.}

\item{loops}{How to treat loop edges; \{0: NO_LOOPS, 1: LOOPS, 2: LOOPS_ONCE\}}

\item{multiple}{Boolean, whether to keep multiple (parallel) edges.}
}
\description{
This function does nothing. It is designed to be used with @inheritParams.
}
\keyword{internal}
