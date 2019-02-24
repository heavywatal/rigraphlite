# It is actually an RC, but the super class "C++Object" has S4 show()
setClass("Rcpp_IGraph")
setMethod("show", "Rcpp_IGraph", function(object){
  methods::callNextMethod(object)
  cat("$V  ")
  utils::str(object$Vattr)
  print(object$as_data_frame())
  invisible(object)
})
