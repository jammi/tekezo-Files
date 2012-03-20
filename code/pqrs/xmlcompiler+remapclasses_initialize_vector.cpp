#include "pqrs/bridge.h"
#include "pqrs/xmlcompiler.hpp"

namespace pqrs {
  xmlcompiler::remapclasses_initialize_vector::remapclasses_initialize_vector(void) :
    max_configindex_(0),
    freezed_(false)
  {
    data_.resize(2);
    data_[INDEX_OF_FORMAT_VERSION] = BRIDGE_REMAPCLASS_INITIALIZE_VECTOR_FORMAT_VERSION;
    data_[INDEX_OF_COUNT] = 0;
  }

  const std::vector<uint32_t>&
  xmlcompiler::remapclasses_initialize_vector::get(void) const
  {
    if (! freezed_) {
      throw xmlcompiler_logic_error("remapclasses_initialize_vector is not freezed.");
    }
    return data_;
  }

  void
  xmlcompiler::remapclasses_initialize_vector::add(const std::vector<uint32_t>& v, uint32_t configindex)
  {
    if (freezed_) {
      throw xmlcompiler_logic_error("remapclasses_initialize_vector is freezed.");
    }

    // size
    data_.push_back(v.size() + 1); // +1 == configindex
    // configindex
    data_.push_back(configindex);
    // data
    std::copy(v.begin(), v.end(), std::back_inserter(data_));

    ++(data_[INDEX_OF_COUNT]);

    if (configindex > max_configindex_) {
      max_configindex_ = configindex;
    }
    is_configindex_added_[configindex] = true;
  }

  void
  xmlcompiler::remapclasses_initialize_vector::freeze(void)
  {
    if (freezed_) {
      throw xmlcompiler_logic_error("remapclasses_initialize_vector is already freezed.");
    }

    for (uint32_t i = 0; i < max_configindex_; ++i) {
      if (is_configindex_added_.find(i) == is_configindex_added_.end()) {
        std::vector<uint32_t> v;
        add(v, i);
      }
    }

    freezed_ = true;
  }
}
