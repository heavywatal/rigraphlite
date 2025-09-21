#include "igraph.hpp"
#include "policy.hpp"
#include "dataframe.hpp"

#include <igraph/igraph_interface.h>

IGraph::IGraph() noexcept:
  data_(std::make_unique<igraph_t>()),
  Vattr_(impl::tibble({})),
  Eattr_(impl::tibble({})) {}

IGraph::~IGraph() noexcept {
  if (data_) igraph_destroy(data_.get());
}

IGraph::IGraph(const IGraph& other) noexcept:
  data_(std::make_unique<igraph_t>()),
  Vattr_(other.Vattr_),
  Eattr_(other.Eattr_) {
  igraph_copy(data_.get(), other.data_.get());
}

int IGraph::vcount() const {
  return igraph_vcount(data_.get());
}

int IGraph::ecount() const {
  return igraph_ecount(data_.get());
}

cpp11::integers IGraph::from() const {return AsIndices::wrap(&data_->from);}
cpp11::integers IGraph::to() const {return AsIndices::wrap(&data_->to);}
cpp11::integers IGraph::oi() const {return AsIndices::wrap(&data_->oi);}
cpp11::integers IGraph::ii() const {return AsIndices::wrap(&data_->ii);}
cpp11::integers IGraph::os() const {return AsIndices::wrap(&data_->os);}
cpp11::integers IGraph::is() const {return AsIndices::wrap(&data_->is);}

void IGraph::init_attr() {
  impl::set_data_frame_attributes(&Vattr_, vcount());
  impl::set_data_frame_attributes(&Eattr_, ecount());
}
