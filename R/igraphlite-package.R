#' @useDynLib igraphlite, .registration = TRUE
#' @import Rcpp
#' @importFrom rlang .data
#' @keywords internal
"_PACKAGE"

#' IGraph class: thin wrapper of `igraph_t`.
#'
#' @field V Vertex IDs in a integer vector
#' @field E Edge IDs in a integer vector
#' @field Vattr Vertex attributes in a data.frame
#' @field Eattr Edge attributes in a data.frame
#'
#' @field from The first column of the edge list.
#' @field to The second column of the edge list.
#' @field oi The index of the edge list by the first column.
#' @field ii The index of the edge list by the second column.
#' @field os The pointers to the outgoing edges.
#' @field is The pointers to the incoming edges.
#'
#' @seealso [graph_from_edgelist()], [graph_from_data_frame], [graph_tree()]
#'   for object instanciation.
#' @source <https://github.com/igraph/igraph/blob/master/include/igraph_datatype.h>
#' @docType class
#' @keywords data
#' @format Reference Class (RC) exposed by Rcpp Modules.
#' @name IGraph
#' @rdname igraph-class
NULL

#' Check if an object is IGraph class
#'
#' @param x object to be tested.
#'
#' @rdname is_igraph
#' @export
is_igraph = function(x) {
  inherits(x, "Rcpp_IGraph")
}
