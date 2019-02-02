// [[Rcpp::plugins(cpp14)]]
#include <Rcpp.h>

// [[Rcpp::export]]
int len(const std::vector<std::string>& args) {
    return args.size();
}
