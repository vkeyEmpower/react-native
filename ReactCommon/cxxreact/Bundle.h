#pragma once

#include <memory>
#include "JSBigString.h"
#include "JSBundleType.h"

#ifndef RN_EXPORT
#define RN_EXPORT __attribute__((visibility("default")))
#endif

namespace facebook {
namespace react {

class RN_EXPORT Bundle {
  public:
    Bundle() = default;
    Bundle(const Bundle&) = delete;
    Bundle& operator=(const Bundle&) = delete;
    virtual ~Bundle() {};

    /**
     * URL with filename from where the source code is comming from.
     * Use it for stack traces.
     */
    virtual std::string getSourceURL() const = 0;
    virtual ScriptTag getBundleType() const = 0;

};

} // react
} // facebook