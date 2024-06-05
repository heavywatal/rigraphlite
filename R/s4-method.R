# It is actually an RC, but the super class "C++Object" has S4 show()
setClass("Rcpp_IGraph")
setMethod("show", "Rcpp_IGraph", function(object) {
  methods::callNextMethod(object)
  cat("$V  ")
  utils::str(Vattr(object))
  print(as.data.frame(object))
  invisible(object)
})
