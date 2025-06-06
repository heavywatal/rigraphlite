% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/igraphlite-package.R
\name{igraph_ptr}
\alias{igraph_ptr}
\alias{is_igraph}
\title{\code{igraph_ptr}: cpp11-powered class for igraph objects}
\source{
\url{https://github.com/igraph/igraph/blob/master/include/igraph_datatype.h}
}
\usage{
is_igraph(x)
}
\arguments{
\item{x}{An object to be tested.}
}
\value{
A logical, \code{TRUE} if \code{x} is of class \code{igraph_ptr}, \code{FALSE} otherwise.
}
\description{
\code{igraph_ptr} is a subclass of external pointer to C++ \code{IGraph} objects.
The \code{IGraph} class is a thin wrapper of \code{igraph_t} in C igraph library.
}
\examples{
v = seq_len(6L)
is_igraph(v)

g = graph_create(v)
is_igraph(g)

print(g)
}
\seealso{
\code{\link[=as_igraph]{as_igraph()}} and \code{\link[=as.data.frame.igraph_ptr]{as.data.frame.igraph_ptr()}} for conversion
from and to R objects.
}
