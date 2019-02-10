#' @useDynLib igraphlite, .registration = TRUE
#' @import Rcpp
#' @keywords internal
"_PACKAGE"

.onUnload = function(libpath) {
  library.dynam.unload("igraphlite", libpath)
}

Rcpp::loadModule("igraph", TRUE)

# It is actually an RC, but the super class "C++Object" has S4 show()
setClass("Rcpp_IGraph")
setMethod("show", "Rcpp_IGraph", function(object){
  methods::callNextMethod(object)
  cat("$V  ")
  utils::str(object$V)
  print(object$as_data_frame())
  invisible(object)
})
