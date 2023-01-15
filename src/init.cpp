#include <Rcpp.h>

#include <igraph/igraph_error.h>
#include <igraph/igraph_interrupt.h>
#include <igraph/igraph_random.h>
#include <igraph/igraph_version.h>

//' Check and return igraph version.h
//'
//' @source <https://igraph.org/c/doc/igraph-Nongraph.html>
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

void error_handler(const char* reason, const char* file, int line, igraph_error_t igraph_errno) {
  Rcpp::stop("%s:%d: %s: %s", file, line, reason, igraph_strerror(igraph_errno));
}

void warning_handler(const char* reason, const char* file, int line) {
  Rcpp::warning("%s:%d: %s", file, line, reason);
}

igraph_error_t interruption_handler(void* data) {
  Rcpp::checkUserInterrupt();
  return IGRAPH_SUCCESS;
}

// [[Rcpp::init]]
void igraphlite_init(DllInfo *dll) {
  igraph_version();
  igraph_set_error_handler(&error_handler);
  igraph_set_warning_handler(&warning_handler);
  igraph_set_interruption_handler(&interruption_handler);
}

//' Random numbers
//'
//' @source <https://igraph.org/c/doc/igraph-Random.html>
//' @param seed An integer.
//' @rdname random
//' @export
// [[Rcpp::export]]
void rng_seed(long seed) {
  igraph_rng_seed(igraph_rng_default(), static_cast<unsigned long>(seed));
}
