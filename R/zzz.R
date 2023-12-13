.onUnload = function(libpath) {
  library.dynam.unload("igraphlite", libpath)
}

Rcpp::loadModule("igraph", TRUE)
