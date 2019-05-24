#pragma once

#include <memory>
#include "JSBigString.h"

namespace facebook {
namespace react {

enum struct BundleType {
  BasicBundle = 0,
  IndexedRAMBundle,
  FileRAMBundle,
  DeltaBundle,
};

class Bundle {
  public:
    Bundle() = default;
    Bundle(const Bundle&) = delete;
    Bundle& operator=(const Bundle&) = delete;
    virtual ~Bundle();

    virtual std::string getSourceURL() const = 0;
    
    virtual BundleType bundleType const = 0;
};

} // react
} // facebook
