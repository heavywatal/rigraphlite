// [[Rcpp::plugins(cpp14)]]
#include <Rcpp.h>

#include <igraph/igraph_error.h>
#include <igraph/igraph_version.h>

void error_handler(const char* reason, const char* file, int line, int igraph_errno) {
  igraph_error_handler_printignore(reason, file, line, igraph_errno);
  Rcpp::stop("%s: %s", reason, igraph_strerror(igraph_errno));
}

//' Check and return igraph version.h
//'
//' @rdname version
//' @export
// [[Rcpp::export]]
Rcpp::StringVector igraph_version() {
  const char* version_string;
  int major, minor, patch;
  igraph_version(&version_string, &major, &minor, &patch);
  if (major < 0 || minor < 8 || patch < 0) {
    Rcpp::warning("too old igraph %s", version_string);
  }
  return version_string;
}

// [[Rcpp::init]]
void igraphlite_init(DllInfo *dll) {
  igraph_version();
  igraph_set_error_handler(&error_handler);
}
