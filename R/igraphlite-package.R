#' @useDynLib igraphlite, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @keywords internal
"_PACKAGE"

.onUnload = function(libpath) {
  library.dynam.unload("igraphlite", libpath)
}

Rcpp::loadModule("test", TRUE)
