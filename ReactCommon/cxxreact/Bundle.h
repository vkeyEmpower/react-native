#pragma once

#include <memory>
#include "BundleRegistry.h"
#include "JSBigString.h"

namespace facebook {
namespace react {

// TODO: add types as enum
class Bundle {
  public:
    Bundle() = default;
    Bundle(const Bundle&) = delete;
    Bundle& operator=(const Bundle&) = delete;
    virtual ~Bundle();

    virtual std::string getSourcePath() const = 0;
    virtual std::string getSourceURL() const = 0;
};

} // react
} // facebook
