#pragma once

#include <memory>
#include "Bundle.h"
#include "JSBigString.h"

namespace facebook {
namespace react {

class BasicBundle : public Bundle {
  public:
    BasicBundle(std::string sourceURL, std::unique_ptr<const JSBigString> script);

    std::string getSourceURL() const override;
    std::shared_ptr<const JSBigString> getScript();
    
    BundleType bundleType = BundleType::BasicBundle;
  private:
    std::string _sourceURL;
    std::shared_ptr<const JSBigString> _script
};

} // react
} // facebook
