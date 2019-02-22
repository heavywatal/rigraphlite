#include <Rcpp.h>

#include <igraph/igraph_error.h>
#include <igraph/igraph_version.h>

//' Check and return igraph version.h
//'
//' @seealso <https://igraph.org/c/doc/igraph-Nongraph.html>
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

void error_handler(const char* reason, const char* file, int line, int igraph_errno) {
  Rcpp::stop("%s:%d: %s: %s", file, line, reason, igraph_strerror(igraph_errno));
}

void warning_handler(const char* reason, const char* file, int line, int) {
  Rcpp::warning("%s:%d: %s", file, line, reason);
}

// [[Rcpp::init]]
void igraphlite_init(DllInfo *dll) {
  igraph_version();
  igraph_set_error_handler(&error_handler);
  igraph_set_warning_handler(&warning_handler);
}
