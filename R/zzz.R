# nocov start
.onUnload = function(libpath) {
  library.dynam.unload("igraphlite", libpath)
}
# nocov end
