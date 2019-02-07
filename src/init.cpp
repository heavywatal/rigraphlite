// [[Rcpp::plugins(cpp14)]]
#include <Rcpp.h>

#include <igraph/igraph_attributes.h>

void error_handler(const char* reason, const char* file, int line, int igraph_errno) {
  igraph_error_handler_printignore(reason, file, line, igraph_errno);
  Rcpp::stop("%s: %s", reason, igraph_strerror(igraph_errno));
}

// [[Rcpp::init]]
void igraphlite_init(DllInfo *dll) {
  igraph_set_error_handler(&error_handler);
  igraph_i_set_attribute_table(&igraph_cattribute_table);
}
