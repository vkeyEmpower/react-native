#include "BasicBundle.h" 

namespace facebook {
namespace react {
    
  BasicBundle::BasicBundle(std::string sourceURL, std::unique_ptr<const JSBigString> script) {
    sourceURL_ = sourceURL;
    script_ = std::move(script);
  }

  std::string BasicBundle::getSourceURL() const {
    return sourceURL_;
  }

  std::shared_ptr<const JSBigString> BasicBundle::getScript() {
    return script_;
  }

} // react
} // facebook