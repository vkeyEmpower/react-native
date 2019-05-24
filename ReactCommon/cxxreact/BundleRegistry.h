#pragma once

#import <memory>
#import "Bundle.h"

namespace facebook {
namespace react {

class BundleRegistry {
  public:
    BundleRegistry() = default;
    BundleRegistry(const BundleRegistry&) = delete;
    BundleRegistry& operator=(const BundleRegistry&) = delete;
    ~BundleRegistry() {};

    // void loadBundle(std::string bundlePath, bool inCurrentEnvironment);
    // JSModulesUnbundle::Module(uint32_t, uint32_t)
};

} // react
} // facebook

