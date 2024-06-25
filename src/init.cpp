#include "cpp11.hpp"

#include <igraph/igraph_error.h>
#include <igraph/igraph_interrupt.h>
#include <igraph/igraph_random.h>
#include <igraph/igraph_version.h>

[[cpp11::register]]
cpp11::r_string igraph_version_() {
  const char* version_string;
  int major, minor, patch;
  igraph_version(&version_string, &major, &minor, &patch);
  if (major <= 0 && minor <= 10 && patch < 12) {
    cpp11::warning("too old igraph %s", version_string);
  }
  return cpp11::r_string(version_string);
}

void error_handler(const char* reason, const char* file, int line, igraph_error_t igraph_errno) {
  cpp11::stop("%s:%d: %s: %s", file, line, reason, igraph_strerror(igraph_errno));
}

void warning_handler(const char* reason, const char* file, int line) {
  cpp11::warning("%s:%d: %s", file, line, reason);
}

igraph_error_t interruption_handler(void* data) {
  if (!R_ToplevelExec([](void*){cpp11::check_user_interrupt();}, NULL)) {
    IGRAPH_FINALLY_FREE();
    return IGRAPH_INTERRUPTED;
  }
  return IGRAPH_SUCCESS;
}

igraph_rng_t igraph_rng_R_instance;

[[cpp11::init]]
void igraphlite_init(DllInfo *dll) {
  igraph_version_();
  igraph_set_error_handler(&error_handler);
  igraph_set_warning_handler(&warning_handler);
  igraph_set_interruption_handler(&interruption_handler);
  igraph_rng_init(&igraph_rng_R_instance, &igraph_rngtype_pcg32);
  igraph_rng_set_default(&igraph_rng_R_instance);
}

[[cpp11::register]]
void rng_seed(long seed) {
  igraph_rng_seed(igraph_rng_default(), static_cast<unsigned long>(seed));
}
