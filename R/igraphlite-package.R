#' @useDynLib igraphlite, .registration = TRUE
#' @import Rcpp
#' @keywords internal
"_PACKAGE"

.onUnload = function(libpath) {
  library.dynam.unload("igraphlite", libpath)
}

Rcpp::loadModule("igraph", TRUE)
Rcpp::loadModule("test", TRUE)
